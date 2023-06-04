#ifndef SDL_LATEX_TEX_PARSER_H
#define SDL_LATEX_TEX_PARSER_H

#include <SDL2/SDL.h>


#define TEX_MAX_LATEX_FILE_SIZE 1024

#ifdef __cplusplus
	extern "C" {
#endif


SDL_Surface *TEX_ParseLaTeX(const char *latex, SDL_bool optimize);


#ifdef __cplusplus
	}
#endif

#endif