#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <SDL3_image/SDL_image.h>

#include "SDL3_latex/SDL_latex.h"
#include "SDL3_latex/TEX_config.h"
#include "SDL3_latex/TEX_parser.h"
#include "SDL3_latex/TEX_hash.h"


SDL_Surface *parseWithOptimization(const char *latex, int size);
SDL_Surface *parseWithoutOptimization(const char *latex, const char *filename, int size);
void createFolderIfNotExists(const char *folder);


SDL_Surface *TEX_ParseLaTeX(const char *latex, bool optimize, int size)
{
	createFolderIfNotExists(TEX_DEFAULT_GENERATION_FOLDER);

	if (optimize)
		return parseWithOptimization(latex, size);
	
	return parseWithoutOptimization(latex, "equation", size);
}


bool doesFileExists(const char *path)
{
	FILE *file = fopen(path, "r");
	if (file == NULL)
		return false;

	fclose(file);
	return true;
}


void createFolderIfNotExists(const char *folder)
{
	struct stat st = {0};

	if (stat(folder, &st) == -1) {
	#ifdef TEX_WINDOWS
		mkdir(folder);
	#elif TEX_LINUX
		mkdir(folder, S_IRWXU | S_IRGRP);
	#endif
	}
}


SDL_Surface *parseWithOptimization(const char *latex, int size)
{
	char hash[17];
	TEX_Hash(latex, hash, size);


	char imgFilePath[TEX_MAX_LATEX_FILE_PATH_SIZE];
	int res = snprintf(imgFilePath, TEX_MAX_LATEX_FILE_PATH_SIZE, "%s/%s.png", TEX_DEFAULT_GENERATION_FOLDER, hash);
	if (res == 0 || res > TEX_MAX_LATEX_FILE_SIZE)
	{
		TEX_SetError("TEX : Can't concatenate png file path");
		return NULL;
	}

	if (doesFileExists(imgFilePath))
		return IMG_Load(imgFilePath);

	return parseWithoutOptimization(latex, hash, size);
}



SDL_Surface *parseWithoutOptimization(const char *latex, const char *filename, int size)
{
	static const char *latexPreambule1 = "\\documentclass[preview]{standalone}\n\
	\\usepackage{mathrsfs}\n\
	\\usepackage{slashed}\n\
	\\usepackage{amsmath}\n\
	\\usepackage{amssymb}\n\
	\\usepackage{mathtools}\n\
	\\usepackage{xcolor}\n\
	\\usepackage{fix-cm}\n\
	\n\
	\\begin{document}\n\
	\\fontsize{";
	static const char *latexPreambule2 = "}{2}\\selectfont{\n\
	\\color{white}\\[\n";
	static const char *latexPostEquation = "\n\\]}\n\\end{document}";
	char completedLatex[TEX_MAX_LATEX_FILE_SIZE];

	int res = snprintf(completedLatex, TEX_MAX_LATEX_FILE_SIZE, "%s%d%s%s%s", latexPreambule1, size, latexPreambule2, latex, latexPostEquation);
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
	res = snprintf(pdfLatexEquation, TEX_MAX_PDFLATEX_COMMAND_SIZE, "pdflatex -shell-escape -output-directory=%s %s", TEX_DEFAULT_GENERATION_FOLDER, texFilePath);
	if (res == 0 || res > TEX_MAX_PDFLATEX_COMMAND_SIZE)
	{
		TEX_SetError("TEX : Can't concatenate png file path");
		return NULL;
	}

	char convertCommand[TEX_MAX_CONVERT_COMMAND_SIZE];
	res = snprintf(convertCommand, TEX_MAX_CONVERT_COMMAND_SIZE, "magick convert -density 300 %s/%s.pdf -quality 100 -trim +repage %s", TEX_DEFAULT_GENERATION_FOLDER, filename, imgFilePath);
	if (res == 0 || res > TEX_MAX_CONVERT_COMMAND_SIZE)
	{
		TEX_SetError("TEX : Can't concatenate png file path");
		return NULL;
	}

	system(pdfLatexEquation);
	system(convertCommand);

	return IMG_Load(imgFilePath);
}
