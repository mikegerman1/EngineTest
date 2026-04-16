
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
	memcpy(game->next->data,buffer->data,buffer->x*buffer->y*sizeof(RGB));
	image* next = game->next;
	
	RGB white = CRGB(255,255,255);
	RGB black = CRGB(0,0,0);

	for (int i = 0 ;i<buffer->y;i++){
		for (int j = 0;j<buffer->x;j++){
			Uint8 counter = 0;
			for (int k = 0;k<9;k++){
				int row = k%3-1;
				int col = k/3-1;
				if (MINMAX(0,buffer->y-1,i+row)==i+row && MINMAX(0,buffer->x-1,j+col)==j+col && k!=4){
					if(GetPixelP(CVec2(j+col,i+row),buffer)->r==255){
						counter++;
					}
				}			
			}
			if (buffer->data[buffer->x*i+j].r ==255){
				if (counter<2){
					SetPixel(CVec2(j,i),black,next);
				}else if(counter>3){
					SetPixel(CVec2(j,i),black,next);
				}
			}else if(counter == 3){
				SetPixel(CVec2(j,i),white,next);
			}

		}
	}
	memcpy(buffer->data,next->data,sizeof(RGB)*buffer->x*buffer->y);	
	game->frame++;
	return 0;
}
