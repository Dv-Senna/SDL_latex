#ifndef SDL_LATEX_TEX_ERROR_H
#define SDL_LATEX_TEX_ERROR_H

#include <SDL2/SDL.h>


#ifdef __cplusplus
	extern "C" {
#endif


#define TEX_GetError SDL_GetError
#define TEX_SetError(msg) SDL_SetError(msg)


#ifdef __cplusplus
	}
#endif

#endif