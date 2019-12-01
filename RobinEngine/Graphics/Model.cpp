#include "Model.h"
#include "vector2.hpp"

bool Model::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView * texture, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader)
{
    this->device = device;
    this->deviceContext = deviceContext;
    this->texture = texture;
    this->cb_vs_vertexshader = &cb_vs_vertexshader;

    float theta = 0;
    float posX = 0;
    float posY = 0;
    float radius = 0.7f;
    vector2<float> stores[] = { vector2(0.f,0.f) };

    //float store[] = {0};
    //={0.0f,0.0f};
   
    for (int i = 0; i <= 30; i++)
    {
        theta = ((DirectX::XM_2PI * i) / /*static_cast<float>(point_count))*/(30 - DirectX::XM_PIDIV2));
        posX = (radius * cos(theta)) + 2.0f;
        posY = (radius * sin(theta)) +0.7f;
        stores[i].x = posX;
        stores[i].y = posY;
    }

    Vertex v[] =
    {
        //Rectangle & texturing
        Vertex(-2.9f,  0.5f, -0.5f, 0.0f, 1.0f), //FRONT Bottom Left   - [0]
        Vertex(-2.9f,   1.2f, -0.5f, 0.0f, 0.0f), //FRONT Top Left      - [1]
        Vertex(-1.5f,   1.2f, -0.5f, 1.0f, 0.0f), //FRONT Top Right     - [2]
        Vertex(-1.5f,  0.5f, -0.5f, 1.0f, 1.0f), //FRONT Bottom Right   - [3]

        //Triangle
        Vertex(-0.75f, 0.25f,-0.5f, 0.0f, 1.0f), //[4]
        Vertex(0.0f, 1.45f, -0.5f, 0.0f, 0.0f),//[5]
        Vertex(0.75f,0.25f, -0.5f, 1.0f, 1.0f),//[6]

        //Circle

        Vertex(stores[0].x, stores[0].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[1].x, stores[1].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[2].x, stores[2].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[3].x, stores[3].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[4].x, stores[4].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[5].x, stores[5].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[6].x, stores[6].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[7].x, stores[7].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[8].x, stores[8].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[9].x, stores[9].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[10].x, stores[10].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[11].x, stores[11].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[12].x, stores[12].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[13].x, stores[13].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[14].x, stores[14].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[15].x, stores[15].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[16].x, stores[16].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[17].x, stores[17].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[18].x, stores[18].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[19].x, stores[19].y,-0.5f, 0.0f, 1.0f), //[7]


        Vertex(stores[20].x, stores[20].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[21].x, stores[21].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[22].x, stores[22].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[23].x, stores[23].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[24].x, stores[24].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[25].x, stores[25].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[26].x, stores[26].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[27].x, stores[27].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[28].x, stores[28].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[29].x, stores[29].y,-0.5f, 0.0f, 1.0f), //[7]
        Vertex(stores[30].x, stores[30].y,-0.5f, 0.0f, 1.0f), //[7]
    
    };

    //Load Vertex Data
    HRESULT hr = this->vertexBuffer.Initialize(this->device, v, ARRAYSIZE(v));
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create vertex buffer.");
        return false;
    }

    DWORD indices[] =
    {
        //Rectangle
        0,1,2,
        0,2,3,
        //Triangle
        4,5,6,
        //Circle
        7,8,9,
        10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,

        27,28,29,30,31,32,33,34,35,36,
    };

    //Load index data

    hr = this->indexBuffer.Initialize(this->device, indices, ARRAYSIZE(indices));
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create indices buffer");
        return hr;
    }
    this->SetPosition(0.0f, 0.0f, 0.0f);
    this->SetRotation(0.0f, 0.0f, 0.0f);
    this->UpdateWorldMatrix();
    return true;
}

void Model::SetTexture(ID3D11ShaderResourceView * texture)
{
    this->texture = texture;
}

void Model::Draw(const XMMATRIX & viewProjectionMatrix)
{
    //Update Constant buffer with WVP Matrix
    this->cb_vs_vertexshader->data.mat = this->worldMatrix * viewProjectionMatrix; //Calculate World-View-Projection Matrix
    this->cb_vs_vertexshader->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader->data.mat);

    this->cb_vs_vertexshader->ApplyChanges();
    this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader->GetAddressOf());


    this->deviceContext->PSSetShaderResources(0, 1, &this->texture); //Set Texture
    this->deviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
    UINT offset = 0;
    this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
    this->deviceContext->DrawIndexed(this->indexBuffer.BufferSize(), 0, 0); //Draw
}

