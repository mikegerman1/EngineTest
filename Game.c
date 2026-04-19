
#include<stdio.h>
#include<stdlib.h>
#include"CpuGraphics.h"
#include<SDL3/SDL.h>
#include"Game.h"
#include<string.h>
#include<time.h>
#include<math.h>


GAME* InitGame(int width,int height,int fps){
	GAME* game = malloc(sizeof(GAME));
	*game = (GAME){
		.frame = 0,
		.buffer = InitImage(CVec2(width,height)),
		.next = InitImage(CVec2(width,height)),
		.fps = fps,
	};

	ClearImage(CRGB(0,0,0),game->buffer);

	for (int i = 0 ;i<game->buffer->y;i++){
		for (int j = 0;j<game->buffer->x;j++){
			SetPixel(CVec2(j,i),(rand()%2 == 1) ? CRGB(255,255,255):CRGB(0,0,0),game->buffer);
		}
	}
	return game;
}


int Tick(GAME* game){
	image* buffer = game->buffer;
	ClearImage(CRGB(249,92,192),buffer);
	RGB Black = CRGB(0,0,0);
	RGB White = CRGB(255,255,255);
	for (int i = 0;i<buffer->y;i++){
		for (int j = 0;j<buffer->x;j++){
			buffer->data[i*buffer->x+j] = (sqrt(pow(i-(int)game->Ym,2)+pow(j-(int)game->Xm,2))>50)? Black:White;
		}
	}

	game->frame++;
	return 0;
}
