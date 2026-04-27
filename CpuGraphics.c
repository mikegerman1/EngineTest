#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include"vector.h"
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


void SetPixels(V2i* points,int count,uint32_t color,image* buffer){
	for (int i = 0;i<count;i++){
		SetPixel(points[i],CRGBA(255,255,255,255),buffer);
	}
	return;
}


FVec3 CFVec3(float x,float y,float z) {return (FVec3){.x = x,.y = y,.z = z};}

uint32_t CRGBA(unsigned char r,unsigned char g,unsigned char b,unsigned char a) {
	return a<<24|b<<16|g<<8|r;
}

uint32_t* GetPixelP(V2i position,image* buffer){return buffer->data+(buffer->x*position.y+position.x);}

int GetPixelIndex(V2i position,image* buffer){return (buffer->x*position.y)+position.x;}

image* InitImage(V2i size){
	image* buffer = malloc(sizeof(image));
	*buffer = (image){
	.depth = 256,
	.x = size.x,
	.y = size.y,
	.data = malloc(sizeof(uint32_t)*size.x*size.y)};
	memset(buffer->data,0,sizeof(uint32_t)*size.x*size.y);
	
	return buffer;
}


void ClearImage(uint32_t color,image* buffer){
	for (uint32_t i = 0 ;i<buffer->x*buffer->y;i++){
		buffer->data[i] = color;
	}
}



V2f GetPosFactor(V2i position,image* buffer){
	float x = (float)(position.x - (buffer->x / 2)) / ((float)buffer->x/2);
	float y = (float)(position.y - (buffer->y / 2)) / ((float)buffer->y/2);
	return (V2f){.x = x, .y = y};
}


void DrawLine(V2i p1 , V2i p2,uint32_t color,image* buffer){
	int distY = p1.y - p2.y;
	int distX = p1.x - p2.x; 
	if (abs(distX)>(abs(distY))){
		for (int i=p1.x ; !(i==p2.x) ; i+=(distX<0)? 1:-1){
			int y = (int)(p1.y - abs(i-p1.x)*distY/abs(distX));
			if (y<0 || y>=buffer->y || i < 0 || i >= buffer->x) continue;
			SetPixel(CV2i(i,y),color,buffer);
		}
	}else{
		for (int i=p1.y ; !(i==p2.y); i+=(distY<0)? 1:-1){
			int x = (int)(p1.x - abs(i-p1.y)*distX/abs(distY));
			if (x<0 || x>=buffer->x || i<0 || i>buffer->y) continue;
			SetPixel(CV2i(x,i),color,buffer);
		}
	}
}

void SetPixel(V2i pos,uint32_t color, image* buffer){
	if (MINMAX(0,buffer->x-1,pos.x) != pos.x || MINMAX(0,buffer->y-1,pos.y) != pos.y) return;
	buffer->data[buffer->x*pos.y+pos.x] = color;
}


void OutputImage(char name[], image* buffer){
	FILE* f = fopen(name, "wb");
	fprintf(f, "P6\n%d %d\n255\n", buffer->x, buffer->y);
	for (int i = 0 ;i<buffer->y; i++){
		for (int j = 0;j<buffer->x;j++){
			fwrite(buffer->data + (i*buffer->x+j),3,1,f);
		}
	}

	fclose(f);
	return;
}

















