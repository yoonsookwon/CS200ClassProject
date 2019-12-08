/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#pragma once
#include "vector3.hpp"
#include "vector2.hpp"
struct  Vertex
{
    Vertex():pos(0,0,0){}
    Vertex(float x, float y ,float z,float u, float v)
        : pos(x, y, z), texCoord(u,v) {}

  
    vector3<float> pos;
    vector2<float> texCoord;
};