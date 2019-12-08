/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#pragma once
#include "matrix4.hpp"
#include "vector4.hpp"
#include  "Model.h"
#include <DirectXMath.h>
using namespace DirectX;

class Camera
{
public:
    Camera();
    vector2<float> GetCameraPosition();

    const  matrix4<float>& GetViewMatrix() const;
    const matrix4<float> & GetProjectionMatrix() const;

    void SetPosition(float x, float y);

    void AdjustPosition(float x, float y);

    void AdjustRotation(float x, float y);
    void AdjustCameraZoom(float _zoom);


    void UpdateViewMatrix();
    float zoom = 0.3f;

private:

    vector2<float> pos;
    vector3<float> rot;
    matrix4<float> viewMatrix = MATRIX4::build_identity<float>();
    matrix4<float> projectionMatrix = MATRIX4::build_identity<float>();


};