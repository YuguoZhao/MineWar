
#define _UNIT_TEST
#define _CASE_TOTAL	16

#include "type.h"
#include "landmine.h"
#include "map.h"

extern int all_map_data[MAP_TOTAL*MAP_H*MAP_W];

static int test_map1[MAP_H][MAP_W]=
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

static int test_map2[MAP_H][MAP_W]=
{
	{5,0,0,1,1,1,4,4,1,1,1,0,0,5},
	{1,1,0,0,1,1,1,1,1,1,0,0,1,1},
	{1,1,1,0,0,1,1,1,1,0,0,1,1,1},
	{4,1,1,1,0,0,3,3,0,0,1,1,1,4},
	{4,4,1,1,1,0,6,6,0,1,1,1,4,4},
	{4,1,1,1,0,0,3,3,0,0,1,1,1,4},
	{1,1,1,0,0,1,1,1,1,0,0,1,1,1},
	{1,1,0,0,1,1,1,1,1,1,0,0,1,1},
	{5,0,0,1,1,1,4,4,1,1,1,0,0,5},
};

static void case_01_001(void)
{
	int tmp_map[MAP_H][MAP_W];

	_T_CASE("MAP-01-001");
	_T_PURPOSE("validate map_save and map_load.");
	_T_PRECOND("-");

	_T_STEP(1);
	_T_OPER("map_save(\"testmap-01.dat\", test_map1)");
	map_save("testmap-01.dat", (int *)test_map1);

	_T_STEP(2);
	_T_OPER("map_load(\"testmap-01.dat\", tmp_map)");
	map_load("testmap-01.dat", (int *)tmp_map);
	
	_T_ASSERT(memcmp(test_map1, tmp_map, sizeof(test_map1)) == 0);
	_T_END_OK();
}

static void case_01_002(void)
{
	int tmp_map[MAP_H][MAP_W];

	_T_CASE("MAP-01-002");
	_T_PURPOSE("validate map_get.");
	_T_PRECOND("-");

	_T_STEP(1);
	_T_OPER("map_save(\"Map1.dat\", test_map1)");
	map_save("Map1.dat", (int *)test_map1);

	_T_STEP(2);
	_T_OPER("map_load(\"Map1.dat\", &all_map_data[0*MAP_H*MAP_W])");
	map_load("Map1.dat", &all_map_data[0*MAP_H*MAP_W]);
	
	_T_STEP(3);
	_T_OPER("map_get(0, tmp_map)");
	map_get(0, tmp_map);
	
	_T_ASSERT(memcmp(test_map1, tmp_map, sizeof(test_map1)) == 0);
	_T_END_OK();
}

static void case_01_003(void)
{
	int tmp_map[MAP_H][MAP_W];
	point_t entrances[4];
	int entrance_total = 0;
	int filled_map1[MAP_H][MAP_W]=
	{
		{2,2,2,1,1,4,4,4,4,1,1,2,2,2},
		{2,1,1,1,1,1,4,1,1,1,1,1,1,1},
		{1,1,0,0,0,1,1,1,1,1,1,1,3,3},
		{1,1,0,1,0,1,0,0,0,0,0,0,0,0},
		{1,1,0,1,0,1,0,1,1,1,1,1,3,3},
		{0,0,0,1,0,1,0,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,0,2,2,4,4,4,1,1},
		{1,1,1,4,4,2,2,2,2,2,4,4,4,1},
		{1,1,4,4,2,2,2,2,2,2,2,4,4,4},
	};

	_T_CASE("MAP-01-003");
	_T_PURPOSE("validate map_fill(1 entrance).");
	_T_PRECOND("-");

	_T_STEP(1);
	_T_OPER("map_save(\"Map1.dat\", test_map1)");
	map_save("Map1.dat", (int *)test_map1);

	_T_STEP(2);
	_T_OPER("map_load(\"Map1.dat\", &all_map_data[0*MAP_H*MAP_W])");
	map_load("Map1.dat", &all_map_data[0*MAP_H*MAP_W]);
	
	_T_STEP(3);
	_T_OPER("map_fill(0, tmp_map, entrances, &entrance_total)");
	map_fill(0, tmp_map, entrances, &entrance_total);
	
	_T_ASSERT(memcmp(filled_map1, tmp_map, sizeof(filled_map1)) == 0);
	_T_ASSERT(entrance_total == 1);
	_T_ASSERT((entrances[0].x == 0)&&(entrances[0].y == 5));
	_T_END_OK();
}

