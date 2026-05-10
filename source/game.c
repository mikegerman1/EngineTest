#include<stdio.h>
#include<stdlib.h>
#include"cpugraphics.h"
#include<SDL3/SDL.h>
#include"game.h"
#include<string.h>
#include<math.h>
#include"vector.h"



void isometric(Mesh* mesh,V3f offset3d, V2i offset,V2f angle,float scale,image* buffer){
	V2f ZV = {0,cosf(angle.y)};
	V2f YV = {cosf(angle.x), sinf(angle.y)*sinf(angle.x)};
	V2f XV = {-sinf(angle.x), sinf(angle.y)*cosf(angle.x)};

	V2i* points = malloc(sizeof(V2i)*mesh->vertcount);

	uint32_t color = CRGBA(255,255,100,255);
	for (int i = 0;i<mesh->vertcount;i++){
		V3f vector = addV3f(scaleV3f(mesh->verts[i],scale),offset3d);
		V2i pos = {
			ZV.x*vector.z + YV.x*vector.y + XV.x*vector.x + offset.x,
			ZV.y*vector.z + YV.y*vector.y + XV.y*vector.x + offset.y
		};
		SetPixel(pos,color,buffer);
		points[i] = pos;
	}
	
	for (int i=0;i<mesh->edgecount-1;i++){
			DrawLine(points[mesh->edges[i].x],points[mesh->edges[i].y],color,buffer);
	}
	free(points);
}

Mesh* LoadOBJ(char* path){
	printf("loadOBJ launched\n");
	Mesh* mesh = malloc(sizeof(Mesh));
	FILE* f = fopen(path,"r");
	if (f == NULL){
		printf("loading failed");
		fprintf(stderr,"unable to open %s\n",path);
		exit(1);
	}
	mesh->verts = (V3f*)malloc(100);
	mesh->edges = (V2i*)malloc(100);
	int vertcount = 0;
	int vertarrsize = 0;
	int edgecount = 0;
	int edgearrsize = 0;
	int maxbuffersize = 64;
	signed char* buffer = (signed char*)malloc(20000);
	float x,y,z;
	int linenum = 0;
	int finished  = 0;
	while(finished == 0){
		printf("\n-%d-\n",linenum);
		linenum++;
		signed char* pointer = buffer;
		if (fgets(pointer,10000,f) == NULL && fgetc(f) == EOF){
			printf("reached end\n");
			finished = 1;
			break;
		} 


		if (pointer == NULL) break;
		printf(pointer);

		//printf(pointer);

		if (pointer == NULL){
			continue;
		}else if (pointer[0]!=0 && pointer[0]=='v' && pointer[1]==' '){
			//adding verts
			printf("adding vert\n");
			if (vertcount == vertarrsize){
				vertarrsize += 100;
				mesh->verts = realloc(mesh->verts,vertarrsize*sizeof(V3f));
			}
			printf("vals read: %d\n", sscanf(pointer+1,"%f %f %f",&x,&y,&z));
			mesh->verts[vertcount] = CV3f(x,y,z);
			vertcount++;
			

		}else if (pointer[0]!=0 && pointer[0]=='l' && pointer[1]==' '){
			//adding edges
			int p1,p2;
			printf("parsing edges\n");
			if (edgecount == edgearrsize){
				edgearrsize += 100;
				mesh->edges = realloc(mesh->edges,edgearrsize*sizeof(V2i));
			}
			printf("vals read: %d\n", sscanf(pointer+1,"%d %d",&p1,&p2));
			mesh->edges[edgecount] = CV2i(p1-1,p2-1);
			edgecount++;
		}else if (pointer[0]!=0 && pointer[0]=='f' && pointer[1]==' '){
			//adding edges from faces
			int p1 = -1;
			int p2 = -1;
			while(1){
				printf("parsing edges edges");
				p1 = p2;
				int offset;	
				int readcount = sscanf(pointer+1,"%d/%*d/%*d%n",&p2,&offset);
				pointer = pointer+offset;
				if (p1 != -1 && p2 != -1 && readcount == 1){
					printf("condition met\n");	
					if (edgecount == edgearrsize){
						edgearrsize += 100;
						mesh->edges = realloc(mesh->edges,edgearrsize*sizeof(V2i));
					}
					mesh->edges[edgecount] = CV2i(p1-1,p2-1);
					edgecount++;
				}else if(readcount != 1){
					//mesh->edges[edgecount] = CV2i(mesh->edges[0].x,mesh->edges[edgecount-1].y);
					//edgecount;
					break;
				}
			}
		}
	}
	

	mesh->vertcount = vertcount;	
	mesh->edgecount = edgecount;
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
		.models = (Mesh**)malloc(sizeof(Mesh*)*2)
	};
	printf("start obj");
	game->models[0] = LoadOBJ("./wireframe.obj");
	
	printf("end obj");

	//inputs
    game->keys = malloc(KEY_INPUT_PF);
    game->keyi = malloc(sizeof(int)*KEY_INPUT_PF);
	memset(game->keys,0,KEY_INPUT_PF);
	memset(game->keyi,0,sizeof(int)*KEY_INPUT_PF);
	ClearImage(0xFFFFFFFF,game->buffer);	
	printf("game initialized\n");
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
	//end of game logic
	
	//writing to buffer
	image* buffer = game->buffer;	
	ClearImage(0xff000000,buffer);
	
	isometric(
					game->models[0],
					CV3f(0,0,0),CV2i(200,200),
					CV2f(game->frame/200.0,game->frame/100.0),
					-100,
					buffer
					);
	
	//end of writing to buffer
	game->frame++;
	return 0;
}
