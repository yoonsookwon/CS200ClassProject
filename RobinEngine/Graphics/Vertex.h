#pragma once
#include "vector3.hpp"
#include "vector2.hpp"
//#include  <DirectXMath.h>
struct  Vertex
{
    Vertex():pos(0,0,0){}
    Vertex(float x, float y ,float z,float u, float v)
        : pos(x, y, 0), texCoord(u,v) {}

    //Vertex(float x, float y,  float u, float v)
    //    : pos2(x, y), texCoord(u, v) {}

    //DirectX::XMFLOAT3
    vector3<float> pos;
    //vector2<float> pos2;
    vector2<float> texCoord;
 //   DirectX::XMFLOAT2 texCoord;
};