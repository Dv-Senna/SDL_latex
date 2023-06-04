#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL_image.h>

#include "SDL_latex.h"
#include "TEX_parser.h"


SDL_Surface *TEX_ParseLaTeX(const char *latex, SDL_bool optimize)
{
	static const char *latexPreambule = "\\documentclass[preview]{standalone}\
	\\usepackage{mathrsfs}\n\
	\\usepackage{slashed}\n\
	\\usepackage{amsmath}\n\
	\\usepackage{amssymb}\n\
	\\usepackage{mathtools}\n\
	\\usepackage{xcolor}\n\
	\n\
	\\begin{document}\n\
	\\color{white}\\[\n";
	static const char *latexPostEquation = "\n\\]\n\\end{document}";
	char completedLatex[TEX_MAX_LATEX_FILE_SIZE];

	int res = snprintf(completedLatex, TEX_MAX_LATEX_FILE_SIZE, "%s%s%s", latexPreambule, latex, latexPostEquation);
	if (res == 0 || res > TEX_MAX_LATEX_FILE_SIZE)
	{
		TEX_SetError("TEX : Can't add preambule or end of file to equation");
		return NULL;
	}

	FILE *latexFile = fopen("equation.tex", "w");
	if (latexFile == NULL)
	{
		TEX_SetError("TEX : Can't open file equation.tex as empty writable file");
		return NULL;
	}

	if (fprintf(latexFile, completedLatex) <= 0)
	{
		TEX_SetError("TEX : Can't write to file equation.tex");
		fclose(latexFile);
		return NULL;
	}

	fclose(latexFile);

	system("pdflatex equation.tex");
	system("convert -density 300 equation.pdf -quality 100 equation.png");

	return IMG_Load("equation.png");
}