void Model::UpdateWorldMatrix()
{
    this->worldMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z) * XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
    XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
    this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
    this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
    this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
    this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}

const XMVECTOR & Model::GetPositionVector() const
{
    return this->posVector;
}

const XMFLOAT3 & Model::GetPositionFloat3() const
{
    return this->pos;
}

const XMVECTOR & Model::GetRotationVector() const
{
    return this->rotVector;
}

const XMFLOAT3 & Model::GetRotationFloat3() const
{
    return this->rot;
}

void Model::SetPosition(const XMVECTOR & pos)
{
    XMStoreFloat3(&this->pos, pos);
    this->posVector = pos;
    this->UpdateWorldMatrix();
}

void Model::SetPosition(const XMFLOAT3 & pos)
{
    this->pos = pos;
    this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateWorldMatrix();
}

void Model::SetPosition(float x, float y, float z)
{
    this->pos = XMFLOAT3(x, y, z);
    this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateWorldMatrix();
}

void Model::AdjustPosition(const XMVECTOR & pos)
{
    this->posVector += pos;
    XMStoreFloat3(&this->pos, this->posVector);
    this->UpdateWorldMatrix();
}

void Model::AdjustPosition(const XMFLOAT3 & pos)
{
    this->pos.x += pos.y;
    this->pos.y += pos.y;
    this->pos.z += pos.z;
    this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateWorldMatrix();
}

void Model::AdjustPosition(float x, float y, float z)
{
    this->pos.x += x;
    this->pos.y += y;
    this->pos.z += z;
    this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateWorldMatrix();
}

void Model::SetRotation(const XMVECTOR & rot)
{
    this->rotVector = rot;
    XMStoreFloat3(&this->rot, rot);
    this->UpdateWorldMatrix();
}

void Model::SetRotation(const XMFLOAT3 & rot)
{
    this->rot = rot;
    this->rotVector = XMLoadFloat3(&this->rot);
    this->UpdateWorldMatrix();
}

void Model::SetRotation(float x, float y, float z)
{
    this->rot = XMFLOAT3(x, y, z);
    this->rotVector = XMLoadFloat3(&this->rot);
    this->UpdateWorldMatrix();
}

void Model::AdjustRotation(const XMVECTOR & rot)
{
    this->rotVector += rot;
    XMStoreFloat3(&this->rot, this->rotVector);
    this->UpdateWorldMatrix();
}

void Model::AdjustRotation(const XMFLOAT3 & rot)
{
    this->rot.x += rot.x;
    this->rot.y += rot.y;
    this->rot.z += rot.z;
    this->rotVector = XMLoadFloat3(&this->rot);
    this->UpdateWorldMatrix();
}

void Model::AdjustRotation(float x, float y, float z)
{
    this->rot.x += x;
    this->rot.y += y;
    this->rot.z += z;
    this->rotVector = XMLoadFloat3(&this->rot);
    this->UpdateWorldMatrix();
}

void Model::SetLookAtPos(XMFLOAT3 lookAtPos)
{
    //Verify that look at pos is not the same as cam pos. They cannot be the same as that wouldn't make sense and would result in undefined behavior.
    if (lookAtPos.x == this->pos.x && lookAtPos.y == this->pos.y && lookAtPos.z == this->pos.z)
        return;

    lookAtPos.x = this->pos.x - lookAtPos.x;
    lookAtPos.y = this->pos.y - lookAtPos.y;
    lookAtPos.z = this->pos.z - lookAtPos.z;

    float pitch = 0.0f;
    if (lookAtPos.y != 0.0f)
    {
        const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
        pitch = atan(lookAtPos.y / distance);
    }

    float yaw = 0.0f;
    if (lookAtPos.x != 0.0f)
    {
        yaw = atan(lookAtPos.x / lookAtPos.z);
    }
    if (lookAtPos.z > 0)
        yaw += XM_PI;

    this->SetRotation(pitch, yaw, 0.0f);
}

const XMVECTOR & Model::GetForwardVector()
{
    return this->vec_forward;
}

const XMVECTOR & Model::GetRightVector()
{
    return this->vec_right;
}

const XMVECTOR & Model::GetBackwardVector()
{
    return this->vec_backward;
}

const XMVECTOR & Model::GetLeftVector()
{
    return this->vec_left;
}