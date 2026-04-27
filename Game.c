#include<stdio.h>
#include<stdlib.h>
#include"./CpuGraphics.h"
#include<SDL3/SDL.h>
#include"./Game.h"
#include<string.h>
#include<math.h>
#include"vector.h"


float dist(V2i p1,V2i p2){
	return (float)sqrt(pow(p1.x - p2.x,2)+pow(p1.y - p2.y,2));
}

float randf(int seed){return fabsf((float)((30987-29893*seed*seed)%104532)/104532);}
RGBA func(int x,int y,int scale){
	int px = (x<0)?(x/scale)-1:x/scale;
	int py = (y<0)?(y/scale)-1:y/scale;
	float fx = (x<0)?1-(-(float)(x%scale)/scale):(float)(x%scale)/scale;
	float fy = (y<0)?1-(-(float)(y%scale)/scale):(float)(y%scale)/scale;
	
	float val = (fx*fy)*randf((px+1)*9+(py+1)*5)+(1-fx)*(1-fy)*randf(px*9+py*5) + (fx*(1-fy))*randf((px+1)*9+py*5)+((1-fx)*fy)*randf(px*9+(py+1)*5);
	return CRGBA(
					val*255,
					0,
					0,
					255
					);
}
GAME* InitGame(int width,int height,int fps){
	GAME* game = malloc(sizeof(GAME));
	*game = (GAME){
		.frame = 0,
		.buffer = InitImage(CV2i(width,height)),
		.fps = fps,
		.Pos = CV2f(0,0)
	};

	ClearImage(0xFFFFFFFF,game->buffer);

	return game;
}


int Tick(GAME* game){
	image* buffer = game->buffer;
	V2i Pos = CV2i(200,200);
	uint32_t Black = 0xff000000;
	uint32_t White = 0xffffffff;
	for (int i = 0 ; i<buffer->y; i++){
			for (int j = 0;j<buffer->x;j++){
				SetPixel(CV2i(j,i),func(j-game->Pos.x,i-game->Pos.y,1),buffer);
			}
	}
	game->Pos.x-= (float)((game->Xm-(buffer->x/2))/30);
	game->Pos.y-= (float)((game->Ym-(buffer->y/2))/30);

	game->frame++;
	return 0;
}
