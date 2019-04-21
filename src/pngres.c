#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "png.h"
#include "pngres.h"

#ifdef _DEBUG
#pragma   comment(lib,"zlib1d.lib")
#pragma   comment(lib,"libpng16d.lib")
#else
#pragma   comment(lib,"zlib1.lib")
#pragma   comment(lib,"libpng16.lib")
#endif

#define _LOG 				printf
#define PNG_BYTES_TO_CHECK	4

void *load_png(const char *filepath, int *pw, int *ph)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep *row_ptrs;
	char buf[PNG_BYTES_TO_CHECK];
	int w, h, i, j, k, temp;
	int color_type;
	int bit_depth;
	unsigned char *pixels = NULL;

	fp = fopen(filepath, "rb");
	
	if(fp == NULL){
		_LOG("file %s open failed!\n", filepath);
		return NULL;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	
	if (png_ptr == NULL){
		fclose(fp);
		_LOG("create read struct failed!\n");
		return NULL;
	}

   info_ptr = png_create_info_struct(png_ptr);
   
	if (info_ptr == NULL){
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		_LOG("create info struct failed!\n");
		return NULL;
	}

	if(setjmp(png_jmpbuf(png_ptr))){
		_LOG("setjmp error!\n");
		goto end;
	}
	
	temp = fread(buf, 1, PNG_BYTES_TO_CHECK, fp);
	
	if(temp < PNG_BYTES_TO_CHECK) {
		_LOG("read bytes2check error!\n");
		goto end;
	}
	
	temp = png_sig_cmp((png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK);
	
	if(temp != 0) {
		_LOG("file is NOT png file!\n");
		goto end;
	}
	
	rewind(fp);
	png_init_io(png_ptr, fp);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
	color_type = png_get_color_type(png_ptr, info_ptr);
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	w = png_get_image_width(png_ptr, info_ptr);
	h = png_get_image_height(png_ptr, info_ptr);

	*pw = w;
	*ph = h;

	//_LOG("file=%s, w=%d, h=%d, color_type=%d, bit_depth=%d\n", 
	//	filepath, w, h, color_type, bit_depth);

	if((color_type != PNG_COLOR_TYPE_RGB_ALPHA)
		&&(color_type != PNG_COLOR_TYPE_RGB)){
		_LOG("color type(%d) is NOT supported!\n", color_type);
		goto end;
	}

	if(bit_depth != 8){
		_LOG("bit_depth(%d) is NOT supported!\n", bit_depth);
		goto end;
	}
	
	row_ptrs = png_get_rows(png_ptr, info_ptr);
	pixels = malloc(w*h*4);

	if(pixels == NULL){
		_LOG("malloc failed!\n");
		goto end;
	}
	
	if(color_type == PNG_COLOR_TYPE_RGB_ALPHA){
		for(i = 0; i < h; i++){
			for(j = 0; j < w; j++){
				k = 4*(i*w+j);
				pixels[k+0] = row_ptrs[i][4*j+0];	// red
				pixels[k+1] = row_ptrs[i][4*j+1];	// green
				pixels[k+2] = row_ptrs[i][4*j+2];	// blue
				pixels[k+3] = row_ptrs[i][4*j+3];	// alpha
			}
		}
	}
	else{
		for(i = 0; i < h; i++){
			for(j = 0; j < w; j++){
				k = 4*(i*w+j);
				pixels[k+0] = row_ptrs[i][3*j+0];	// red
				pixels[k+1] = row_ptrs[i][3*j+1];	// green
				pixels[k+2] = row_ptrs[i][3*j+2];	// blue
				pixels[k+3] = 255; 				 	// alpha
			}
		}
	}
end:
	fclose(fp);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	return (void*)pixels;
}

