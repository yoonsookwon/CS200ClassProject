#include "Camera.h"

Camera::Camera()
{
    this->UpdateViewMatrix();
}

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
    float fovRadians = (fovDegrees / 360.0f) * XM_2PI;
}

vector2<float> Camera::GetCameraPosition()
{
    vector2<float> result;
    result.x = pos.x;
    result.x = pos.y;
    return  result;
}

const  matrix4<float> & Camera::GetViewMatrix() const
{
    return this->viewMatrix;
}

const matrix4<float>& Camera::GetProjectionMatrix() const
{
    return this->projectionMatrix;
}

void Camera::SetPosition(float x, float y)
{
    this->pos = vector2<float>(x, y);
    this->UpdateViewMatrix();
}

void Camera::AdjustPosition(const vector4<float> & pos)
{
    this->UpdateViewMatrix();
}

void Camera::AdjustPosition(const vector3<float> & pos)
{
    this->pos.x += pos.y;
    this->pos.y += pos.y;
    this->UpdateViewMatrix();
}

void Camera::AdjustPosition(float x, float y, float z)
{
    this->pos.x += x;
    this->pos.y += y;
    this->UpdateViewMatrix();
}
void Camera::AdjustCameraZoom(float _zoom)
{
    this->zoom += zoom;
    this->UpdateViewMatrix();
}



void Camera::AdjustRotation(float x, float y, float z)
{
    this->rot.x += x;
    this->rot.y += y;
    this->UpdateViewMatrix();

}


void Camera::UpdateViewMatrix() //Updates view matrix and also updates the movement vectors
{
    matrix4<float> translation = MATRIX4::build_translation<float>(pos.x,pos.y);
    matrix4<float> rotation = MATRIX4::build_rotation<float>(rot.x);
    matrix4<float> scale = MATRIX4::build_scale<float>(zoom);

    //Rebuild view matrix
    this->viewMatrix = translation * rotation * scale;// scale * rotation * translation;
    this->viewMatrix = MATRIX4::transpose(this->viewMatrix);

}