#include<stdio.h>
#include<stdlib.h>
#include"cpugraphics.h"
#include<SDL3/SDL.h>
#include"game.h"
#include<string.h>


int main(){
	printf("debug start\n");
    bool Finished = false;
    SDL_Init(SDL_INIT_VIDEO);
	//The main window
    SDL_Window* MainWindow = SDL_CreateWindow(
        "Game",
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL
    );
	
	printf("debug window init\n");
    if (MainWindow==NULL) {
        SDL_Log("unable to initialize window");
        return 1;
    }
	SDL_Surface* WindowSurface = SDL_GetWindowSurface(MainWindow);
	//Initializing game related structs
	GAME* MainGame = InitGame(WIDTH,HEIGHT,FRAMERATE);
	SDL_Surface* MainSurface = SDL_CreateSurface(WIDTH,HEIGHT,SDL_PIXELFORMAT_RGBA32);
	MainSurface->pixels = MainGame->buffer->data;
	printf("debug applying surface\n");
	while (!Finished) {
		//handling events
        SDL_Event event;
		int eventcounter = 0;
		    while (SDL_PollEvent(&event)){
		        if (event.type == SDL_EVENT_QUIT) Finished = true;
				if (event.type == SDL_EVENT_KEY_DOWN && eventcounter != KEY_INPUT_PF){
					MainGame->keyi[eventcounter] = event.key.key;
					MainGame->keys[eventcounter] = 1;
				}
				if (event.type == SDL_EVENT_KEY_UP && eventcounter != KEY_INPUT_PF){
					MainGame->keyi[eventcounter] = event.key.key;
					MainGame->keys[eventcounter] = 0;
				}
			}
		
			eventcounter++;
		

		Uint64 delta = SDL_GetTicksNS();
		SDL_GetMouseState(&MainGame->Xm,&MainGame->Ym);
		//game tick
		Tick(MainGame);

		//updating window
		SDL_BlitSurface(MainSurface,NULL,WindowSurface,NULL);
		SDL_UpdateWindowSurface(MainWindow);
		SDL_ShowWindow(MainWindow);

		//framerate lock
		delta = SDL_GetTicksNS() - delta;
		if(MainGame->frame%100 == 0) printf("%d\n",1000000000/delta);
		if (MainGame->fps != 0){
			SDL_DelayNS((delta > 1000000000/MainGame->fps) ? 0:1000000000/MainGame->fps-delta);
		}
		}
    return 0;
}



