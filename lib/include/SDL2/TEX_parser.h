#ifndef SDL_LATEX_TEX_PARSER_H
#define SDL_LATEX_TEX_PARSER_H

#include <SDL2/SDL.h>

#ifdef __cplusplus
	extern "C" {
#endif


/// @brief Parse a string in LaTeX format (make sure you write `\ \ ` instead of `\ `) and convert it into an `SDL_Surface`
/// @param latex The string containing the LaTeX equation (make sure you write `\ \ ` instead of `\ `)
/// @param optimize `SDL_TRUE` to enable image convertion on first run, and then just image loading. `SDL_FALSE` to recompile it every time
/// @param size The size of the font in pt
/// @return The `SDL_Surface` generated, or `NULL` on error (see `TEX_GetError()`)
SDL_Surface *TEX_ParseLaTeX(const char *latex, SDL_bool optimize, int size);


#ifdef __cplusplus
	}
#endif

#endif