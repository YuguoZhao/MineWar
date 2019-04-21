#include "L.h"

static const double layoutTable[][6]={
	//6     6p      5/5s	4/4s	1/2     p         //Device
	{1334	,2208	,1136	,960	,1024	,1024	},//L_SCR_W 		;
	{750	,1242	,640	,640	,768	,768	},//L_SCR_H 		;
    {0		,0		,0		,0		,0		,0		},//L_SCR_X0 		;
    {0		,0		,0		,0		,0		,0		},//L_SCR_Y0 		;
	{3		,0		,0		,0		,0		,0		},//L_X0 		;
	{1      ,0		,1		,0		,0		,0		},//L_Y0 		;
	{83		,138	,71     ,60     ,73     ,73     },//L_GRID_W 		;
	{83		,138	,71     ,71     ,73     ,73     },//L_GRID_H 		;
	{83*2+2	,138*2	,71*2	,60*2	,0      ,0      },//L_PLAY_MTX_X 	;
	{0		,0		,0		,0		,111	,111	},//L_PLAY_MTX_Y 	;
	{83*14	,138*14	,71*14	,60*14	,73*14	,73*14	},//L_PLAY_MTX_W 	;
    {83*9	,138*9	,71*9	,71*9	,73*9	,73*9	},//L_PLAY_MTX_H 	;
    {359	,597	,307	,307	,307	,307	},//L_LOGO_W      ;
	{206	,343	,176	,176	,176	,176	},//L_LOGO_MINE_W	;
	{151	,251	,129	,129	,129	,129	},//L_LOGO_WAR_W	;
	{240	,400	,212	,212	,212	,212	},//L_ICON_W_L	;
	{120	,200	,106	,106	,106	,106	},//L_ICON_W_S	;
	{607	,1004	,515	,427	,459	,459	},//L_ICON_HO_X   ;
	{630	,1042	,534	,534	,663	,663	},//L_ICON_HO_Y   ;
	{488	,806	,415	,327	,359	,359	},//L_ICON_A_X 	;
	{16		,24		,14		,14		,14		,14		},//L_ICON_A_Y 	;
	{480	,800	,410	,410	,490	,490	},//L_ICON_TEXT_Y ;
	{20		,31		,18		,18		,17		,17		},//L_ICON_OFFSET ;
    {83*2	,138*2	,71*2	,60*2	,73*2	,73*2	},//L_MAP_PAGE_W	;
    {83*2	,138*2	,71*2	,71*2	,73*2	,73*2	},//L_MAP_PAGE_H	;
    {1168   ,1932   ,994    ,840    ,878    ,878    },//L_MAP_PAGE_X2	;
    {292	,483	,249	,249	,311	,311	},//L_MAP_PAGE_Y	;
	{240	,360	,200	,200	,200	,200	},//L_MQ_EDIT_W	;
	{557	,924    ,468    ,380    ,412    ,412    },//L_MQ_EDIT_X	;
	{667	,1104	,569	,569	,695	,695	},//L_MQ_EDIT_Y2	;
	{377	,621	,316	,270	,260	,260	},//L_ENTER_X		;
	{188	,310	,158	,158	,220	,220	},//L_ENTER_Y		;
	{581	,966	,504	,420	,504	,504	},//L_ENTER_W		;
	{373	,621	,324	,324	,328	,328	},//L_ENTER_H		;
	{15		,15		,13		,13		,15		,15		},//L_TITLE_X		;
	{20		,35		,3		,17		,25		,25		},//L_TEXT_Y		;
	{83*4	,138*4	,71*4 	,160    ,183    ,183    },//L_HONOR_X		;(SW-GH*9)/2
	{83*3	,138*3	,71*3	,71*3	,73*3.5	,73*3.5	},//L_HONOR_Y		;
	{83*9	,138*9	,71*9	,71*9	,73*9	,73*9	},//L_HONOR_W		;
	{83*2	,138*2	,71*2	,71*2	,73*2	,73*2	},//L_HONOR_H		;
	{83*6	,138*6	,71*6	,60*6	,73*4	,73*4	},//L_MN_MENU_X	;
	{83*8	,138*8	,71*8	,60*8	,73*6	,73*8	},//L_MN_REPLAY_X	;
	{83*10	,138*10	,71*10	,60*10	,73*8	,73*8	},//L_MN_NEXT_X	;
	{83*6	,138*6	,71*6	,71*6	,476    ,476	},//L_MN_BTN_Y	;GH*6+OY
	{83*2	,138*2	,71*2	,60*2	,73*2	,73*2	},//L_MN_BTN_W	;
	{28		,46		,24		,20		,26		,26		},//L_NUMBER_W	;
	{35		,60		,30		,25     ,73*12.5,73*12.5},//L_BTN_PLAY_X	;
    {645	,1050	,550	,550	,15     ,15     },//L_BTN_PLAY_Y	;
	{0		,0		,0		,0		,0		,0		},//L_BACK_X		;
	{0		,0		,0		,0		,0		,0		},//L_BACK_Y		;
	{0		,0		,0		,0		,365	,365    },//L_PLAY_TB_X	;
	{83*2.5	,138*2.5,71*2.5 ,71*2.5 ,15     ,15     },//L_PLAY_TB_Y	;GW*5/2
	{83*2-10,266	,71*2-10,60*2-10,73*4	,73*4	},//L_PLAY_TB_W	;GW*2-10
	{83*4	,138*4	,71*4	,71*4	,73     ,73     },//L_PLAY_TB_H	;
	{35		,60		,30		,25		,14     ,14		},//L_TB_ICON_X   ;for iPhone
    {35		,60		,30		,25		,15     ,15		},//L_TB_ICON_Y   ;for iPad
    {35		,60		,30		,25		,36     ,36		},//L_BTN_MENU2_X ;
	{20		,30		,20		,20		,15     ,15     },//L_BTN_MENU2_Y	;
	{83*15	,138*15	,71*15	,60*15	,73*13	,73*13	},//L_BTN_SAVE2_X	;
	{0		,0		,0		,0		,0		,0		},//L_BTN_SAVE2_Y	;
	{83*6	,138*6	,71*6	,60*6	,73*4	,73*4	},//L_BK_ITEM_X	;
	{83*6	,138*6	,71*6	,60*6	,73*6	,73*6	},//L_BK_ITEM_W	;
	{83*17/6,391    ,71*17/6,71*17/6,245    ,245	},//L_BK_MENU_Y	;GH*17/6+OY
	{83*4	,138*4	,71*4	,71*4	,330    ,330	},//L_BK_REPLAY_Y	;GH*4+OY
	{83*31/6,713    ,71*31/6,71*31/6,415    ,415	},//L_BK_CONTIN_Y ;GH*31/6+OY
	{83*6.5	,138*6.5,71*6.5 ,60*6.5 ,73*4.5 ,73*4.5 },//L_MN_MENU2_X	;GW*13/2
	{83*9.5	,138*9.5,71*9.5 ,60*9.5 ,73*7.5 ,73*7.5 },//L_MN_REPLAY2_X;GW*19/2
    {83*13	,138*13	,71*13	,60*13	,73*12	,73*12	},//L_CAL_ADJ_UP_X;
    {83*9	,138*9	,71*9	,60*9	,73*8	,73*8	},//L_CAL_ADJ_DN_X;
    {83*7	,138*7	,71*7	,71*7	,73*7	,73*7	},//L_CAL_ADJ_H	;
    {83*4	,138*4	,71*4	,60*4	,73*3	,73*3	},//L_CAL_EID_X	;
    {83*7	,138*7	,71*7	,60*7	,73*6	,73*6	},//L_CAL_Q_X     ;
	{83*6	,138*6	,71*6	,60*6	,73*5	,73*5	},//L_CAL_L_DN_X	;
	{83*9	,138*9	,71*9	,60*9	,73*8	,73*8	},//L_CAL_L_UP_X	;
	{83*8	,138*8	,71*8	,71*8	,73*9	,73*9	},//L_CAL_ITEM_Y	;
	{83*0	,138*0	,71*0	,71*0	,73*0	,73*0	},//L_CAL_ITEM_Y2	;
    {6      ,9.5    ,6      ,4.5    ,3      ,3      },//L_LOCK_S_OX   ;
    {35		,60		,30		,25		,183    ,183	},//L_ME_TB_X     ;
    {0		,0		,0		,0		,14     ,14		},//L_ME_TB_Y     ;
    {83		,138	,71		,60		,73*7	,73*7	},//L_ME_TB_W     ;
    {83*7	,138*7	,71*7	,71*7	,73     ,73     },//L_ME_TB_H     ;
    {35		,60		,30		,25     ,73*10.5,73*10.5},//L_ME_SAVE_X	;
    {83*8	,138*8	,71*8	,71*8	,14     ,14     },//L_ME_SAVE_Y	;
    {83*2	,138*2  ,71*2   ,60*2   ,73     ,73     },//L_LIST_X		;
    {83		,138	,71     ,71     ,73*1.7 ,73*1.7	},//L_LIST_Y		;
};

static int layout = 0;
static int density = 2;

double L_n(int index)
{
    return layoutTable[index][layout]/density;
}

double L_x(int index)
{
    return (layoutTable[index][layout]+layoutTable[L_X0][layout])/density;
}

double L_y(int index)
{
    return (layoutTable[index][layout]+layoutTable[L_Y0][layout])/density;
}

void L_setDensity(int layout0, int density0)
{
    layout = layout0;
    density = density0;
}

void L_setWidgetData(WidgetInfo_t *array, int size)
{
	int i;

	for(i = 0; i < size; i++){
		array[i].x = (int)L_x(array[i].x);
		array[i].y = (int)L_y(array[i].y);
		array[i].w = (int)L_n(array[i].w);
		array[i].h = (int)L_n(array[i].h);
	    array[i].gw = (int)L_n(array[i].gw);
	    array[i].gh = (int)L_n(array[i].gh);
	}
}