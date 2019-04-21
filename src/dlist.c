#include "stdlib.h"
#include "type.h"
#include "dlist.h"

int dlist_push_front(dlist_t **dlist, void *data)
{
	int ret = 0;
	dlist_t *p = *dlist;
	dlist_t *q;

	q = malloc(sizeof(dlist_t));

	if(q != NULL)
	{
		q->data = data;
		q->next = p;
		q->prev = NULL;
		
		if(p != NULL)
		{
			p->prev = q;
		}
		
		*dlist = q;
		ret = 1;
	}
	
	return ret;
}

int dlist_push_back(dlist_t **dlist, void *data)
{
	int ret = 0;
	dlist_t *p = *dlist;
	dlist_t *q;

	if(p != NULL)
	{
		while(p->next != NULL)
		{
			p = p->next;
		}
		
		q = malloc(sizeof(dlist_t));

		if(q != NULL)
		{
			q->data = data;
			q->next = NULL;
			q->prev = p;
			p->next = q;
			ret = 1;
		}
	}
	else
	{
		p = malloc(sizeof(dlist_t));

		if(p != NULL)
		{
			p->data = data;
			p->next = NULL;
			p->prev = NULL;
			*dlist = p;
			ret = 1;
		}
	}
	
	return ret;
}

int dlist_ins(dlist_t **dlist, void *data, void *data2, cmp_func_t func)
{
	int ret = 0;
	dlist_t *p = *dlist;
	dlist_t *q;

	if(p != NULL)
	{
		while(p != NULL)
		{
			if(0 == func(p->data, data))
			{
				q = malloc(sizeof(dlist_t));

				if(q != NULL)
				{
					q->data = data2;
					q->next = p;
					q->prev = p->prev;
					p->prev = q;

					if(p == *dlist)
					{
						*dlist = q;
					}
					
					ret = 1;
				}
				
				break;
			}
			else
			{
				p = p->next;
			}
		}
	}
	else
	{
		p = malloc(sizeof(dlist_t));

		if(p != NULL)
		{
			p->data = data2;
			p->next = NULL;
			p->prev = NULL;
			*dlist = p;
			ret = 1;
		}
	}
	
	return ret;
}

int dlist_del(dlist_t **dlist, void *data, cmp_func_t func)
{
	int ret = 0;
	dlist_t *p = *dlist;
	dlist_t *q;

	while(p != NULL)
	{
		if(0 == func(p->data, data))
		{
			q = p->prev;
			
			if(q != NULL)
			{
				q->next = p->next;
			}
			else	//	first node
			{
				*dlist = p->next;
			}

			if(p->next != NULL)
			{
				p->next->prev = q;
			}
			else	//	last node
			{
			}
			
			free(p->data);
			free(p);
			ret = 1;
			
			break;
		}
		else
		{
			p = p->next;
		}
	}
	
	return ret;
}

void *dlist_find(dlist_t *dlist, void *data, cmp_func_t func)
{
	void *ret = NULL;
	dlist_t *p = dlist;

	while(p != NULL)
	{
		if(0 == func(p->data, data))
		{
			ret = p->data;
			
			break;
		}
		else
		{
			p = p->next;
		}
	}
	
	return ret;
}

int dlist_get_size(dlist_t *dlist)
{
	int ret = 0;
	dlist_t *p = dlist;

	while(p != NULL)
	{
		ret++;
		p = p->next;
	}
	
	return ret;
}

void dlist_clear(dlist_t **dlist)
{
	dlist_t *p = *dlist;
	dlist_t *q;

	while(p != NULL)
	{
		free(p->data);
		q = p;
		p = p->next;
		free(q);
	}

	*dlist = NULL;
}

