#define _DEBUG_WIN

#include <math.h>

#include "type.h"
#include "pngres.h"
#include "GL.h"

#define FONT_W			70
#define FONT_H			70
#define FONT_SPACE		3

#define C_R(c)			((unsigned char)((c)&0x000000FF))
#define C_G(c)			((unsigned char)(((c)>>8)&0x000000FF))
#define C_B(c)			((unsigned char)(((c)>>16)&0x000000FF))
#define C_A(c)			((unsigned char)(((c)>>24)&0x000000FF))

typedef struct _ResInfo_t{
	unsigned char *data;
	int w;
	int h;
} ResInfo_t;

typedef struct _FontChar_t{
	int x;
	int w;
} FontChar_t;

static ResInfo_t *resArray;
static int resArraySize = 0;
static unsigned char *font_data;
static FontChar_t fontInfo[16*16];
static unsigned char *_vram;
static int _scr_w;
static int _scr_h;

GL_t GL;

static void drawImage2(double x, double y, int id, int a)
{
	if((id >= 0)&&(id < resArraySize)){
		int i,j,k,m;
		int x0 = (int)x;
		int y0 = (int)y;
		int a0 = a%256;
		int a1;
		
		for(i = 0; i < resArray[id].h; i++){
			for(j = 0; j < resArray[id].w; j++){
				k = 3*(y0+i)*_scr_w+3*(x0+j);
				m = 4*i*resArray[id].w+4*j;
				a1 = resArray[id].data[m+3]*a0/255;
				if(a1 == 255){
					_vram[k+0] = resArray[id].data[m+0];
					_vram[k+1] = resArray[id].data[m+1];
					_vram[k+2] = resArray[id].data[m+2];
				}
				else{
					_vram[k+0] = a1*(resArray[id].data[m+0])/255+_vram[k+0]*(255-a1)/255;
					_vram[k+1] = a1*(resArray[id].data[m+1])/255+_vram[k+1]*(255-a1)/255;
					_vram[k+2] = a1*(resArray[id].data[m+2])/255+_vram[k+2]*(255-a1)/255;
				}
			}
		}
	}
	else{
		_LOGE("GL", "invalid res id! id=%d\n", id);
	}
}

static void drawImage(double x, double y, int id)
{
	drawImage2(x, y, id, 255);
	return;
}

static double getTextWidth(const char * text)
{
	const unsigned char *p = (const unsigned char *)text;
	int ret = 0;
	
	while(*p != '\0'){
		ret += fontInfo[*p-0x20].w+FONT_SPACE;
		p++;
	}
	
	return ret;
}

static void drawText2(double x, double y, const char *text, UIColor color)
{
	const unsigned char *p = text;
	unsigned char c;
	unsigned char r = C_R(color);
	unsigned char g = C_G(color);
	unsigned char b = C_B(color);
	unsigned char a = C_A(color);
	int x0 = (int)x;
	int y0 = (int)y;
	int x1,y1;
	int i,j,k,m;
	int a2;
	
	while(*p != '\0'){
		if(*p < 0x20){
			p++;
			continue;
		}
		
		c = *p-0x20;
		
		x1 = (c)%16*FONT_W+fontInfo[c].x;
		y1 = (c)/16*FONT_H+2;
		
		for(i = 0; i < FONT_H; i++){
			for(j = 0; j < fontInfo[c].w; j++){
				m = 4*((y1+i)*(FONT_W*16)+(x1+j));
				a2 = font_data[m+3]*a/255;

				if(a2 != 0){
					k = 3*((y0+i)*_scr_w+(x0+j));
					_vram[k+0] = (a2*r+_vram[k+0]*(255-a2))/255;
					_vram[k+1] = (a2*g+_vram[k+1]*(255-a2))/255;
					_vram[k+2] = (a2*b+_vram[k+2]*(255-a2))/255;
				}
			}
		}
		
		x0 += fontInfo[c].w+FONT_SPACE;
		p++;
	}
}

static void drawText(double x, double y, const char *text)
{
	drawText2(x, y, text, C_RGBA(255, 255, 255, 255));
}

static void drawTextC(double x, double y, const char *text)
{
	int w = (int)getTextWidth(text);
	
	x = x-w/2;
	drawText2(x, y, text, C_RGBA(255, 255, 255, 255));
}

static void drawTextR(double x, double y, const char *text)
{
	int w = (int)getTextWidth(text);
	
	x = x-w;
	drawText2(x, y, text, C_RGBA(255, 255, 255, 255));
}

static void drawRectFill(double x1, double y1, double x2, double y2, UIColor color)
{
	int i,j,k;
	unsigned char r = C_R(color);
	unsigned char g = C_G(color);
	unsigned char b = C_B(color);
	
	for(i = 0; i < y2-y1; i++){
		for(j = 0; j < x2-x1; j++){
			k = 3*(((int)y1)+i)*_scr_w+3*(((int)x1)+j);
			
			_vram[k+0] = r;
			_vram[k+1] = g;
			_vram[k+2] = b;
		}
	}
}

static void drawRectFill2(double x1, double y1, double x2, double y2, UIColor color)
{
	int i,j,k;
	int a = C_A(color);
	
	for(i = 0; i < y2-y1; i++){
		for(j = 0; j < x2-x1; j++){
			k = 3*(((int)y1)+i)*_scr_w+3*(((int)x1)+j);
			
			_vram[k+0] = C_R(color)*a/255+_vram[k+0]*(255-a)/255;
			_vram[k+1] = C_G(color)*a/255+_vram[k+1]*(255-a)/255;
			_vram[k+2] = C_B(color)*a/255+_vram[k+2]*(255-a)/255;
		}
	}
}

