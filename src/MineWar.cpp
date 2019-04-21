#define _DEBUG_WIN

#ifdef	_DEBUG_WIN
#include "stdafx.h"
#include <windows.h>
#include <time.h>
#include "dispdrv.h"

#pragma   comment(lib,"WINMM.LIB")
#pragma   comment(lib,"dispdrv.lib")
#endif

#include "App.h"

/*******************************************************************************
	Macro Definition
*******************************************************************************/
#define SCR_WIDTH		(1136)
#define SCR_HEIGHT		(640)

//#define	_DEBUG_DRAW_TIME
//#define	_DEBUG_UNIT_TEST

/*******************************************************************************
	Type Definition
*******************************************************************************/

/*******************************************************************************
	Prototype  Declaration
*******************************************************************************/
#ifdef _DEBUG_WIN
static void zoom_screen(void);
#endif

/*******************************************************************************
	Variable  Definition
*******************************************************************************/
#ifdef _DEBUG_WIN
static unsigned char VRAM[SCR_WIDTH*SCR_HEIGHT*3];
static unsigned char VRAM2[SCR_WIDTH/2*SCR_HEIGHT/2*3];
#endif

/*******************************************************************************
	Function  Definition
*******************************************************************************/
#ifdef _DEBUG_WIN
#ifdef _DEBUG_UNIT_TEST
extern "C"
{
void test_dlist(void);
void test_vstack(void);
void test_map(void);
}
#endif
int main(int argc, char* argv[])
{
	unsigned char tstatus = 0;
	unsigned char last_tstatus = 0;
	int x;
	int y;
	int count = 0;
#ifdef _DEBUG_DRAW_TIME
	double tt = 0;
	double dt = 0;
	LARGE_INTEGER freq, lt0, lt;
#endif
	int count2 = 1;

	_LOGI("main", "init\n");
	
	App_startup();
	GL.regVram(VRAM, SCR_WIDTH, SCR_HEIGHT);

	disp_drv_init(SCR_WIDTH/2, SCR_HEIGHT/2, 24);
#ifdef _DEBUG_DRAW_TIME
	QueryPerformanceFrequency(&freq);
#endif
	_LOGI("main", "start...\n");
#ifdef _DEBUG_UNIT_TEST
	test_dlist();
	test_vstack();
	test_map();
#endif
	while(1){
		disp_drv_get_touch(&tstatus, &x, &y);
		x *= 2;
		y *= 2;

		if(tstatus != last_tstatus){
			if(tstatus){
				App_touchesBegan(x, y);
			}
			else{
				App_touchesEnded(x, y);
			}
		}
		else if(tstatus){
			App_touchesMoved(x, y);
		}

		last_tstatus = tstatus;

		App_sendEvent(EV_TIME_TICK);
		
		if(count%5 == 0){
			memset(VRAM, 0, sizeof(VRAM));
#ifdef _DEBUG_DRAW_TIME
			QueryPerformanceCounter(&lt0);
#endif
			App_draw();
#ifdef _DEBUG_DRAW_TIME
			QueryPerformanceCounter(&lt);
			dt = (double)(lt.QuadPart-lt0.QuadPart)/((double)freq.QuadPart/1000000);
			tt += dt;
			if(count%50 == 0){
				_LOGI("main", "dt=%05dus, at=%05dus\n", (int)dt, (int)tt/count2);
			}
#endif
			count2++;
			
			zoom_screen();
			disp_drv_send_data(VRAM2);
		}
		else{
			Sleep(10);
		}
		
		count++;
	}

	App_exit();
	
	return 0;
}

static void zoom_screen(void)
{
	int i;
	int j;
	int m;
	int n;

	for(i = 0; i < SCR_HEIGHT/2; i++){
		for(j = 0; j < SCR_WIDTH/2; j++){
			m = 3*(i*SCR_WIDTH/2+j);
			n = 3*(2*i*SCR_WIDTH+2*j);
			
			VRAM2[m+0] = VRAM[n+0];
			VRAM2[m+1] = VRAM[n+1];
			VRAM2[m+2] = VRAM[n+2];
		}
	}
}
#endif
