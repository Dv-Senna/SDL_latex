#ifndef SDL_LATEX_TEX_LIST_H
#define SDL_LATEX_TEX_LIST_H

#include <inttypes.h>

#include "TEX_font.h"


#ifdef __cplusplus
	extern "C" {
#endif


typedef struct TEX_List_t
{
	TEX_Font font;
	struct TEX_List_t *next;
} TEX_List;


TEX_List *TEX_ListCreate(TEX_Font firstElement);
void TEX_ListDestroy(TEX_List *list);
size_t TEX_ListGetSize(TEX_List *list);
TEX_List *TEX_ListGetNthElement(TEX_List *list, size_t index);
TEX_List *TEX_ListGetLastElement(TEX_List *list);
TEX_List *TEX_ListRemoveNthElement(TEX_List *list, size_t index);
TEX_List *TEX_ListPushBack(TEX_List *list, TEX_Font element);
TEX_List *Tex_ListPopBack(TEX_List *list);
TEX_List *TEX_ListPushFront(TEX_List *list, TEX_Font element);
TEX_List *TEX_ListPopFront(TEX_List *list);
TEX_List *TEX_ListInsertNthElement(TEX_List *list, TEX_Font element, size_t index);



#ifdef __cplusplus
	}
#endif

#endif