static void drawRect0(double x1, double y1, double x2, double y2, UIColor color)
{
	int i,j,k;
	int a = C_A(color);
	
	for(j = 0; j < x2-x1; j++){
		k = 3*((int)y1)*_scr_w+3*(((int)x1)+j);
		_vram[k+0] = C_R(color)*a/255+_vram[k+0]*(255-a)/255;
		_vram[k+1] = C_G(color)*a/255+_vram[k+1]*(255-a)/255;
		_vram[k+2] = C_B(color)*a/255+_vram[k+2]*(255-a)/255;

		k = 3*((int)y2)*_scr_w+3*(((int)x1)+j);
		_vram[k+0] = C_R(color)*a/255+_vram[k+0]*(255-a)/255;
		_vram[k+1] = C_G(color)*a/255+_vram[k+1]*(255-a)/255;
		_vram[k+2] = C_B(color)*a/255+_vram[k+2]*(255-a)/255;
	}

	for(i = 0; i < y2-y1; i++){
		k = 3*(((int)y1)+i)*_scr_w+3*((int)x1);
		_vram[k+0] = C_R(color)*a/255+_vram[k+0]*(255-a)/255;
		_vram[k+1] = C_G(color)*a/255+_vram[k+1]*(255-a)/255;
		_vram[k+2] = C_B(color)*a/255+_vram[k+2]*(255-a)/255;

		k = 3*(((int)y1)+i)*_scr_w+3*((int)x2);
		_vram[k+0] = C_R(color)*a/255+_vram[k+0]*(255-a)/255;
		_vram[k+1] = C_G(color)*a/255+_vram[k+1]*(255-a)/255;
		_vram[k+2] = C_B(color)*a/255+_vram[k+2]*(255-a)/255;
	}
}

static void drawRect(double x1, double y1, double x2, double y2, UIColor color)
{
	drawRect0(x1, y1, x2, y2, color);
	drawRect0(x1+1, y1+1, x2-1, y2-1, color);
}

static void addImage(int index, const char *fileName)
{
	if(index < resArraySize){
		int w;
		int h;
		unsigned char *data;
		
		data = load_png(fileName, &w, &h);

		if(data != NULL){
			resArray[index].data = data;
			resArray[index].w = w;
			resArray[index].h = h;
		}
		else{
			_LOGE("GL", "%s load error!\n", fileName);
		}
	}
	else{
		_LOGE("GL", "invalid index! index=%d\n", index);
	}
}

static void allocResArray(int total)
{
	_LOGE("GL", "alloc resource array. size=%d\n", total);
	resArray = (ResInfo_t *)malloc(sizeof(ResInfo_t)*total);
	resArraySize = total;
}

static void freeResArray(void)
{
	int i;

	for(i = 0; i < resArraySize; i++){
		free(resArray[i].data);
	}
	
	free(resArray);
	resArray = NULL;
	resArraySize = 0;
}

static void loadFont(const char *fileName)
{
	int i,j,k,m,x,y;
	int left;
	int right;
	int w;
	int h;
		
	font_data = load_png(fileName, &w, &h);

	if(font_data == NULL){
		_LOGE("GL", "font load error! file=%s\n", fileName);
		return;
	}
	
	for(i = 0; i < 16*11; i++){		
		x = i%16*FONT_W;
		y = i/16*FONT_H;
		
		left = FONT_W;
		right = 0;
		
		for(j = 0; j < FONT_H; j++){
			for(k = 0; k < FONT_W; k++){
				m = (y+j)*(FONT_W*16)*4+(x+k)*4;
				
				font_data[m+3] = font_data[m];
				
				if(font_data[m] > 64){
					if(right < k){
						right = k;
					}
					
					if(left > k){
						left = k;
					}
				}
				
				if((k == FONT_W-1)&&(j == FONT_H-1)){
					if(right > left){
						fontInfo[i].x = left;
						fontInfo[i].w = right-left+1;
					}
					else{
						_LOGW("GL", "font error! i=0x%02x\n", i+0x20);
						fontInfo[i].x = 0;
						fontInfo[i].w = FONT_W;
					}
				}
			}
		}

		//_LOGD("GL", "font[%d].x=%d, w=%d\n", i, fontInfo[i].x, fontInfo[i].w);
	}
	//Space
	fontInfo[0].x = FONT_W/4;
	fontInfo[0].w = FONT_W/5;
}

static void setFontSize(int size)
{
}

static void regVram(unsigned char *vram, int w, int h)
{
	_LOGI("GL", "regVram, vram=%p, w=%d, h=%d\n", vram, w, h);
	_vram = vram;
	_scr_w = w;
	_scr_h = h;
}

void GL_init(GL_t *gl)
{
	gl->drawImage2 = drawImage2;
	gl->drawImage = drawImage;
	gl->drawText = drawText;
	gl->drawText2 = drawText2;
	gl->drawTextC = drawTextC;
	gl->drawTextR = drawTextR;
	gl->drawRectFill = drawRectFill;
	gl->drawRectFill2 = drawRectFill2;
	gl->drawRect = drawRect;
	gl->getTextWidth = getTextWidth;

	gl->addImage = addImage;
	gl->allocResArray = allocResArray;
	gl->freeResArray = freeResArray;
	gl->loadFont = loadFont;
	gl->setFontSize = setFontSize;
	gl->regVram = regVram;
}

