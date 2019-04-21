#include "option.h"
#include "landmine.h"
#include "utils.h"
#include "map.h"

static void fill_move(int x, int y);
static void set_default(int index);

//ROAD-0,NORMAL-1,FOREST-2,HOUSE-3,WATER-4,ENTRANCE-5,END-6
static int map_default[MAP_H][MAP_W]=
{
	{2,2,2,1,1,4,4,4,4,1,1,2,2,2},
	{2,1,1,1,1,1,4,1,1,1,1,1,1,1},
	{1,1,0,0,0,1,1,1,1,1,1,1,3,3},
	{1,1,0,1,0,1,0,0,0,0,0,0,0,6},
	{1,1,0,1,0,1,0,1,1,1,1,1,3,3},
	{5,0,0,1,0,1,0,1,1,1,1,1,1,1},
	{1,1,1,1,0,0,0,2,2,4,4,4,1,1},
	{1,1,1,4,4,2,2,2,2,2,4,4,4,1},
	{1,1,4,4,2,2,2,2,2,2,2,4,4,4},
};

#if 1
int all_map_data[MAP_TOTAL*MAP_H*MAP_W];
#else
static int all_map_data[MAP_TOTAL*MAP_H*MAP_W];
#endif

static int move_map[MAP_H][MAP_W];
static int temp_map[MAP_H][MAP_W];

#define NO_FILLED	-3

void map_fill(int index, int map_data[MAP_H][MAP_W], point_t *entrance, int *total)
{
	if(index < MAP_TOTAL)
	{
		int i;
		int j;
		int count = 0;
		
		memcpy(map_data, &all_map_data[index*MAP_H*MAP_W], sizeof(int)*MAP_H*MAP_W);
		
		for(i = 0; i < MAP_H; i++)
		{
			for(j = 0; j < MAP_W; j++)
			{
				if(map_data[i][j] == FIELD_ENTRANCE)
				{
					entrance[count].x = j;
					entrance[count].y = i;
					count++;
					
					map_data[i][j] = FIELD_ROAD;
				}
				else if(map_data[i][j] == FIELD_END)
				{
					map_data[i][j] = FIELD_ROAD;
				}
				else if(map_data[i][j] == FIELD_TREE)
				{
					map_data[i][j] = FIELD_LAND;
				}
			}
		}

		*total = count;
	}
}

int map_is_mining_enable(int x, int y, int id, int map[MAP_H][MAP_W])
{
	int ret = 0;

	if(! map_is_in_range(x, y))
	{
		_LOGE("Map", "coodinate error! x=%d, y=%d\n", x, y);
		return ret;
	}
	
	if(((map[y][x] == FIELD_ROAD)&&(id != MINE_RS))
		||((map[y][x] == FIELD_LAND)&&(id == MINE_RS)))
	{
		ret = 1;
	}

	return ret;
}

int map_is_in_range(int x, int y)
{
	int ret  = 0;
	
	if((x >= 0)&&(x < MAP_W)
		&&(y >= 0)&&(y < MAP_H))
	{
		ret = 1;
	}
	
	return ret;
}

int map_is_road_side(int x, int y, int map[MAP_H][MAP_W])
{
	int ret = 0;
	const int offset[8][2]= 
	{
		{-1, -1},
		{0, -1},
		{+1, -1},
		{-1, 0},
		{+1, 0},
		{-1, +1},
		{0, +1},
		{+1, +1}
	};
	int i;
	int x0;
	int y0;

	if(! map_is_in_range(x, y))
	{
		return ret;
	}
	
	for(i = 0; i < 8; i++)
	{
		x0 = x+offset[i][0];
		y0 = y+offset[i][1];

		if(map_is_in_range(x0, y0))
		{
			if((map[y0][x0] == FIELD_ROAD)
				&&(map[y][x] != FIELD_ROAD))
			{
				ret = 1;
				break;
			}
		}
	}
	
	return ret;
}

