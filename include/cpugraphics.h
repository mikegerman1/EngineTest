#ifndef CPU_GRAPHICS
#define CPU_GRAPHICS

#define MAX(a,b) (((a)<(b)) ? (b):(a))
#define MIN(a,b) (((a)>(b)) ? (b):(a))
#define MINMAX(a,b,c) MIN(b,MAX(a,c))

#include<stdint.h>
#include"vector.h"

typedef struct{
	float x,y,z;
}FVec3;

typedef uint32_t RGBA;

typedef struct{
    short depth;
    int x,y;
    uint32_t* data;
}image;

//Function declarations 

uint32_t CRGBA(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
FVec3 CFVec3(float x,float y,float z);
uint32_t MixRGBA(uint32_t color1,uint32_t color2,float factor);
V2f GetPosFactor(V2i position,image* buffer); 
uint32_t* GetPixelP(V2i position,image* buffer);

void SetPixels(V2i* points,int count,uint32_t color,image* buffer);
void SetPixel(V2i postion, uint32_t color, image* buffer);
void DrawLine(V2i p1,V2i p2,uint32_t color, image* buffer);
void ClearImage(uint32_t color, image* buffer);

V2i* Isometric(FVec3* verts,int vertcount,float scale,V2i offset,float ZAngle,float CamAngle);
image* InitImage(V2i size);
void OutputImage(char name[], image* buffer);

#endif
