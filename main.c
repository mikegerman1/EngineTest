#include<stdio.h>
#include<stdlib.h>
#include"CpuGraphics.h"
#include<SDL3/SDL.h>
#include"Game.h"
#include<string.h>

#define HEIGHT 1000
#define WIDTH 1000

int main(){
    bool Finished = false;
    SDL_Init(SDL_INIT_VIDEO);
	//The main window
    SDL_Window* MainWindow = SDL_CreateWindow(
        "Game",
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL
    );
    if (MainWindow==NULL) {
        SDL_Log("unable to initialize window");
        return 1;
    }
	SDL_Surface* WindowSurface = SDL_GetWindowSurface(MainWindow);
	//Initializing game related structs
	GAME* MainGame = InitGame(WIDTH,HEIGHT,120);
	SDL_Surface* MainSurface = SDL_CreateSurface(WIDTH,HEIGHT,SDL_PIXELFORMAT_RGB24);
	MainSurface->pixels = MainGame->buffer->data;

	while (!Finished) {
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_EVENT_QUIT){
                Finished = true;
            }
        }
		Uint64 delta = SDL_GetTicks();
		SDL_GetMouseState(&MainGame->Xm,&MainGame->Ym);
		Tick(MainGame);
		SDL_BlitSurface(MainSurface,NULL,WindowSurface,NULL);
		SDL_UpdateWindowSurface(MainWindow);
		SDL_ShowWindow(MainWindow);
		delta = SDL_GetTicks() - delta;
		if (MainGame->fps != 0){
			SDL_Delay((delta > 1000/MainGame->fps) ? 0:1000/MainGame->fps-delta);
		}
		//printf("%d\n",delta);
    }

    return 0;
}

