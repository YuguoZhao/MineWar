/**
	\addtogroup	DoubleLinkList
	declaration of double link list.
	\ingroup GameCore
*/
/*@{*/
/***************************************************************************//**
	\file		dlist.h
	\brief		declaration of double link list type and api.
	\author		XB
	\date		2016-7-1
	\version	1.0.1
*******************************************************************************/
#ifndef _DLIST_H
#define _DLIST_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
	\typedef int (*cmp_func_t)(void *p1, void *p2)
	condition match function.
	\param[in]	p1 :data1.
	\param[in]	p2 :data2.
	\return		0:match/1:not match.
*/
typedef int (*cmp_func_t)(void *p1, void *p2);

/**
	\struct _dlist_t
	node of double link list.
*/
struct _dlist_t{
	void *data;				/**< data pointer */
	struct _dlist_t *next;	/**< next pointer */
	struct _dlist_t *prev;	/**< prev pointer */
};

/**
	\typedef struct _dlist_t dlist_t
	node of double link list.
*/
typedef struct _dlist_t dlist_t;

/***************************************************************************//**
	\fn			int dlist_push_front(dlist_t **dlist, void *data)
	\brief		push data to front end.
	\param[in,out]	dlist :head pointer of list.
	\param[in]	data :data pointer.
*******************************************************************************/
int dlist_push_front(dlist_t **dlist, void *data);

/***************************************************************************//**
	\fn			int dlist_push_back(dlist_t **dlist, void *data)
	\brief		push data to back end.
	\param[in,out]	dlist :head pointer of list.
	\param[in]	data :data pointer.
*******************************************************************************/
int dlist_push_back(dlist_t **dlist, void *data);

/***************************************************************************//**
	\fn			int dlist_ins(dlist_t **dlist, void *data, void *data2, 
					cmp_func_t func)
	\brief		insert data before the match node.
	\param[in,out]	dlist :head pointer of list.
	\param[in]	data :data pointer.
	\param[in]	data2 :compare data pointer.
	\param[in]	func :condition match function.
	\return		0:failed/1:succeed.
*******************************************************************************/
int dlist_ins(dlist_t **dlist, void *data, void *data2, cmp_func_t func);

/***************************************************************************//**
	\fn			int dlist_del(dlist_t **dlist, void *data, cmp_func_t func)
	\brief		delete data which match condition.
	\param[in,out]	dlist :head pointer of list.
	\param[in]	data :compare data pointer.
	\param[in]	func :condition match function.
	\return		0:failed/1:succeed.
*******************************************************************************/
int dlist_del(dlist_t **dlist, void *data, cmp_func_t func);

/***************************************************************************//**
	\fn			void *dlist_find(dlist_t *dlist, void *data, cmp_func_t func)
	\brief		find data which match condition.
	\param[in]	dlist :head pointer of list.
	\param[in]	data :compare data pointer.
	\param[in]	func :condition match function.
	\return		data pointer. if not found, return NULL.
*******************************************************************************/
void *dlist_find(dlist_t *dlist, void *data, cmp_func_t func);

/***************************************************************************//**
	\fn			int dlist_get_size(dlist_t *dlist)
	\brief		get list length.
	\param[in]	dlist :head pointer of list.
	\return		length of list.
*******************************************************************************/
int dlist_get_size(dlist_t *dlist);

/***************************************************************************//**
	\fn			void dlist_clear(dlist_t **dlist)
	\brief		free all list, include data of every node.
	\param[in,out]	dlist :head pointer of list.
*******************************************************************************/
void dlist_clear(dlist_t **dlist);

#ifdef __cplusplus
}
#endif
#endif //_DLIST_H
/*@}*/
