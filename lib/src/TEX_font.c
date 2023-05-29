#include "TEX_font.h"



TEX_Font TEX_FontCreate(const char *name, const char *path, int size)
{
	TEX_Font font = {NULL, name, size};
	font.font = TTF_OpenFont(path, size);
	return font;
}



void TEX_FontDestroy(TEX_Font font)
{
	TTF_CloseFont(font.font);
}