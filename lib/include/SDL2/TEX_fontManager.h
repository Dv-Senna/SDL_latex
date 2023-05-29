#ifndef SDL_LATEX_TEX_FONT_MANAGER_H
#define SDL_LATEX_TEX_FONT_MANAGER_H

#include "TEX_list.h"

#ifndef TEX_CUSTOM_FONTS_PATHS
	#define TEX_MATH_FONT_PATH "fonts/latex/math/cmunti.ttf"
	#define TEX_MATHCAL_FONT_PATH "fonts/latex/mathcal/cmsy10.ttf"
	#define TEX_MATHSCR_FONT_PATH "fonts/latex/mathscr/rsfs10.ttf"
	#define TEX_CUSTOM_FONTS_PATHS
#endif


#ifndef TEX_DEFAULT_FONT_SIZE
	#define TEX_DEFAULT_FONT_SIZE 100
#endif


#ifdef __cplusplus
	extern "C" {
#endif


typedef struct 
{
	TEX_List *fonts;
} TEX_FontManager;


TEX_FontManager *TEX_FontManagerCreate();
void TEX_FontManagerDestroy(TEX_FontManager *fontManager);



#ifdef __cplusplus
	}
#endif

#endif