#ifndef Game
#define Game
#include<stdint.h>
#include<stdlib.h>
#include"CpuGraphics.h"

typedef struct{
	uint64_t frame;
	image* buffer;
	float Xm;
	float Ym;
	V2f Pos;
}GAME;

GAME* InitGame(int width,int height,int fps);

int Tick(GAME* game);





#endif