static void case_01_004(void)
{
	int tmp_map[MAP_H][MAP_W];
	point_t entrances[4];
	int entrance_total = 0;
	int filled_map2[MAP_H][MAP_W]=
	{
		{0,0,0,1,1,1,4,4,1,1,1,0,0,0},
		{1,1,0,0,1,1,1,1,1,1,0,0,1,1},
		{1,1,1,0,0,1,1,1,1,0,0,1,1,1},
		{4,1,1,1,0,0,3,3,0,0,1,1,1,4},
		{4,4,1,1,1,0,0,0,0,1,1,1,4,4},
		{4,1,1,1,0,0,3,3,0,0,1,1,1,4},
		{1,1,1,0,0,1,1,1,1,0,0,1,1,1},
		{1,1,0,0,1,1,1,1,1,1,0,0,1,1},
		{0,0,0,1,1,1,4,4,1,1,1,0,0,0},
	};

	_T_CASE("MAP-01-004");
	_T_PURPOSE("validate map_fill(4 entrances).");
	_T_PRECOND("-");

	_T_STEP(1);
	_T_OPER("map_save(\"Map2.dat\", test_map2)");
	map_save("Map2.dat", (int *)test_map2);

	_T_STEP(2);
	_T_OPER("map_load(\"Map2.dat\", &all_map_data[1*MAP_H*MAP_W])");
	map_load("Map2.dat", &all_map_data[1*MAP_H*MAP_W]);
	
	_T_STEP(3);
	_T_OPER("map_fill(1, tmp_map, entrances, &entrance_total)");
	map_fill(1, tmp_map, entrances, &entrance_total);
	
	_T_ASSERT(memcmp(filled_map2, tmp_map, sizeof(filled_map2)) == 0);
	_T_ASSERT(entrance_total == 4);
	_T_ASSERT((entrances[0].x == 0)&&(entrances[0].y == 0));
	_T_ASSERT((entrances[1].x == 13)&&(entrances[1].y == 0));
	_T_ASSERT((entrances[2].x == 0)&&(entrances[2].y == 8));
	_T_ASSERT((entrances[3].x == 13)&&(entrances[3].y == 8));
	_T_END_OK();
}

static void case_01_005(void)
{
	int tmp_direction[MAP_H][MAP_W];
	int entrance_total = 0;
	int direction_1[MAP_H][MAP_W]=
	{
		{-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3},
		{-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3},
		{-3,-3,+1,+1,+2,-3,-3,-3,-3,-3,-3,-3,-3,-3},
		{-3,-3,-2,-3,+2,-3,+1,+1,+1,+1,+1,+1,+1, 0},
		{-3,-3,-2,-3,+2,-3,-2,-3,-3,-3,-3,-3,-3,-3},
		{+1,+1,-2,-3,+2,-3,-2,-3,-3,-3,-3,-3,-3,-3},
		{-3,-3,-3,-3,+1,+1,-2,-3,-3,-3,-3,-3,-3,-3},
		{-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3},
		{-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3},
	};

	_T_CASE("MAP-01-005");
	_T_PURPOSE("validate map_get_move_direction(1 entrance/1 end).");
	_T_PRECOND("-");

	_T_STEP(1);
	_T_OPER("map_save(\"Map1.dat\", test_map1)");
	map_save("Map1.dat", (int *)test_map1);

	_T_STEP(2);
	_T_OPER("map_load(\"Map1.dat\", &all_map_data[0*MAP_H*MAP_W])");
	map_load("Map1.dat", &all_map_data[0*MAP_H*MAP_W]);
	
	_T_STEP(3);
	_T_OPER("map_get_move_direction(0, tmp_direction)");
	map_get_move_direction(0, tmp_direction);
	
	_T_ASSERT(memcmp(direction_1, tmp_direction, sizeof(direction_1)) == 0);
	_T_END_OK();
}

