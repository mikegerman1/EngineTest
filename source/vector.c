#include"vector.h"



V2i CV2i(int x,int y){return (V2i){x,y};}
V2i addV2i(V2i V1,V2i V2){return (V2i){V1.x+V2.x, V1.y+V2.y};}
V2i subV2i(V2i V1,V2i V2){return (V2i){V1.x-V2.x, V1.y-V2.y};}
V2i multV2i(V2i V1,V2i V2){return (V2i){V1.x*V2.x, V1.y*V2.y};}
V2i flipV2i(V2i V1){return (V2i){V1.y,V1.x};}
V2i scaleV2i(V2i V1,float scale){return (V2i){V1.x*scale,V1.y*scale};}


V2f CV2f(float x,float y){return (V2f){x,y};}
V2f addV2f(V2f V1,V2f V2){return (V2f){V1.x+V2.x, V1.y+V2.y};}
V2f subV2f(V2f V1,V2f V2){return (V2f){V1.x-V2.x, V1.y-V2.y};}
V2f multV2f(V2f V1,V2f V2){return (V2f){V1.x*V2.x, V1.y*V2.y};}
V2f flipV2f(V2f V1){return (V2f){V1.y,V1.x};}
V2f scaleV2f(V2f V1,float scale){return (V2f){V1.x*scale,V1.y*scale};}


V3f CV3f(float x,float y,float z){return (V3f){x,y,z};}
V3f addV3f(V3f V1,V3f V2){return (V3f){V1.x+V2.x, V1.y+V2.y, V1.z+V2.z};}
V3f subV3f(V3f V1,V3f V2){return (V3f){V1.x-V2.x, V1.y-V2.y, V1.z-V2.z};}
V3f multV3f(V3f V1,V3f V2){return (V3f){V1.x*V2.x, V1.y*V2.y, V1.z*V2.z};}
V3f scaleV3f(V3f V1,float scale){return (V3f){V1.x*scale,V1.y*scale,V1.z*scale};}
