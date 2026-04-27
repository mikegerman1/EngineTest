#include"vector.h"

V2i CV2i(int x,int y){return (V2i){.x=x,.y=y};}
addV2i(V2i V1,V2i V2){return (V2i){.x=V1.x+V2i.x, .y=V1.y+V2.y};}
subV2i(V2i V1,V2i V2){return (V2i){.x=V1.x-V2i.x, .y=V1.y-V2.y};}
multV2i(V2i V1,V2i V2){return (V2i){.x=V1.x*V2i.x, .y=V1.y*V2.y};}
flipV2i(V2i V1){return (V2i){.x=V1.y,.y=V1.x};}

V2f CV2f(float x,float y){return (V2f){.x=x,.y=y};}
addV2f(V2i V1,V2i V2){return (V2i){.x=V1.x+V2i.x, .y=V1.y+V2.y};}
subV2f(V2i V1,V2i V2){return (V2i){.x=V1.x-V2i.x, .y=V1.y-V2.y};}
multV2f(V2i V1,V2i V2){return (V2i){.x=V1.x*V2i.x, .y=V1.y*V2.y};}
flipV2f(V2f V1){return (V2f){.x=V1.y,.y=V1.x};}
