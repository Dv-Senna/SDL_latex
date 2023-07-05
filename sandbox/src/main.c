#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_latex.h>


void handleError()
{
	printf("ERROR : %s\n", TEX_GetError());
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

	
	SDL_Window *window = SDL_CreateWindow("SDL_latex", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 16 * 70, 9 * 70, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	SDL_Surface *latexSurface = TEX_ParseLaTeX("E = m_0\\gamma c^2", SDL_TRUE, 7);
	if (latexSurface == NULL)
		handleError();
	SDL_Rect latexRect = {10, 20, latexSurface->w, latexSurface->h};
	SDL_Texture *latexTexture = SDL_CreateTextureFromSurface(renderer, latexSurface);
	SDL_FreeSurface(latexSurface);

	SDL_Surface *latexSurface2 = TEX_ParseLaTeX("R_{\\mu\\nu} - \\dfrac{1}{2}Rg_{\\mu\\nu} = 0", SDL_TRUE, 11);
	if (latexSurface2 == NULL)
		handleError();
	SDL_Rect latexRect2 = {50, 80, latexSurface2->w, latexSurface2->h};
	SDL_Texture *latexTexture2 = SDL_CreateTextureFromSurface(renderer, latexSurface2);
	SDL_FreeSurface(latexSurface2);


	SDL_bool running = SDL_TRUE;
	SDL_Event event;


	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
				running = SDL_FALSE;
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, latexTexture, NULL, &latexRect);
		SDL_RenderCopy(renderer, latexTexture2, NULL, &latexRect2);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(latexTexture2);
	SDL_DestroyTexture(latexTexture);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return 0;
}