static void case_01_006(void)
{
	int tmp_direction[MAP_H][MAP_W];
	int entrance_total = 0;
	int direction_2[MAP_H][MAP_W]=
	{
		{+1,+1,+2,-3,-3,-3,-3,-3,-3,-3,-3,+2,-1,-1},
		{-3,-3,+1,+2,-3,-3,-3,-3,-3,-3,+2,-1,-3,-3},
		{-3,-3,-3,+1,+2,-3,-3,-3,-3,+2,-1,-3,-3,-3},
		{-3,-3,-3,-3,+1,+2,-3,-3,+2,-1,-3,-3,-3,-3},
		{-3,-3,-3,-3,-3,+1, 0, 0,-1,-3,-3,-3,-3,-3},
		{-3,-3,-3,-3,+1,-2,-3,-3,-2,-1,-3,-3,-3,-3},
		{-3,-3,-3,+1,-2,-3,-3,-3,-3,-2,-1,-3,-3,-3},
		{-3,-3,+1,-2,-3,-3,-3,-3,-3,-3,-2,-1,-3,-3},
		{+1,+1,-2,-3,-3,-3,-3,-3,-3,-3,-3,-2,-1,-1},
	};

	_T_CASE("MAP-01-006");
	_T_PURPOSE("validate map_get_move_direction(4 entrances/2 ends).");
	_T_PRECOND("-");

	_T_STEP(1);
	_T_OPER("map_save(\"Map2.dat\", test_map2)");
	map_save("Map2.dat", (int *)test_map2);

	_T_STEP(2);
	_T_OPER("map_load(\"Map2.dat\", &all_map_data[1*MAP_H*MAP_W])");
	map_load("Map2.dat", &all_map_data[1*MAP_H*MAP_W]);
	
	_T_STEP(3);
	_T_OPER("map_get_move_direction(1, tmp_direction)");
	map_get_move_direction(1, tmp_direction);
	
	_T_ASSERT(memcmp(direction_2, tmp_direction, sizeof(direction_2)) == 0);
	_T_END_OK();
}

static void case_01_007(void)
{
	int entrance_total = 0;
	int ret;

	_T_CASE("MAP-01-007");
	_T_PURPOSE("validate map_is_in_range.");
	_T_PRECOND("-");

	_T_STEP(1);
	_T_OPER("ret = map_is_in_range(0, 0)");
	ret = map_is_in_range(0, 0);
	_T_ASSERT(ret == 1);

	_T_STEP(2);
	_T_OPER("ret = map_is_in_range(-1, 0)");
	ret = map_is_in_range(-1, 0);
	_T_ASSERT(ret == 0);

	_T_STEP(3);
	_T_OPER("ret = map_is_in_range(1, 0)");
	ret = map_is_in_range(1, 0);
	_T_ASSERT(ret == 1);

	_T_STEP(4);
	_T_OPER("ret = map_is_in_range(7, 0)");
	ret = map_is_in_range(7, 0);
	_T_ASSERT(ret == 1);

	_T_STEP(5);
	_T_OPER("ret = map_is_in_range(7, -1)");
	ret = map_is_in_range(7, -1);
	_T_ASSERT(ret == 0);

	_T_STEP(6);
	_T_OPER("ret = map_is_in_range(7, 1)");
	ret = map_is_in_range(7, 1);
	_T_ASSERT(ret == 1);

	_T_STEP(7);
	_T_OPER("ret = map_is_in_range(12, 0)");
	ret = map_is_in_range(12, 0);
	_T_ASSERT(ret == 1);

	_T_STEP(8);
	_T_OPER("ret = map_is_in_range(13, 0)");
	ret = map_is_in_range(13, 0);
	_T_ASSERT(ret == 1);

	_T_STEP(9);
	_T_OPER("ret = map_is_in_range(14, 0)");
	ret = map_is_in_range(14, 0);
	_T_ASSERT(ret == 0);

	_T_STEP(10);
	_T_OPER("ret = map_is_in_range(7, 7)");
	ret = map_is_in_range(7, 7);
	_T_ASSERT(ret == 1);

	_T_STEP(11);
	_T_OPER("ret = map_is_in_range(7, 8)");
	ret = map_is_in_range(7, 8);
	_T_ASSERT(ret == 1);

	_T_STEP(12);
	_T_OPER("ret = map_is_in_range(7, 9)");
	ret = map_is_in_range(7, 9);
	_T_ASSERT(ret == 0);
	
	_T_END_OK();
}

