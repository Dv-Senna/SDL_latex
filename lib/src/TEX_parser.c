#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL_image.h>

#include "SDL_latex.h"
#include "TEX_config.h"
#include "TEX_parser.h"
#include "TEX_hash.h"


SDL_Surface *parseWithOptimization(const char *latex);
SDL_Surface *parseWithoutOptimization(const char *latex, const char *filename);


SDL_Surface *TEX_ParseLaTeX(const char *latex, SDL_bool optimize)
{
	if (optimize)
		return parseWithOptimization(latex);
	
	return parseWithoutOptimization(latex, "equation");
}


SDL_bool doesFileExists(const char *path)
{
	FILE *file = fopen(path, "r");
	if (file == NULL)
		return SDL_FALSE;

	fclose(file);
	return SDL_TRUE;
}


SDL_Surface *parseWithOptimization(const char *latex)
{
	char hash[16];
	TEX_Hash(latex, hash);

	char imgFilePath[TEX_MAX_LATEX_FILE_PATH_SIZE];
	int res = snprintf(imgFilePath, TEX_MAX_LATEX_FILE_PATH_SIZE, "%s/%s.png", TEX_DEFAULT_GENERATION_FOLDER, hash);
	if (res == 0 || res > TEX_MAX_LATEX_FILE_SIZE)
	{
		TEX_SetError("TEX : Can't concatenate png file path");
		return NULL;
	}

	if (doesFileExists(imgFilePath))
		return IMG_Load(imgFilePath);

	return parseWithoutOptimization(latex, hash);
}



SDL_Surface *parseWithoutOptimization(const char *latex, const char *filename)
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

	char texFilePath[TEX_MAX_LATEX_FILE_PATH_SIZE];
	res = snprintf(texFilePath, TEX_MAX_LATEX_FILE_PATH_SIZE, "%s/%s.tex", TEX_DEFAULT_GENERATION_FOLDER, filename);
	if (res == 0 || res > TEX_MAX_LATEX_FILE_SIZE)
	{
		TEX_SetError("TEX : Can't concatenate tex file path");
		return NULL;
	}

	FILE *latexFile = fopen(texFilePath, "w");
	if (latexFile == NULL)
	{
		TEX_SetError("TEX : Can't open latex file as empty writable file");
		printf("%s\n", texFilePath);
		return NULL;
	}

	if (fprintf(latexFile, completedLatex) <= 0)
	{
		TEX_SetError("TEX : Can't write to latex file");
		fclose(latexFile);
		return NULL;
	}

	fclose(latexFile);

	char imgFilePath[TEX_MAX_LATEX_FILE_PATH_SIZE];
	res = snprintf(imgFilePath, TEX_MAX_LATEX_FILE_PATH_SIZE, "%s/%s.png", TEX_DEFAULT_GENERATION_FOLDER, filename);
	if (res == 0 || res > TEX_MAX_LATEX_FILE_SIZE)
	{
		TEX_SetError("TEX : Can't concatenate png file path");
		return NULL;
	}

	char pdfLatexEquation[TEX_MAX_PDFLATEX_COMMAND_SIZE];
	res = snprintf(pdfLatexEquation, TEX_MAX_PDFLATEX_COMMAND_SIZE, "pdflatex -output-directory=%s %s", TEX_DEFAULT_GENERATION_FOLDER, texFilePath);
	if (res == 0 || res > TEX_MAX_PDFLATEX_COMMAND_SIZE)
	{
		TEX_SetError("TEX : Can't concatenate png file path");
		return NULL;
	}

	char convertCommand[TEX_MAX_CONVERT_COMMAND_SIZE];
	res = snprintf(convertCommand, TEX_MAX_CONVERT_COMMAND_SIZE, "convert -density 300 %s/%s.pdf -quality 100 %s", TEX_DEFAULT_GENERATION_FOLDER, filename, imgFilePath);
	if (res == 0 || res > TEX_MAX_CONVERT_COMMAND_SIZE)
	{
		TEX_SetError("TEX : Can't concatenate png file path");
		return NULL;
	}

	system(pdfLatexEquation);
	system(convertCommand);

	return IMG_Load(imgFilePath);
}