#include <stdlib.h>

#include "TEX_error.h"
#include "TEX_list.h"


TEX_List *TEX_ListCreate(TEX_Font firstElement)
{
	TEX_List *list = malloc(sizeof(TEX_List));
	if (list == NULL)
	{
		TEX_SetError("TEX : can't allocate memory to create a TEX_List");
		return NULL;
	}

	list->font = firstElement;
	list->next = NULL;

	return list;
}



void TEX_ListDestroy(TEX_List *list)
{
	while (list != NULL)
	{
		TEX_List *next = list->next;
		free(list);
		list = next;
	}
}



size_t TEX_ListGetSize(TEX_List *list)
{
	size_t length = 0;

	while (list->next != NULL)
	{
		list = list->next;
		length++;
	}

	return length;
}



TEX_List *TEX_ListGetNthElement(TEX_List *list, size_t index)
{
	size_t current = 0;

	while (current < index)
	{
		if (list->next == NULL)
		{
			TEX_SetError("TEX : can't get the nth element of TEX_List because the list is too small");
			return NULL;
		}

		list = list->next;
		current++;
	}

	return list;
}



TEX_List *TEX_ListGetLastElement(TEX_List *list)
{
	while (list->next != NULL)
	{
		list = list->next;
	}

	return list;
}



TEX_List *TEX_ListRemoveNthElement(TEX_List *list, size_t index)
{
	if (index == 0)
		return TEX_ListPopFront(list);

	TEX_List *element = TEX_ListGetNthElement(list, index - 1);
	TEX_List *next = element->next->next;
	free(element->next);
	element->next = next;

	return list;
}



TEX_List *TEX_ListPushBack(TEX_List *list, TEX_Font element)
{
	TEX_List *last = TEX_ListGetLastElement(list);
	TEX_List *newElement = malloc(sizeof(TEX_List));
	if (newElement == NULL)
	{
		TEX_SetError("TEX : can't allocate memory to push back to TEX_List");
		return NULL;
	}

	newElement->font = element;
	newElement->next = NULL;
	last->next = newElement;

	return list;
}



TEX_List *Tex_ListPopBack(TEX_List *list)
{
	size_t length = TEX_ListGetSize(list);
	if (length == 0)
		return NULL;

	if (length == 1)
	{
		TEX_ListDestroy(list);
		return NULL;
	}

	TEX_List *element = TEX_ListGetNthElement(list, length - 1);
	free(element->next);
	element->next = NULL;

	return list;
}



TEX_List *TEX_ListPushFront(TEX_List *list, TEX_Font element)
{
	TEX_List *newElement = malloc(sizeof(TEX_List));
	if (newElement == NULL)
	{
		TEX_SetError("TEX : can't allocate memory to push front to TEX_List");
		return NULL;
	}

	newElement->font = element;
	newElement->next = list;

	return newElement;
}



TEX_List *TEX_ListPopFront(TEX_List *list)
{
	TEX_List *first = list->next;
	free(list);

	return first;
}



TEX_List *TEX_ListInsertNthElement(TEX_List *list, TEX_Font element, size_t index)
{
	TEX_List *before = TEX_ListGetNthElement(list, index - 1);
	TEX_List *next = before->next;

	TEX_List *newElement = malloc(sizeof(TEX_List));
	if (newElement == NULL)
	{
		TEX_SetError("TEX : can't allocate memory to insert into TEX_List");
		return NULL;
	}

	newElement->font = element;
	newElement->next = next;
	before->next = newElement;

	return list;
}


