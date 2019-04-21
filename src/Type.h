#ifndef _TYPE_H
#define	_TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

#ifndef BOOL
#define bool unsigned char
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)   sizeof(a)/sizeof(a[0])
#endif

typedef struct{
	int x;
	int y;
} point_t;

typedef struct _Msg_t
{
    int mid;
    int event;
    int p1;
    int p2;
    int p3;
    int p4;
} Msg_t;

#define TIME_UNIT		10		/*ms*/

#define _DEBUG_LOG
#ifdef _DEBUG_LOG
#define _LOGE(tag, format, ...)   printf("["tag"/E] "format, ##__VA_ARGS__)
#define _LOGI(tag, format, ...)   printf("["tag"/I] "format, ##__VA_ARGS__)
#define _LOGD(tag, format, ...)   printf("["tag"/D] "format, ##__VA_ARGS__)
#define _LOGW(tag, format, ...)   printf("["tag"/W] "format, ##__VA_ARGS__)
#define _LOGT(tag, format, ...)   printf("["tag"/T] "format, ##__VA_ARGS__)
#else
#define _LOGE(tag, format, ...)
#define _LOGI(tag, format, ...)
#define _LOGD(tag, format, ...)
#define _LOGW(tag, format, ...)
#define _LOGT(tag, format, ...)
#endif

#define DELETE_P(p) 		free(p)
#define NEW_T(t)			malloc(sizeof(t))

#ifdef _DEBUG_ASSERT
#define _ASSERT(exp)	\
	if(!(exp))	\
	{\
		printf("Assertion failed: %s, %d\n", __FILE__, __LINE__);\
		exit(-1);\
	}
#else
#define _ASSERT(exp)
#endif

#ifdef	_UNIT_TEST
#define	_T_CASE(id)				\
	printf("----------------------------------------\n");	\
	printf("<Case>         %s\n", id);	\
	strcpy(results[case_count].case_id, id);

#define	_T_PURPOSE(str)			printf("<Purpose>      %s\n", str)
#define	_T_PRECOND(str)			printf("<Precondition> %s\n", str)
#define	_T_PARAM(format, ...)	printf("<Param>        "format"\n", ##__VA_ARGS__)
#define	_T_RET(format, ...)		printf("<Ret>          "format"\n", ##__VA_ARGS__)
#define	_T_INFO(format, ...)	printf("<Info>         "format"\n", ##__VA_ARGS__)
#define	_T_OPER(str)			printf("<Operation>    %s\n", str)
#define	_T_STEP(n)				printf("<Step>         %d\n", n)
#define	_T_END_OK()				\
	printf("<Result>       OK\n");	\
	printf("----------------------------------------\n");	\
	results[case_count++].result = 1;
#define	_T_ASSERT(exp)			\
	if(!(exp)){	\
		printf("<Assert>       %s -> FALSE\n", #exp);	\
		printf("<Result>       NG\n");	\
		printf("----------------------------------------\n");	\
		results[case_count++].result = 0;	\
		return;	\
	}	\
	else{	\
		printf("<Assert>       %s -> TRUE\n", #exp);	\
	}
#define	_T_ASSERT_GOTO(exp,lable)	\
	if(!(exp)){	\
		printf("<Assert>       %s -> FALSE\n", #exp);	\
		printf("<Result>       NG\n");	\
		printf("----------------------------------------\n");	\
		results[case_count++].result = 0;	\
		goto lable;	\
	}	\
	else{	\
		printf("<Assert>       %s -> TRUE\n", #exp);	\
	}

typedef struct{
	char case_id[32];
	int result;
} result_t;

#ifdef _CASE_TOTAL
static result_t results[_CASE_TOTAL];
static int case_count = 0;

#define	_T_INIT()	\
	case_count = 0
#endif

#define	_T_CASE_TOTAL		case_count
#define _T_CASE_RESULT(i)	results[(i)]

#endif	//_UNIT_TEST
#endif	//_TYPE_H