static void case_01_008(void)
{
	int ret;
	int map1[MAP_H][MAP_W]=
	{
		{2,2,2,1,1,4,4,4,4,1,1,2,2,2},
		{2,1,1,1,1,1,4,1,1,1,1,1,1,1},
		{1,1,0,0,0,1,1,1,1,1,1,1,3,3},
		{1,1,0,1,0,1,0,0,0,0,0,0,0,0},
		{1,1,0,1,0,1,0,1,1,1,1,1,3,3},
		{0,0,0,1,0,1,0,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,0,2,2,4,4,4,1,1},
		{1,1,1,4,4,2,2,2,2,2,4,4,4,1},
		{1,1,4,4,2,2,2,2,2,2,2,4,4,4},
	};

	_T_CASE("MAP-01-008");
	_T_PURPOSE("validate map_is_mining_enable.");
	_T_PRECOND("-");

	_T_STEP(1);
	_T_INFO("road-mine ae");
	_T_OPER("ret = map_is_mining_enable(1, 5, MINE_AE, map1)");
	ret = map_is_mining_enable(1, 5, MINE_AE, map1);
	_T_ASSERT(ret == 1);

	_T_STEP(2);
	_T_INFO("road-mine tk");
	_T_OPER("ret = map_is_mining_enable(1, 5, MINE_AT, map1)");
	ret = map_is_mining_enable(1, 5, MINE_AT, map1);
	_T_ASSERT(ret == 1);

	_T_STEP(3);
	_T_INFO("roadside-mine ae");
	_T_OPER("ret = map_is_mining_enable(1, 4, MINE_AE, map1)");
	ret = map_is_mining_enable(1, 4, MINE_AE, map1);
	_T_ASSERT(ret == 0);
	
	_T_STEP(4);
	_T_INFO("roadside-mine tk");
	_T_OPER("ret = map_is_mining_enable(1, 4, MINE_AT, map1)");
	ret = map_is_mining_enable(1, 4, MINE_AT, map1);
	_T_ASSERT(ret == 0);

	_T_STEP(5);
	_T_INFO("road-mine rs");
	_T_OPER("ret = map_is_mining_enable(1, 5, MINE_RS, map1)");
	ret = map_is_mining_enable(1, 5, MINE_RS, map1);
	_T_ASSERT(ret == 0);

	_T_STEP(6);
	_T_INFO("roadside-mine rs");
	_T_OPER("ret = map_is_mining_enable(3, 1, MINE_RS, map1)");
	ret = map_is_mining_enable(3, 1, MINE_RS, map1);
	_T_ASSERT(ret == 1);

	_T_STEP(7);
	_T_INFO("water-mine rs");
	_T_OPER("ret = map_is_mining_enable(4, 7, MINE_RS, map1)");
	ret = map_is_mining_enable(4, 7, MINE_RS, map1);
	_T_ASSERT(ret == 0);

	_T_STEP(8);
	_T_INFO("house-mine rs");
	_T_OPER("ret = map_is_mining_enable(12, 2, MINE_RS, map1)");
	ret = map_is_mining_enable(12, 2, MINE_RS, map1);
	_T_ASSERT(ret == 0);

	_T_STEP(9);
	_T_INFO("forest-mine rs");
	_T_OPER("ret = map_is_mining_enable(5, 7, MINE_RS, map1)");
	ret = map_is_mining_enable(5, 7, MINE_RS, map1);
	_T_ASSERT(ret == 0);
	
	_T_END_OK();
}

