#ifndef _LIB_LIST_H_
#define _LIB_LIST_H_

#include <string.h>
#include <stdbool.h>

#define LIB_LIST_CONCAT2(s1, s2)	s1##s2
#define LIB_LIST_CONCAT(s1, s2)		LIB_LIST_CONCAT2(s1, s2)

#define LIST(name)													\
		 static void *LIB_LIST_CONCAT(name,_list) = NULL;				\
		 static lib_list_t name = (lib_list_t)&LIB_LIST_CONCAT(name,_list)

typedef void ** lib_list_t;

struct lib_list
{
	struct lib_list *next;
};

/*****************************************************************************************************/
/*
	Function	:	lib_list_head
	Description	:	Get a pointer to the first element of a list.
	Input		:	list - Pointer to the list need to be operated
	Output		:	none
	Return		:	the first element of the list
	Notes		:	none
*/
/*****************************************************************************************************/
static inline void *lib_list_head(lib_list_t list)
{
	return *list;
}

/*****************************************************************************************************/
/*
	Function	:	lib_list_copy
	Description	:	copying the src list's element to the dest list.
	Input		:	dest - Pointer to the list accepting the element.
					src  - Pointer to the list sending the element.
	Output		:	dest - Pointer to the list accepting the element.
	Return		:	none
	Notes		:	none
*/
/*****************************************************************************************************/
static inline void lib_list_copy(lib_list_t dest, lib_list_t src)
{
	*dest = *src;
}

/*****************************************************************************************************/
/*
	Function	:	lib_list_tail
	Description	:	Get the tail of a list.
	Input		:	list - Pointer to the list need to be operated
	Output		:	none
	Return		:	the last element of the list
	Notes		:	none
*/
/*****************************************************************************************************/
static inline void *lib_list_tail(lib_list_t list)
{
	struct lib_list *p;

	if(*list == NULL)
	{
		return NULL;
	}

	for(p = *list; p->next != NULL; p = p->next);

	return p;
}

/*****************************************************************************************************/
/*
	Function	:	lib_list_add
	Description	:	Add an element at the tail of a list
	Input		:	list - Pointer to the list need to be operated
					item - A pointer to the item to be added.
	Output		:	none
	Return		:	none
	Notes		:	none
*/
/*****************************************************************************************************/
static inline void lib_list_add(lib_list_t list, void *item)
{
	struct lib_list *p;

	((struct lib_list *)item)->next = NULL;

	p = lib_list_tail(list);
	if(p == NULL)
	{
		*list = item;
	}
	else
	{
		p->next = item;
	}
}

/*****************************************************************************************************/
/*
	Function	:	lib_list_push
	Description	:	Add an item at the head of a list.
	Input		:	list - Pointer to the list need to be operated
					item - A pointer to the item to be added.
	Output		:	none
	Return		:	none
	Notes		:	none
*/
/*****************************************************************************************************/
static inline void lib_list_push(lib_list_t list, void *item)
{
	((struct lib_list *)item)->next = *list;
	*list = item;
}

/*****************************************************************************************************/
/*
	Function	:	lib_list_chop
	Description	:	Remove the last element of a list.
	Input		:	list - Pointer to the list need to be operated
	Output		:	none
	Return		:	The removed element
	Notes		:	none
*/
/*****************************************************************************************************/
static inline void *lib_list_chop(lib_list_t list)
{
	struct lib_list *p, *r;

	if(*list == NULL)
	{
		return NULL;
	}
	if(((struct lib_list *)*list)->next == NULL)
	{
		p = *list;
		*list = NULL;
		return p;
	}

	for(p = *list; p->next->next != NULL; p = p->next);

	r = p->next;
	p->next = NULL;

	return r;
}

/*****************************************************************************************************/
/*
	Function	:	lib_list_pop
	Description	:	Remove the first element of a list.
	Input		:	list - Pointer to the list need to be operated
	Output		:	none
	Return		:	The removed element
	Notes		:	none
*/
/*****************************************************************************************************/
static inline void *lib_list_pop(lib_list_t list)
{
	void *temp = NULL;
	if(*list != NULL)
	{
		temp = *list;
		*list = ((struct lib_list *)*list)->next;
	}

	return temp;
}

/*****************************************************************************************************/
/*
	Function	:	lib_list_remove
	Description	:	Remove a specific element from a list.
	Input		:	list - Pointer to the list need to be operated
					item - Pointer to the element nend to be removed
	Output		:	none
	Return		:	none
	Notes		:	none
*/
/*****************************************************************************************************/
static inline void lib_list_remove(lib_list_t list, void *item)
{
	struct lib_list *p, *r;

	if(*list == NULL)
	{
		return;
	}

	r = NULL;
	for(p = *list; p != NULL; p = p->next)
	{
		if(p == item)
		{
			if(r == NULL)
			{
				/* First on list */
				*list = p->next;
			}
			else
			{
				/* Not first on list */
				r->next = p->next;
			}
			p->next = NULL;
			return;
		}
		r = p;
	}
}

/*****************************************************************************************************/
/*
	Function	:	lib_list_length
	Description	:	Get the length of a list.
	Input		:	list - Pointer to the list need to be operated
	Output		:	none
	Return		:	none
	Notes		:	none
*/
/*****************************************************************************************************/
int lib_list_length(lib_list_t list)
{
	struct lib_list *p;
	int n = 0;

	for(p = *list; p != NULL; p = p->next)
	{
		++n;
	}

	return n;
}

/*****************************************************************************************************/
/*
	Function	:	lib_list_insert
	Description	:	Insert an item at a specified position of a list. on the list.
	Input		:	list     - Pointer to the list need to be operated.
					previtem - The insert position, the new element will be inserted behand the previtem.
					newitem  - The pointer to the element will be inserted in the list.
	Output		:	none
	Return		: none
	Notes		: none
*/
/*****************************************************************************************************/
static inline void lib_list_insert(lib_list_t list, void *previtem, void *newitem)
{
	if(previtem == NULL)
	{
		lib_list_push(list, newitem);
	}
	else
	{
		((struct lib_list *)newitem)->next  = ((struct lib_list *)previtem)->next;
		((struct lib_list *)previtem)->next = newitem;
	}
}

/*****************************************************************************************************/
/*
	Function	:	lib_list_search
	Description	:	Search an item from a list.
	Input		:	list - Pointer to the list need to be operated.
					item - Pointer to the element need to be searched.
	Output		:	none
	Return		:	true  - The element exits in the list.
					false - The element doesn't exit in the list.
	Notes		:	none
*/
/*****************************************************************************************************/
static inline bool lib_list_search(lib_list_t list, void *item)
{
	struct lib_list *p;

	for(p = *list; p != NULL; p = p->next)
	{
		if(p == item)
			return true;
	}
	return false;
}

#endif
