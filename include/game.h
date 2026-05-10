#ifndef Game
#define Game
#include<stdint.h>
#include<stdlib.h>
#include"cpugraphics.h"
#include"vector.h"

#define HEIGHT 480
#define WIDTH 620
#define FRAMERATE 100
#define KEY_INPUT_PF 1

typedef struct{
	V3f* verts;
	int vertcount;
	V2i* edges;
	int edgecount;
}Mesh;

typedef struct{
	uint64_t frame;
	image* buffer;
	float Xm;
	float Ym;
	V2f Pos;
	int fps;
	int* keyi;
	unsigned char* keys;
	Mesh** models;
}GAME;

GAME* InitGame(int width,int height,int fps);

int Tick(GAME* game);





#endif
