#include "Camera.h"

Camera::Camera()
{
    this->pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
    this->posVector = XMLoadFloat3(&this->pos);
    this->rot = XMFLOAT3(0.0f,0.0f,0.0f);
    this->rotVector = XMLoadFloat3(&this->rot);
    UpdateViewMatrix();
}

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
    float fovRadians = (fovDegrees / 360.0f) * XM_2PI;
    this->projectionMatrix = XMMatrixPerspectiveFovLH(fovDegrees, aspectRatio, nearZ, farZ);

}

const XMMATRIX & Camera::GetViewMatrix() const
{
    return this->viewMatrix;
}

const XMMATRIX & Camera::GetProjectionMatrix() const
{
    return this->projectionMatrix;
}

const XMVECTOR & Camera::GetPositionVector() const
{
    return this->posVector;
}

const XMFLOAT3 & Camera::GetPositionFloat3() const
{
    return this->pos;
}

const XMVECTOR & Camera::GetRotationVector() const
{
    return this->rotVector;
}

const XMFLOAT3 & Camera::GetRotationFloat3() const
{
    return this->rot;
}

void Camera::SetPosition(const XMVECTOR & pos)
{
    XMStoreFloat3(&this->pos, pos);
    this->posVector = pos;
    this->UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y, float z)
{
    this->pos = XMFLOAT3(x, y, z);
    this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateViewMatrix();
}

void Camera::AdjustPosition(const XMVECTOR & pos)
{
    this->posVector += pos;
    XMStoreFloat3(&this->pos, this->posVector);
    this->UpdateViewMatrix();
}

void Camera::AdjustPosition(float x, float y, float z)
{
    this->pos.x += x;
    this->pos.y += y;
    this->pos.z += z;
    this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateViewMatrix();
}

void Camera::SetRotation(const XMVECTOR & rot)
{
    this->rotVector = rot;
    XMStoreFloat3(&this->rot, rot);
    this->UpdateViewMatrix();
}

void Camera::SetRotation(float x, float y, float z)
{
    this->rot = XMFLOAT3(x,y,z);
    this->rotVector = XMLoadFloat3(&this->rot);
    this->UpdateViewMatrix();
}

void Camera::AdjustRotation(const XMVECTOR & rot)
{
    this->rotVector += rot;
    XMStoreFloat3(&this->rot, this->rotVector);
    this->UpdateViewMatrix();
}

void Camera::AdjustRotation(float x, float y, float z)
{
    this->rot.x  += x;
    this->rot.y += y;
    this->rot.z += z;
    this->rotVector = XMLoadFloat3(&this->rot);
    this->UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
    //카메라 회전 매트릭스 계산
    XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
    //calculate unit vector of cam target based off camera forward value transformed by cam roatation matrix.
    XMVECTOR camTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, camRotationMatrix);

    //카메라의 현재위치에 의해 카메라의 offset을 적용
    camTarget += this->posVector;
    //현재 회전을 기반으로 up direction 계산
    XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, camRotationMatrix);
    //REbuild view matrix
    this->viewMatrix = XMMatrixLookAtLH(this->posVector, camTarget, upDir);
}