void map_load_maps(void)
{
	int i;
	char file_name[256];
	char path[1024];
	
	for(i = 0; i < MAP_TOTAL; i++)
	{
		set_default(i);
		sprintf(file_name, "Map%d.dat", (i+1));
		Utils_getAssetsPath(file_name, path);
		map_load(path, &all_map_data[i*MAP_H*MAP_W]);
	}
}

void map_load(const char *file_name, int *map)
{
	FILE* fp = NULL;

	_LOGI("Map", "map load, file=%s\n", file_name);
	fp = fopen(file_name, "rb");

	if(fp != NULL)
	{
		fread(map, sizeof(int)*MAP_W*MAP_H, 1, fp);
		fclose(fp);
	}
	else
	{
		_LOGE("Map", "load failed! file=%s\n", file_name);
	}
}

void map_save(const char *file_name, int *map)
{
	FILE* fp = NULL;

	_LOGI("Map", "map save, file=%s\n", file_name);
	fp = fopen(file_name, "wb");

	if(fp != NULL)
	{
		fwrite(map, sizeof(int)*MAP_W*MAP_H, 1, fp);
		fclose(fp);
	}
	else
	{
		_LOGE("Map", "save failed! file=%s\n", file_name);
	}
}

void map_get(int index, int map[MAP_H][MAP_W])
{
	if(index < MAP_TOTAL)
	{
		//_LOGI("Map", "get map, index=%d\n", index);
		memcpy(map, &all_map_data[index*MAP_H*MAP_W], sizeof(int)*MAP_W*MAP_H);
	}
	else
	{
		_LOGE("Map", "map get failed! index=%d\n", index);
	}
}

void map_get_move_direction(int index, int dir[MAP_H][MAP_W])
{
	if(index < MAP_TOTAL)
	{
		int i;
		int j;
		point_t end_point[4];
		int end_total = 0;

		_LOGI("Map", "get direction, index=%d\n", index);

		memcpy(temp_map, &all_map_data[index*MAP_H*MAP_W], sizeof(int)*MAP_W*MAP_H);
		
		for(i = 0; i < MAP_H; i++)
		{
			for(j = 0; j < MAP_W; j++)
			{
				move_map[i][j] = NO_FILLED;

				if(temp_map[i][j] == FIELD_END)
				{
					end_point[end_total].x = j;
					end_point[end_total].y = i;
					end_total++;
				}
			}
		}
		
		for(i = 0; i < end_total; i++)
		{
			move_map[end_point[i].y][end_point[i].x] = 0;
		}
		
		for(i = 0; i < end_total; i++)
		{
			fill_move(end_point[i].x, end_point[i].y);
		}
		
		memcpy(dir, move_map, sizeof(int)*MAP_W*MAP_H);
	}
	else
	{
		_LOGE("Map", "get direction failed! index=%d\n", index);
	}
}

static void fill_move(int x, int y)
{
	static const int move_dir_2[4]={
		MOVE_L, MOVE_U, MOVE_R, MOVE_D
	};
	static const int move_dir[4][2]={
		{+1,0}, {0,+1}, {-1,0}, {0,-1}
	};
	int i;
	int x0;
	int y0;
	
	for(i = 0; i < 4; i++)
	{
		x0 = x+move_dir[i][0];
		y0 = y+move_dir[i][1];
		
		if(map_is_in_range(x0, y0))
		{
			if((move_map[y0][x0] == NO_FILLED)
				&&((temp_map[y0][x0] == FIELD_ROAD)
				||(temp_map[y0][x0] == FIELD_ENTRANCE)))
			{
				move_map[y0][x0] = move_dir_2[i];

				fill_move(x0, y0);
			}
		}
	}
}

static void set_default(int index)
{
	if((index >= 0)&&(index < MAP_TOTAL))
	{
		memcpy(&all_map_data[index*MAP_H*MAP_W], map_default, sizeof(int)*MAP_W*MAP_H);
	}
}
