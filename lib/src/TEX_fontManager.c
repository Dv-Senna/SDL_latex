#include <stdlib.h>
#include <string.h>

#include "TEX_error.h"
#include "TEX_fontManager.h"


TEX_FontManager *TEX_FontManagerCreate()
{
	TEX_Font mathFont = TEX_FontCreate("math", TEX_MATH_FONT_PATH, TEX_DEFAULT_FONT_SIZE);
	if (mathFont.font == NULL)
		return NULL;

	TEX_Font mathcalFont = TEX_FontCreate("mathcal", TEX_MATHCAL_FONT_PATH, TEX_DEFAULT_FONT_SIZE);
	if (mathcalFont.font == NULL)
	{
		TEX_FontDestroy(mathFont);
		return NULL;
	}
	
	TEX_Font mathscrFont = TEX_FontCreate("mathscr", TEX_MATHSCR_FONT_PATH, TEX_DEFAULT_FONT_SIZE);
	if (mathscrFont.font == NULL)
	{
		TEX_FontDestroy(mathFont);
		TEX_FontDestroy(mathcalFont);
		return NULL;
	}


	TEX_FontManager *fontManager = malloc(sizeof(TEX_FontManager));
	if (fontManager == NULL)
	{
		TEX_FontDestroy(mathFont);
		TEX_FontDestroy(mathcalFont);
		TEX_FontDestroy(mathscrFont);
		TEX_SetError("TEX : Can't allocate memory for TEX_FontManager");
		return NULL;
	}


	fontManager->fonts = TEX_ListCreate(mathFont);
	fontManager->fonts = TEX_ListPushBack(fontManager->fonts, mathcalFont);
	fontManager->fonts = TEX_ListPushBack(fontManager->fonts, mathscrFont);
}



void TEX_FontManagerDestroy(TEX_FontManager *fontManager)
{

}


