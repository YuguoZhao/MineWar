#include "option.h"

#define OPT_INFO_MIN	0
#define OPT_INFO_MAX	1
#define OPT_INFO_STEP	2
#define OPT_INFO_DEF	3

static void set_default(void);

static int item_value[OPT_ID_MAX];

static const int item_info[OPT_ID_MAX*4]= 
{
//	min	max		step	default
	10	,1000	,10		,20		,//OPT_ID_ENEMY_DISPOSE_CYCLE,
	500	,10000	,500	,1000	,//OPT_ID_ENEMY_MOVE_CYCLE,
	10	,500	,10		,50		,//OPT_ID_BULLET_MOVE_CYCLE,
	1000,50000	,1000	,7000	,//OPT_ID_PLANT_GROW_CYCLE,
	2000,20000	,1000	,10000	,//OPT_ID_PLUG_TIMER_CYCLE,
	50	,5000	,50		,100	,//OPT_ID_INITIAL_MONEY,
	0	,100	,1		,100	,//OPT_ID_DISPOSE_OFFSET,
	5	,100	,5		,5		,//OPT_ID_PLANT_PRICE,
	2	,20		,1		,5		,//OPT_ID_PLANT_HARVEST,
	5	,200	,5		,5		,//OPT_ID_MINE_PRICE_NM,
	5	,200	,5		,10		,//OPT_ID_MINE_PRICE_AE,
	5	,200	,5		,20		,//OPT_ID_MINE_PRICE_RS,
	5	,200	,5		,30		,//OPT_ID_MINE_PRICE_AA,
	5	,200	,5		,40		,//OPT_ID_MINE_PRICE_AT,
	5	,200	,5		,40		,//OPT_ID_PLUG_PRICE_TIMER,
	5	,200	,5		,50		,//OPT_ID_PLUG_PRICE_REMOTE,
	0	,1		,1		,0		,//OPT_ID_GAME_SPEED,
	100	,20000	,100	,1000	,//OPT_ID_LIMIT_MONEY
	0	,1		,1		,0		,//OPT_ID_QUEUE_RANDOM
	10	,50		,1		,25		,//OPT_ID_EMEMY_Q1_LEN,
	10	,50		,1		,25		,//OPT_ID_EMEMY_Q2_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q3_LEN,
	10	,50		,1		,25		,//OPT_ID_EMEMY_Q4_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q5_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q6_LEN,
	10	,50		,1		,30		,//OPT_ID_EMEMY_Q7_LEN,
	10	,50		,1		,35		,//OPT_ID_EMEMY_Q8_LEN,
	10	,50		,1		,40		,//OPT_ID_EMEMY_Q9_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q10_LEN,
	10	,50		,1		,30		,//OPT_ID_EMEMY_Q11_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q12_LEN,
	10	,50		,1		,40		,//OPT_ID_EMEMY_Q13_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q14_LEN,
	10	,50		,1		,45		,//OPT_ID_EMEMY_Q15_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q16_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q17_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q18_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q19_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q20_LEN,
	10	,50		,1		,25		,//OPT_ID_EMEMY_Q21_LEN,
	10	,50		,1		,25		,//OPT_ID_EMEMY_Q22_LEN,
	10	,50		,1		,30		,//OPT_ID_EMEMY_Q23_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q24_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q25_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q26_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q27_LEN,
	10	,50		,1		,40		,//OPT_ID_EMEMY_Q28_LEN,
	10	,50		,1		,40		,//OPT_ID_EMEMY_Q29_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q30_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q31_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q32_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q33_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q34_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q35_LEN,
	10	,50		,1		,50		,//OPT_ID_EMEMY_Q36_LEN,
};

