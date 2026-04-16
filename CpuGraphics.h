#ifndef CPU_GRAPHICS
#define CPU_GRAPHICS

#define MAX(a,b) (((a)<(b)) ? (b):(a))
#define MIN(a,b) (((a)>(b)) ? (b):(a))
#define MINMAX(a,b,c) MIN(b,MAX(a,c))

#include<stdint.h>

typedef struct{
	int x,y;
}Vec2;
typedef struct{
	float x,y;
}FVec2;

typedef struct{
	float x,y,z;
}FVec3;

typedef struct{
    unsigned char r,g,b;
}RGB;

typedef struct{
    short depth;
    int x,y;
    RGB* data;
}image;

//Function declarations 

RGB CRGB(unsigned char r,unsigned char g,unsigned char b);
FVec3 CFVec3(float x,float y,float z);
Vec2 CVec2(int x, int y); RGB MixRGB(RGB color1,RGB color2,float factor);
FVec2 GetPosFactor(Vec2 position,image* buffer); 
RGB* GetPixelP(Vec2 position,image* buffer);
FVec2 CFVec2(float x,float y);

void SetPixels(Vec2* points,int count,RGB color,image* buffer);
void SetPixel(Vec2 postion, RGB color, image* buffer);
void DrawLine(Vec2 p1,Vec2 p2,RGB color, image* buffer);
void ClearImage(RGB color, image* buffer);

Vec2* Isometric(FVec3* verts,int vertcount,float scale,Vec2 offset,float ZAngle,float CamAngle);
image* InitImage(Vec2 size);
void OutputImage(char name[], image* buffer);

#endif
