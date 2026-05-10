#ifndef Game
#define Game
#include<stdint.h>
#include<stdlib.h>
#include"CpuGraphics.c"
#include"vector.c"

#define HEIGHT 480
#define WIDTH 620
#define FRAMERATE 30
#define KEY_INPUT_PF 50

typedef struct{
	V3f* verts;
	int vertcount;
	V2i* edges;
	int edgecount;
}model;

typedef struct{
	uint64_t frame;
	image* buffer;
	float Xm;
	float Ym;
	V2f Pos;
	int fps;
	int* keyi;
	unsigned char* keys;
	model** meshes;
}GAME;

GAME* InitGame(int width,int height,int fps);

int Tick(GAME* game);





#endif