static const char * const item_names[]={
    "Enemy dispose cycle"	,//OPT_ID_ENEMY_DISPOSE_CYCLE,
    "Enemy moving cycle"	,//OPT_ID_ENEMY_MOVE_CYCLE,
    "Bullet moving cycle"	,//OPT_ID_BULLET_MOVE_CYCLE,
    "Plant growing cycle"	,//OPT_ID_PLANT_GROW_CYCLE,
    "Plug timer cycle"		,//OPT_ID_PLUG_TIMER_CYCLE,
    "Initial money"			,//OPT_ID_INITIAL_MONEY,
    "Dispose offset"		,//OPT_ID_DISPOSE_OFFSET,
    "Plant price"			,//OPT_ID_PLANT_PRICE,
    "Plant harvest"			,//OPT_ID_PLANT_HARVEST,
    "NM mine price"			,//OPT_ID_MINE_PRICE_NM,
    "AE mine price"			,//OPT_ID_MINE_PRICE_AE,
    "RS mine price"			,//OPT_ID_MINE_PRICE_RS,
    "AA mine price"			,//OPT_ID_MINE_PRICE_AA,
    "AT mine price"			,//OPT_ID_MINE_PRICE_AT,
    "Plug timer price"		,//OPT_ID_PLUG_PRICE_TIMER,
    "Plug remote price"		,//OPT_ID_PLUG_PRICE_REMOTE,
    "Game speed"			,//OPT_ID_GAME_SPEED,
    "Limit mode money"		,//OPT_ID_LIMIT_MONEY
    "Queue random"			,//OPT_ID_QUEUE_RANDOM
    "G-01 Q length"			,//OPT_ID_EMEMY_Q1_LEN,
    "G-02 Q length"			,//OPT_ID_EMEMY_Q2_LEN,
    "G-03 Q length"			,//OPT_ID_EMEMY_Q3_LEN,
    "G-04 Q length"			,//OPT_ID_EMEMY_Q4_LEN,
    "G-05 Q length"			,//OPT_ID_EMEMY_Q5_LEN,
    "G-06 Q length"			,//OPT_ID_EMEMY_Q6_LEN,
    "G-07 Q length"			,//OPT_ID_EMEMY_Q7_LEN,
    "G-08 Q length"			,//OPT_ID_EMEMY_Q8_LEN,
    "G-09 Q length"			,//OPT_ID_EMEMY_Q9_LEN,
    "G-10 Q length"			,//OPT_ID_EMEMY_Q10_LEN,
    "G-11 Q length"			,//OPT_ID_EMEMY_Q11_LEN,
    "G-12 Q length"			,//OPT_ID_EMEMY_Q12_LEN,
    "G-13 Q length"			,//OPT_ID_EMEMY_Q13_LEN,
    "G-14 Q length"			,//OPT_ID_EMEMY_Q14_LEN,
    "G-15 Q length"			,//OPT_ID_EMEMY_Q15_LEN,
    "G-16 Q length"			,//OPT_ID_EMEMY_Q16_LEN,
    "G-17 Q length"			,//OPT_ID_EMEMY_Q17_LEN,
    "G-18 Q length"			,//OPT_ID_EMEMY_Q18_LEN,
    "G-19 Q length"			,//OPT_ID_EMEMY_Q19_LEN,
    "G-20 Q length"			,//OPT_ID_EMEMY_Q20_LEN,
    "G-21 Q length"			,//OPT_ID_EMEMY_Q21_LEN,
    "G-22 Q length"			,//OPT_ID_EMEMY_Q22_LEN,
    "G-23 Q length"			,//OPT_ID_EMEMY_Q23_LEN,
    "G-24 Q length"			,//OPT_ID_EMEMY_Q24_LEN,
    "G-25 Q length"			,//OPT_ID_EMEMY_Q25_LEN,
    "G-26 Q length"			,//OPT_ID_EMEMY_Q26_LEN,
    "G-27 Q length"			,//OPT_ID_EMEMY_Q27_LEN,
    "G-28 Q length"			,//OPT_ID_EMEMY_Q28_LEN,
    "G-29 Q length"			,//OPT_ID_EMEMY_Q29_LEN,
    "G-30 Q length"			,//OPT_ID_EMEMY_Q30_LEN,
    "G-31 Q length"			,//OPT_ID_EMEMY_Q31_LEN,
    "G-32 Q length"			,//OPT_ID_EMEMY_Q32_LEN,
    "G-33 Q length"			,//OPT_ID_EMEMY_Q33_LEN,
    "G-34 Q length"			,//OPT_ID_EMEMY_Q34_LEN,
    "G-35 Q length"			,//OPT_ID_EMEMY_Q35_LEN,
    "G-36 Q length"			,//OPT_ID_EMEMY_Q36_LEN,
};

void opt_load(const char *file_name)
{
	FILE* fp = NULL;

	set_default();

	_LOGI("Option", "option load, file=%s\n", file_name);
	fp = fopen(file_name, "rb");
	
	if(fp == NULL)	
	{
		_LOGE("Option", "load failed! file=%s\n", file_name);
		return;
	}
	
	fread(item_value, sizeof(item_value), 1, fp);
	fclose(fp);
}

void opt_save(const char *file_name)
{
	FILE* fp = NULL;

	_LOGI("Option", "option save, file=%s\n", file_name);
	fp = fopen(file_name, "wb");
	
	if(fp == NULL)
	{
		_LOGE("Option", "save failed! file=%s\n", file_name);
		return;
	}
	
	fwrite(item_value, sizeof(item_value), 1, fp);
	fclose(fp);	
}

void opt_adjust_up(int index)
{
	if((index < 0)||(index >= OPT_ID_MAX))
	{
		_LOGE("Option", "opt_adjust_down, index=%d\n", index);
		return;
	}
	
	if(item_value[index]+item_info[4*index+OPT_INFO_STEP] < item_info[4*index+OPT_INFO_MAX])
	{
        item_value[index] += item_info[4*index+OPT_INFO_STEP];
    }
    else
	{
        item_value[index] = item_info[4*index+OPT_INFO_MAX];
    }
}

void opt_adjust_down(int index)
{
	if((index < 0)||(index >= OPT_ID_MAX))
	{
		_LOGE("Option", "opt_adjust_down, index=%d\n", index);
		return;
	}
	
	if(item_value[index]-item_info[4*index+OPT_INFO_STEP] > item_info[4*index+OPT_INFO_MIN])
	{
        item_value[index] -= item_info[4*index+OPT_INFO_STEP];
    }
    else
	{
        item_value[index] = item_info[4*index+OPT_INFO_MIN];
    }
}

int opt_get_value(int index)
{
	if((index >= 0)&&(index < OPT_ID_MAX))
	{
		return item_value[index];
	}
	else
	{
		_LOGE("Option", "opt_get_value, index=%d\n", index);
		return -1;
	}
}

const char *opt_get_name(int index)
{
	if((index >= 0)&&(index < OPT_ID_MAX))
	{
		return item_names[index];
	}
	else
	{
		_LOGE("Option", "opt_get_name, index=%d\n", index);
		return "";
	}
}

static void set_default(void)
{
	int i;

	for(i = 0; i < OPT_ID_MAX; i++)
	{
		item_value[i] = item_info[4*i+OPT_INFO_DEF];
	}
}