#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
#include<string.h>
#include<time.h>

#include "./CpuGraphics.h"

#define MAX(a,b) (((a)<(b)) ? (b):(a))
#define MIN(a,b) (((a)>(b)) ? (b):(a))
#define MINMAX(a,b,c) MIN(b,MAX(a,c))


//math func
float function(float x){
	float scale = 20;
	x = (x)/130 + 3;
	float scaledX = x/(float)scale;
	return  (float)((x-1)*(x-2)*(x-3)*(x-4)*(x-5))*scale;
}

	
//START OF MAIN-----------------

//END OF MAIN-----------------------



//FUNCTIOIN DEFINITIONl


void SetPixels(Vec2* points,int count,RGB color,image* buffer){
	for (int i = 0;i<count;i++){
		SetPixel(points[i],CRGB(255,255,255),buffer);
	}
	return;
}


Vec2 CVec2(int x,int y){return (Vec2){.x = x, .y = y};}

FVec2 CFVec2(float x,float y) {return (FVec2){.x = x, .y = y};}
FVec3 CFVec3(float x,float y,float z) {return (FVec3){.x = x,.y = y,.z = z};}

RGB CRGB(unsigned char r,unsigned char g,unsigned char b) {return (RGB){.r=r, .g=g, .b=b};}

RGB* GetPixelP(Vec2 position,image* buffer){return buffer->data+(buffer->x*position.y+position.x);}

int GetPixelIndex(Vec2 position,image* buffer){return (buffer->x*position.y)+position.x;}

image* InitImage(Vec2 size){
	image* buffer = malloc(sizeof(image));
	*buffer = (image){
	.depth = 256,
	.x = size.x,
	.y = size.y,
	.data = malloc(sizeof(RGB)*size.x*size.y)};
	memset(buffer->data,0,sizeof(RGB)*size.x*size.y);
	
	return buffer;
}


void ClearImage(RGB color,image* buffer){
	if (color.r == color.b && color.r == color.g){
		memset(buffer->data,color.r,buffer->x*buffer->y*sizeof(RGB));

	}else{
		for (unsigned long long i = 0;i<buffer->x*buffer->y;i++){
			buffer->data[i]=color;
		}
	}return;
}



FVec2 GetPosFactor(Vec2 position,image* buffer){
	float x = (float)(position.x - (buffer->x / 2)) / ((float)buffer->x/2);
	float y = (float)(position.y - (buffer->y / 2)) / ((float)buffer->y/2);
	return (FVec2){.x = x, .y = y};
}


void DrawLine(Vec2 p1 , Vec2 p2,RGB color,image* buffer){
	int distY = p1.y - p2.y;
	int distX = p1.x - p2.x; 
	if (abs(distX)>(abs(distY))){
		for (int i=p1.x ; !(i==p2.x) ; i+=(distX<0)? 1:-1){
			int y = (int)(p1.y - abs(i-p1.x)*distY/abs(distX));
			if (y<0 || y>=buffer->y || i < 0 || i >= buffer->x) continue;
			SetPixel(CVec2(i,y),color,buffer);
		}
	}else{
		for (int i=p1.y ; !(i==p2.y); i+=(distY<0)? 1:-1){
			int x = (int)(p1.x - abs(i-p1.y)*distX/abs(distY));
			if (x<0 || x>=buffer->x || i<0 || i>buffer->y) continue;
			SetPixel(CVec2(x,i),color,buffer);
		}
	}return;
}

void SetPixel(Vec2 pos,RGB color, image* buffer){
	if (MINMAX(0,buffer->x-1,pos.x) != pos.x || MINMAX(0,buffer->y-1,pos.y) != pos.y) {return ;}
	buffer->data[buffer->x*pos.y+pos.x] = color;
	return ;
}


void OutputImage(char name[], image* buffer){
	FILE* f = fopen(name, "wb");
	fprintf(f, "P6\n%d %d\n255\n", buffer->x, buffer->y);
	if (sizeof(RGB) == 3){
		fwrite(buffer->data, buffer->x*buffer->y*3,1,f);
	} else {		
		for (unsigned long i = 0;i<buffer->x*buffer->y;i++){
			unsigned char rgbbuf[3] = {buffer->data[i].r,buffer->data[i].g,buffer->data[i].b};
			fwrite(&rgbbuf,3,1,f);
		}
		
	}

	fclose(f);
	return;
}

















