
#define _UNIT_TEST
#define _CASE_TOTAL	32

#include "type.h"
#include "dlist.h"

typedef struct{
	int a;
} tdata_t;

static int cmp_func(tdata_t *v1, tdata_t *v2)
{
	if(v1->a == v2->a){
		return 0;
	}
	return 1;
}

static void case_01_001(void)
{
	dlist_t *list = NULL;
	void *data = NULL;
	int ret;

	_T_CASE("DLIST-01-001");
	_T_PURPOSE("validate dlist_push_front.");
	_T_PRECOND("list is empty.");

	_T_STEP(1);
	_T_PARAM("data=%p", data);

	_T_STEP(2);
	_T_OPER("ret = dlist_push_front(&list, data)");

	ret = dlist_push_front(&list, data);
	_T_ASSERT_GOTO(ret != 0, end);
	_T_ASSERT_GOTO(dlist_get_size(list) == 1, end);
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_01_002(void)
{
	dlist_t *list = NULL;
	tdata_t *data1 = NEW_T(tdata_t);
	tdata_t *data2 = NEW_T(tdata_t);
	tdata_t *pdata;
	int ret;
	dlist_t *p;
	int i;

	_T_CASE("DLIST-01-002");
	_T_PURPOSE("validate dlist_push_front.");
	_T_PRECOND("list is not empty.");

	_T_STEP(1);
	data1->a = 1;
	_T_PARAM("data1->a=%d", data1->a);
	_T_OPER("ret = dlist_push_front(&list, data1)");
	ret = dlist_push_front(&list, data1);
	
	_T_STEP(2);
	data2->a = 2;
	_T_PARAM("data2->a=%d", data2->a);
	_T_OPER("ret = dlist_push_front(&list, data2)");
	ret = dlist_push_front(&list, data2);
	
	_T_ASSERT_GOTO(ret != 0, end);
	_T_ASSERT_GOTO(dlist_get_size(list) == 2, end);
	
	p = list;
	i = 0;
	
	while(p != NULL){
		pdata = p->data;
		
		if(i == 0){
			_T_ASSERT_GOTO(pdata->a == 2, end);
		}

		i++;
		p = p->next;
	}
	
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_02_001(void)
{
	dlist_t *list = NULL;
	void *data = NULL;
	int ret;

	_T_CASE("DLIST-02-001");
	_T_PURPOSE("validate dlist_push_back.");
	_T_PRECOND("list is empty.");

	_T_STEP(1);
	_T_PARAM("data=%p", data);

	_T_STEP(2);
	_T_OPER("ret = dlist_push_back(&list, data)");

	ret = dlist_push_back(&list, data);
	_T_ASSERT_GOTO(ret != 0, end);
	_T_ASSERT_GOTO(dlist_get_size(list) == 1, end);
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_02_002(void)
{
	dlist_t *list = NULL;
	tdata_t *data1 = NEW_T(tdata_t);
	tdata_t *data2 = NEW_T(tdata_t);
	tdata_t *pdata;
	int ret;
	dlist_t *p;
	int i;

	_T_CASE("DLIST-02-002");
	_T_PURPOSE("validate dlist_push_back.");
	_T_PRECOND("list is not empty.");

	_T_STEP(1);
	data1->a = 1;
	_T_PARAM("data1->a=%d", data1->a);
	_T_OPER("ret = dlist_push_back(&list, data1)");
	ret = dlist_push_back(&list, data1);
	
	_T_STEP(2);
	data2->a = 2;
	_T_PARAM("dataa->a=%d", data2->a);
	_T_OPER("ret = dlist_push_back(&list, data2)");
	ret = dlist_push_back(&list, data2);
	
	_T_ASSERT_GOTO(ret != 0, end);
	_T_ASSERT_GOTO(dlist_get_size(list) == 2, end);
	
	p = list;
	i = 0;
	
	while(p != NULL){
		pdata = p->data;
		
		if(i == 1){
			_T_ASSERT_GOTO(pdata->a == 2, end);
		}

		i++;
		p = p->next;
	}
	
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_03_001(void)
{
	dlist_t *list = NULL;
	tdata_t *data1 = NEW_T(tdata_t);
	tdata_t *pdata;
	int ret;
	dlist_t *p;
	int i;

	_T_CASE("DLIST-03-001");
	_T_PURPOSE("validate dlist_ins.");
	_T_PRECOND("list is empty.");

	_T_STEP(1);
	data1->a = 1;
	_T_PARAM("data1->a=%d", data1->a);
	_T_STEP(2);
	_T_OPER("ret = dlist_ins(&list, NULL, data1, cmp_func)");
	ret = dlist_ins(&list, NULL, data1, cmp_func);
	
	_T_ASSERT_GOTO(ret != 0, end);
	_T_ASSERT_GOTO(dlist_get_size(list) == 1, end);
	
	p = list;
	i = 0;
	
	while(p != NULL){
		pdata = p->data;
		
		if(i == 0){
			_T_ASSERT_GOTO(pdata->a == 1, end);
		}

		i++;
		p = p->next;
	}
	
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_03_002(void)
{
	dlist_t *list = NULL;
	tdata_t *data1 = NEW_T(tdata_t);
	tdata_t *data2 = NEW_T(tdata_t);
	tdata_t *data3 = NEW_T(tdata_t);
	tdata_t *pdata;
	int ret;
	dlist_t *p;
	int i;

	_T_CASE("DLIST-03-002");
	_T_PURPOSE("validate dlist_ins.");
	_T_PRECOND("list is not empty, data match.");

	_T_STEP(1);
	data1->a = 1;
	_T_PARAM("data1->a=%d", data1->a);
	_T_OPER("ret = dlist_ins(&list, NULL, data1, cmp_func)");
	ret = dlist_ins(&list, NULL, data1, cmp_func);

	_T_STEP(2);
	data2->a = 1;
	data3->a = 3;
	_T_PARAM("dataa->a=%d", data1->a);
	_T_OPER("ret = dlist_ins(&list, data2, data3, cmp_func)");
	ret = dlist_ins(&list, data2, data3, cmp_func);
	
	_T_ASSERT_GOTO(ret != 0, end);
	_T_ASSERT_GOTO(dlist_get_size(list) == 2, end);
	
	p = list;
	i = 0;
	
	while(p != NULL){
		pdata = p->data;
		
		if(i == 0){
			_T_ASSERT_GOTO(pdata->a == 3, end);
		}

		i++;
		p = p->next;
	}
	
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_03_003(void)
{
	dlist_t *list = NULL;
	tdata_t *data1 = NEW_T(tdata_t);
	tdata_t *data2 = NEW_T(tdata_t);
	tdata_t *data3 = NEW_T(tdata_t);
	int ret;

	_T_CASE("DLIST-03-003");
	_T_PURPOSE("validate dlist_ins.");
	_T_PRECOND("list is not empty, data not match.");

	_T_STEP(1);
	data1->a = 1;
	_T_PARAM("data1->a=%d", data1->a);
	_T_OPER("ret = dlist_ins(&list, NULL, data1, cmp_func)");
	ret = dlist_ins(&list, NULL, data1, cmp_func);

	_T_STEP(2);
	data2->a = 2;
	data3->a = 3;
	_T_PARAM("dataa->a=%d", data2->a);
	_T_OPER("ret = dlist_ins(&list, data2, data3, cmp_func)");
	ret = dlist_ins(&list, data2, data3, cmp_func);
	
	_T_ASSERT_GOTO(ret == 0, end);
	_T_ASSERT_GOTO(dlist_get_size(list) == 1, end);
	
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_04_001(void)
{
	dlist_t *list = NULL;
	int ret;

	_T_CASE("DLIST-04-001");
	_T_PURPOSE("validate dlist_del.");
	_T_PRECOND("list is empty.");

	_T_STEP(1);
	_T_OPER("ret = dlist_del(&list, NULL, cmp_func)");
	ret = dlist_del(&list, NULL, cmp_func);
	
	_T_ASSERT(ret == 0);
	_T_ASSERT(dlist_get_size(list) == 0);
	
	_T_END_OK();
}

static void case_04_002(void)
{
	dlist_t *list = NULL;
	tdata_t *data1 = NEW_T(tdata_t);
	tdata_t *data2 = NEW_T(tdata_t);
	tdata_t *data3 = NEW_T(tdata_t);
	int ret;

	_T_CASE("DLIST-04-002");
	_T_PURPOSE("validate dlist_del.");
	_T_PRECOND("list is not empty, data match.");

	_T_STEP(1);
	data1->a = 1;
	_T_PARAM("data1->a=%d", data1->a);
	_T_OPER("ret = dlist_push_back(&list, data1)");
	ret = dlist_push_back(&list, data1);

	_T_STEP(2);
	data2->a = 2;
	
	_T_PARAM("dataa->a=%d", data2->a);
	_T_OPER("ret = dlist_push_back(&list, data2)");
	ret = dlist_push_back(&list, data2);

	_T_STEP(3);

	data3->a = 2;
	_T_PARAM("data3->a=%d", data3->a);
	_T_OPER("ret = dlist_del(&list, data3, cmp_func)");
	ret = dlist_del(&list, data3, cmp_func);
	
	_T_ASSERT_GOTO(ret != 0, end);
	_T_ASSERT_GOTO(dlist_get_size(list) == 1, end);
	
	_T_STEP(4);

	data3->a = 1;
	_T_PARAM("data3->a=%d", data3->a);
	_T_OPER("ret = dlist_del(&list, data3, cmp_func)");
	ret = dlist_del(&list, data3, cmp_func);
	
	_T_ASSERT_GOTO(ret != 0, end);
	_T_ASSERT_GOTO(dlist_get_size(list) == 0, end);
	
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_04_003(void)
{
	dlist_t *list = NULL;
	tdata_t *data1 = NEW_T(tdata_t);
	tdata_t *data2 = NEW_T(tdata_t);
	tdata_t *data3 = NEW_T(tdata_t);
	int ret;

	_T_CASE("DLIST-04-003");
	_T_PURPOSE("validate dlist_del.");
	_T_PRECOND("list is not empty, data not match.");

	_T_STEP(1);
	data1->a = 1;
	_T_PARAM("data1->a=%d", data1->a);
	_T_OPER("ret = dlist_push_back(&list, data1)");
	ret = dlist_push_back(&list, data1);

	_T_STEP(2);
	data2->a = 2;
	
	_T_PARAM("dataa->a=%d", data2->a);
	_T_OPER("ret = dlist_push_back(&list, data2)");
	ret = dlist_push_back(&list, data2);

	_T_STEP(3);

	data3->a = 3;
	_T_PARAM("data3->a=%d", data3->a);
	_T_OPER("ret = dlist_del(&list, data3, cmp_func)");
	ret = dlist_del(&list, data3, cmp_func);
	
	_T_ASSERT_GOTO(ret == 0, end);
	_T_ASSERT_GOTO(dlist_get_size(list) == 2, end);
	
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_05_001(void)
{
	dlist_t *list = NULL;
	void *ret;

	_T_CASE("DLIST-05-001");
	_T_PURPOSE("validate dlist_find.");
	_T_PRECOND("list is empty.");

	_T_STEP(1);
	_T_OPER("ret = dlist_find(list, NULL, cmp_func)");
	ret = dlist_find(list, NULL, cmp_func);
	
	_T_ASSERT(ret == NULL);
	
	_T_END_OK();
}

static void case_05_002(void)
{
	dlist_t *list = NULL;
	tdata_t *data1 = NEW_T(tdata_t);
	tdata_t *data2 = NEW_T(tdata_t);
	tdata_t *data3 = NEW_T(tdata_t);
	tdata_t *pdata;
	int ret;

	_T_CASE("DLIST-05-002");
	_T_PURPOSE("validate dlist_find.");
	_T_PRECOND("list is not empty, data match.");

	_T_STEP(1);
	data1->a = 1;
	_T_PARAM("data1->a=%d", data1->a);
	_T_OPER("ret = dlist_push_back(&list, data1)");
	ret = dlist_push_back(&list, data1);

	_T_STEP(2);
	data2->a = 2;
	
	_T_PARAM("dataa->a=%d", data2->a);
	_T_OPER("ret = dlist_push_back(&list, data2)");
	ret = dlist_push_back(&list, data2);

	_T_STEP(3);

	data3->a = 2;
	_T_PARAM("data3->a=%d", data3->a);
	_T_OPER("pdata = dlist_find(list, data3, cmp_func)");
	pdata = dlist_find(list, data3, cmp_func);
	
	_T_ASSERT_GOTO(pdata != NULL, end);
	_T_ASSERT_GOTO(pdata->a == 2, end);
	
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_05_003(void)
{
	dlist_t *list = NULL;
	tdata_t *data1 = NEW_T(tdata_t);
	tdata_t *data2 = NEW_T(tdata_t);
	tdata_t *data3 = NEW_T(tdata_t);
	tdata_t *pdata;
	int ret;

	_T_CASE("DLIST-05-003");
	_T_PURPOSE("validate dlist_find.");
	_T_PRECOND("list is not empty, data not match.");

	_T_STEP(1);
	data1->a = 1;
	_T_PARAM("data1->a=%d", data1->a);
	_T_OPER("ret = dlist_push_back(&list, data1)");
	ret = dlist_push_back(&list, data1);

	_T_STEP(2);
	data2->a = 2;
	
	_T_PARAM("dataa->a=%d", data2->a);
	_T_OPER("ret = dlist_push_back(&list, data2)");
	ret = dlist_push_back(&list, data2);

	_T_STEP(3);

	data3->a = 3;
	_T_PARAM("data3->a=%d", data3->a);
	_T_OPER("pdata = dlist_find(list, data3, cmp_func)");
	pdata = dlist_find(list, data3, cmp_func);
	
	_T_ASSERT_GOTO(pdata == NULL, end);
	
	_T_END_OK();
end:
	dlist_clear(&list);
}

static void case_06_001(void)
{
	dlist_t *list = NULL;

	_T_CASE("DLIST-06-001");
	_T_PURPOSE("validate dlist_clear.");
	_T_PRECOND("list is empty.");

	_T_STEP(1);
	_T_OPER("dlist_clear(&list)");
	dlist_clear(&list);
	
	_T_ASSERT(list == NULL);
	_T_ASSERT(dlist_get_size(list) == 0);
	
	_T_END_OK();
}

static void case_06_002(void)
{
	dlist_t *list = NULL;
	tdata_t *data = NEW_T(tdata_t);
	int ret;

	_T_CASE("DLIST-06-002");
	_T_PURPOSE("validate dlist_clear.");
	_T_PRECOND("list is not empty.");

	_T_STEP(1);
	data->a = 1;
	_T_PARAM("data->a=%d", data->a);
	_T_OPER("ret = dlist_push_back(&list, data)");
	ret = dlist_push_back(&list, data);
	_T_ASSERT(list != NULL);
	_T_ASSERT_GOTO(dlist_get_size(list) == 1, end);
	
	_T_STEP(2);
	_T_OPER("dlist_clear(&list)");
	dlist_clear(&list);
	
	_T_ASSERT(list == NULL);
	_T_ASSERT(dlist_get_size(list) == 0);
	
	_T_END_OK();
end:
	dlist_clear(&list);
}

void test_dlist(void)
{
	int i;
	_T_INIT();

	case_01_001();
	case_01_002();
	case_02_001();
	case_02_002();
	case_03_001();
	case_03_002();
	case_03_003();
	case_04_001();
	case_04_002();
	case_04_003();
	case_05_001();
	case_05_002();
	case_05_003();
	case_06_001();
	case_06_002();
	
	for(i = 0; i < _T_CASE_TOTAL; i++){
		if(_T_CASE_RESULT(i).result == 1){
			printf("%s OK\n", _T_CASE_RESULT(i).case_id);
		}
		else{
			printf("%s NG\n", _T_CASE_RESULT(i).case_id);
		}
	}
}
