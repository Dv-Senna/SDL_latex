#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL_latex.h>
#include <SDL2/SDL.h>


void handleError()
{
	printf("ERROR : %s\n", TEX_GetError());
	TEX_Quit();
	exit(1);
}


int main(int argc, char *argv[])
{
	if (TEX_Init() != 0)
		handleError();

	

	TEX_Quit();

	return 0;
}