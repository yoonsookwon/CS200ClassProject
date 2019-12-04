#pragma once
#include <DirectXMath.h>
#include "matrix4.hpp"

struct CB_VS_vertexshader
{
    matrix4<float> mat;
};

struct CB_PS_pixelshader
{
    float alpha = 1.0f;
};