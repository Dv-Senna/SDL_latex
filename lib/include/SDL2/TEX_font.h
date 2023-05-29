#ifndef SDL_LATEX_TEX_FONT_H
#define SDL_LATEX_TEX_FONT_H

#include <SDL2/SDL_ttf.h>


#ifdef __cplusplus
	extern "C" {
#endif


typedef struct 
{
	TTF_Font *font;
	const char *name;
	int size;
} TEX_Font;



TEX_Font TEX_FontCreate(const char *name, const char *path, int size);
void TEX_FontDestroy(TEX_Font font);


#ifdef __cplusplus
	}
#endif

#endif