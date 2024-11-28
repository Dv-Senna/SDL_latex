#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_latex/SDL_latex.h>


void handleError()
{
	printf("ERROR : %s\n", TEX_GetError());
	IMG_Quit();
	SDL_Quit();
	exit(1);
}


int main(int argc, char *argv[])
{
	if (!SDL_Init(SDL_INIT_VIDEO))
		handleError();

	if (IMG_Init(IMG_INIT_PNG) == 0)
		handleError();

	
	SDL_Window *window = SDL_CreateWindow("SDL_latex", 16 * 70, 9 * 70, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);


	SDL_Surface *latexSurface = TEX_ParseLaTeX("E = m_0\\gamma c^2", true, 7);
	if (latexSurface == NULL)
		handleError();
	SDL_FRect latexRect = {10, 20, latexSurface->w, latexSurface->h};
	SDL_Texture *latexTexture = SDL_CreateTextureFromSurface(renderer, latexSurface);
	SDL_DestroySurface(latexSurface);

	SDL_Surface *latexSurface2 = TEX_ParseLaTeX("R_{\\mu\\nu} - \\dfrac{1}{2}Rg_{\\mu\\nu} = 0", true, 11);
	if (latexSurface2 == NULL)
		handleError();
	SDL_FRect latexRect2 = {50, 80, latexSurface2->w, latexSurface2->h};
	SDL_Texture *latexTexture2 = SDL_CreateTextureFromSurface(renderer, latexSurface2);
	SDL_DestroySurface(latexSurface2);


	bool running = true;
	SDL_Event event;


	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_KEY_DOWN)
				running = false;
		}

		SDL_RenderClear(renderer);

		SDL_RenderTexture(renderer, latexTexture, NULL, &latexRect);
		SDL_RenderTexture(renderer, latexTexture2, NULL, &latexRect2);

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
