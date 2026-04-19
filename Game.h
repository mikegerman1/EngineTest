#ifndef Game
#define Game
#include<stdint.h>
#include<stdlib.h>
#include"CpuGraphics.h"

typedef struct{
	uint64_t frame;
	image* buffer;
	image* next;
	uint16_t fps;
	Vec2 position;
	int maxParticles;
	Vec2* particles;
	int particleCount;
	float Xm;
	float Ym;
}GAME;

GAME* InitGame(int width,int height,int fps);

int Tick(GAME* game);





#endif
