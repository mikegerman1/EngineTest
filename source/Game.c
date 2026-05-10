#include<stdio.h>
#include<stdlib.h>
#include"cpugraphics.c"
#include<SDL3/SDL.h>
#include"game.c"
#include<string.h>
#include<math.h>
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

float dist(V2i p1,V2i p2){
	return (float)sqrt(pow(p1.x - p2.x,2)+pow(p1.y - p2.y,2));
}

void isometric(model* mesh,V3f offset3d, V2i offset,V2f angle,float scale,image* buffer){
	V2f ZV = {0,cos(angle.y)};
	V2f YV = {cos(angle.x), sin(angle.y)*sin(angle.x)};
	V2f XV = {-sin(angle.x), sin(angle.y)*cos(angle.x)};

	V2i* points = malloc(sizeof(V2i)*mesh->vertcount);

	for (int i = 0;i<mesh->vertcount;i++){
		V3f vector = addV3f(scaleV3f(mesh->verts[i],scale),offset3d);
		V2i pos = {
			ZV.x*vector.z + YV.x*vector.y + XV.x*vector.x + offset.x,
			ZV.y*vector.z + YV.y*vector.y + XV.y*vector.x + offset.y
		};
		SetPixel(pos,0xffffffff,buffer);
		points[i] = pos;
	}

	for (int i=0;i<mesh->edgecount;i++){
			DrawLine(points[mesh->edges[i].x],points[mesh->edges[i].y],0xffffffff,buffer);
	}
	free(points);
}

model* LoadModel(char* path){
	model* mesh = malloc(sizeof(model));
	FILE* f = fopen(path,"r");

	float x,y,z;
	fscanf(f,"%d",&mesh->vertcount);
	mesh->verts = malloc(sizeof(V3f)*mesh->vertcount);
	for (int i=0;i<mesh->vertcount;i++){
		fscanf(f,"%f %f %f",&x,&y,&z);
		mesh->verts[i] = (V3f){x,y,z};
	}

	
	int p1,p2;
	fscanf(f,"%d",&mesh->edgecount);
	mesh->edges = malloc(sizeof(V2i)*mesh->edgecount);
	for (int i=0;i<mesh->edgecount;i++){
		fscanf(f,"%d %d",&p1,&p2);
		mesh->edges[i] = (V2i){p1,p2};
	}
	fclose(f);
	return mesh;
}

GAME* InitGame(int width,int height,int fps){
	GAME* game = malloc(sizeof(GAME));
	*game = (GAME){
		.frame = 0,
		.buffer = InitImage(CV2i(width,height)),
		.fps = fps,
		.Pos = CV2f(0,0),
		.meshes = malloc(sizeof(model*)*2)
	};
	game->meshes[0] = LoadModel("./model");
	game->meshes[1] = LoadModel("./model2");

	//inputs
    game->keys = malloc(KEY_INPUT_PF);
    game->keyi = malloc(sizeof(int)*KEY_INPUT_PF);
	memset(game->keys,0,KEY_INPUT_PF);
	memset(game->keyi,0,sizeof(int)*KEY_INPUT_PF);
	ClearImage(0xFFFFFFFF,game->buffer);	
	return game;
}


int Tick(GAME* game){
	//static variables
	static float velocityZ = 0;
	static float posZ = 0;
	if (posZ>0){
		velocityZ -= 1;
	}else velocityZ = 0;
	//handling input	
	for(int i = 0;i<KEY_INPUT_PF;i++){
		if(game->keyi[i] == 0) break;
		if(game->keyi[i] == SDLK_SPACE && game->keys[i]==1){
			printf("space pressed");
			velocityZ = 10;
		}
	}
	memset(game->keyi,0,KEY_INPUT_PF);	
	//end of input handling
	
	//game logic

	posZ += velocityZ;
	posZ = (posZ>0)?posZ:0;
	int coldist = 180;
	int topcolpos = 240+sin(game->frame/30.0)*(240-coldist/2);
	//writing to buffer
	image* buffer = game->buffer;	
	ClearImage(0xff000000,buffer);
	//cube
	isometric(
					game->meshes[0],
					CV3f(0,0,0),
					CV2i(0,480-posZ),
					CV2f(game->frame/80.0,(posZ-240)/-480),
					0.5,
					buffer);
	//collumn
	

	isometric(
					game->meshes[1],
					CV3f(0,0,0),
					CV2i(310,topcolpos-coldist/2),
					CV2f(game->frame/50.0,(topcolpos-240)/480.0),
					-0.5,
					buffer);
	isometric(
					game->meshes[1],
					CV3f(0,0,0),
					CV2i(310,topcolpos+coldist/2),
					CV2f(game->frame/50.0,(topcolpos-240)/480.0),
					0.5,
					buffer);
	//end of writing to buffer
	game->frame++;
	return 0;
}
