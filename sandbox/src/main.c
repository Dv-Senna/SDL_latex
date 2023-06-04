#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_latex.h>


void handleError()
{
	printf("ERROR : %s\n", TEX_GetError());
	TEX_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(1);
}


int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		handleError();

	if (IMG_Init(IMG_INIT_PNG) == 0)
		handleError();

	if (TEX_Init() != 0)
		handleError();

	
	SDL_Window *window = SDL_CreateWindow("SDL_latex", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 16 * 70, 9 * 70, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	SDL_Surface *latexSurface = TEX_ParseLaTeX("E = mc^2", SDL_TRUE);
	if (latexSurface == NULL)
		handleError();
	SDL_Rect latexRect = {10, 20, latexSurface->w, latexSurface->h};
	SDL_Texture *latexTexture = SDL_CreateTextureFromSurface(renderer, latexSurface);
	SDL_FreeSurface(latexSurface);


	SDL_bool running = SDL_TRUE;
	SDL_Event event;


	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = SDL_FALSE;
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, latexTexture, NULL, &latexRect);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(latexTexture);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TEX_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}