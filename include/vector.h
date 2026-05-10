



#ifndef VECTOR_TYPES

#define VECTOR_TYPES
//V2i
typedef struct{
	int x;
	int	y;
}V2i;

V2i CV2i(int x,int y);
V2i addV2i(V2i V1,V2i V2);
V2i subV2i(V2i V1,V2i V2);
V2i multV2i(V2i V1,V2i V2);
V2i flipV2i(V2i V1);
V2i scaleV2i(V2i V1,float scale);

//V2f
typedef struct{
	float x;
	float y;
}V2f;

V2f CV2f(float x,float y);
V2f addV2f(V2f V1,V2f V2);
V2f subV2f(V2f V1,V2f V2);
V2f multV2f(V2f V1,V2f V2);
V2f flipV2f(V2f V1);
V2f scaleV2f(V2f V1,float scale);


typedef struct{
	float x;
	float y;
	float z;
}V3f;

V3f CV3f(float x,float y,float z);
V3f addV3f(V3f V1,V3f V2);
V3f subV3f(V3f V1,V3f V2);
V3f multV3f(V3f V1,V3f V2);
V3f scaleV3f(V3f V1,float scale);
#endif