static void case_01_009(void)
{
	int ret;
	int map1[MAP_H][MAP_W]=
	{
		{2,2,2,1,1,4,4,4,4,1,1,2,2,2},
		{2,1,1,1,1,1,4,1,1,1,1,1,1,1},
		{1,1,0,0,0,1,1,1,1,1,1,1,3,3},
		{1,1,0,1,0,1,0,0,0,0,0,0,0,0},
		{1,1,0,1,0,1,0,1,1,1,1,1,3,3},
		{0,0,0,1,0,1,0,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,0,2,2,4,4,4,1,1},
		{1,1,1,4,4,2,2,2,2,2,4,4,4,1},
		{1,1,4,4,2,2,2,2,2,2,2,4,4,4},
	};

	_T_CASE("MAP-01-009");
	_T_PURPOSE("validate map_is_road_side.");
	_T_PRECOND("-");
	
	_T_STEP(1);
	_T_INFO("road side");
	_T_OPER("ret = map_is_road_side(0, 4, map1)");
	ret = map_is_road_side(0, 4, map1);
	_T_ASSERT(ret == 1);

	_T_STEP(2);
	_T_INFO("road side");
	_T_OPER("ret = map_is_road_side(0, 6, map1)");
	ret = map_is_road_side(0, 6, map1);
	_T_ASSERT(ret == 1);

	_T_STEP(3);
	_T_INFO("road side");
	_T_OPER("ret = map_is_road_side(1, 1, map1)");
	ret = map_is_road_side(1, 1, map1);
	_T_ASSERT(ret == 1);

	_T_STEP(4);
	_T_INFO("road side");
	_T_OPER("ret = map_is_road_side(5, 1, map1)");
	ret = map_is_road_side(5, 1, map1);
	_T_ASSERT(ret == 1);

	_T_STEP(5);
	_T_INFO("road side");
	_T_OPER("ret = map_is_road_side(5, 5, map1)");
	ret = map_is_road_side(5, 5, map1);
	_T_ASSERT(ret == 1);

	_T_STEP(6);
	_T_INFO("forest");
	_T_OPER("ret = map_is_road_side(5, 7, map1)");
	ret = map_is_road_side(5, 7, map1);
	_T_ASSERT(ret == 1);

	_T_STEP(7);
	_T_INFO("house");
	_T_OPER("ret = map_is_road_side(13, 2, map1)");
	ret = map_is_road_side(13, 2, map1);
	_T_ASSERT(ret == 1);

	_T_STEP(8);
	_T_INFO("entrance");
	_T_OPER("ret = map_is_road_side(0, 5, map1)");
	ret = map_is_road_side(0, 5, map1);
	_T_ASSERT(ret == 0);

	_T_STEP(8);
	_T_INFO("road");
	_T_OPER("ret = map_is_road_side(1, 5, map1)");
	ret = map_is_road_side(1, 5, map1);
	_T_ASSERT(ret == 0);

	_T_STEP(9);
	_T_INFO("not in range");
	_T_OPER("ret = map_is_road_side(-1, 5, map1)");
	ret = map_is_road_side(-1, 5, map1);
	_T_ASSERT(ret == 0);

	_T_STEP(10);
	_T_INFO("not in range");
	_T_OPER("ret = map_is_road_side(16, 9, map1)");
	ret = map_is_road_side(16, 9, map1);
	_T_ASSERT(ret == 0);
	
	_T_END_OK();
}

void test_map(void)
{
	int i;
	_T_INIT();

	case_01_001();
	case_01_002();
	case_01_003();
	case_01_004();
	case_01_005();
	case_01_006();
	case_01_007();
	case_01_008();
	case_01_009();
	
	for(i = 0; i < _T_CASE_TOTAL; i++){
		if(_T_CASE_RESULT(i).result == 1){
			printf("%s OK\n", _T_CASE_RESULT(i).case_id);
		}
		else{
			printf("%s NG\n", _T_CASE_RESULT(i).case_id);
		}
	}
}

