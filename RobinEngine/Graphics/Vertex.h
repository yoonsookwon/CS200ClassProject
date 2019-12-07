#pragma once
#include "vector3.hpp"
#include "vector2.hpp"
//#include  <DirectXMath.h>
struct  Vertex
{
    Vertex():pos(0,0,0){}
    Vertex(float x, float y ,float z,float u, float v)
        : pos(x, y, 0), texCoord(u,v) {}

  
    vector3<float> pos;
    vector2<float> texCoord;
};