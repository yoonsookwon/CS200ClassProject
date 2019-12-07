#include "Model.h"
#include "vector2.hpp"

bool Model::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView * texture, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader, Model::MeshType MeshType)
{
    this->device = device;
    this->deviceContext = deviceContext;
    this->texture = texture;
    this->cb_vs_vertexshader = &cb_vs_vertexshader;
    this->scale = { 1.0f,1.0f };

    if (MeshType == Elipse)
    {
        float theta = 0;
        float posX = 0;
        float posY = 0;
        float radius = 0.7f;
        vector2<float> stores[21] = { vector2(0.f,0.f) };

        for (int i = 0; i <= 20; i++)
        {

            theta = ((MATHLIB_PI * i) / (20.f)) - (MATHLIB_PI / 2);
            posX = (radius * cos(theta))* 1.2f;//+2.0f;

            posY = (radius * sin(theta))*0.7f;//+0.7f;
            stores[i].x = posX;
            stores[i].y = posY;
        }


        Vertex v[] =
        {
            //Circle
            Vertex(stores[0].x, stores[0].y + radius,0.0f, 0.0f, 1.0f), //7
            Vertex(stores[0].x, stores[0].y,0.0f, 0.0f, 1.0f), //8
            Vertex(stores[1].x, stores[1].y,0.0f, 0.0f, 1.0f), //9


            Vertex(stores[1].x, stores[1].y ,0.0f, 0.0f, 1.0f),   //10
            Vertex(stores[2].x, stores[2].y, 0.0f , 0.0f, 1.0f),    //11


            Vertex(stores[2].x, stores[2].y ,0.0f, 0.0f, 1.0f),//12
            Vertex(stores[3].x, stores[3].y,0.0f, 0.0f, 1.0f), //13

            Vertex(stores[3].x, stores[3].y ,0.0f, 0.0f, 1.0f),//14
            Vertex(stores[4].x, stores[4].y, 0.0f, 0.0f, 1.0f), //15

            Vertex(stores[4].x, stores[4].y ,0.0f, 0.0f, 1.0f),//16
            Vertex(stores[5].x, stores[5].y, 0.0f, 0.0f, 1.0f), //17

            Vertex(stores[5].x, stores[5].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[6].x, stores[6].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[6].x, stores[6].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[7].x, stores[7].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[7].x, stores[7].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[8].x, stores[8].y ,0.0f, 0.0f, 1.0f),

            Vertex(stores[8].x, stores[8].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[9].x, stores[9].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[9].x, stores[9].y , 0.0f, 0.0f, 1.0f),
            Vertex(stores[10].x, stores[10].y,0.0f, 0.0f, 1.0f),

            Vertex(stores[10].x, stores[10].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[11].x, stores[11].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[11].x, stores[11].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[12].x, stores[12].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[12].x, stores[12].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[13].x, stores[13].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[13].x, stores[13].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[14].x, stores[14].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[14].x, stores[14].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[15].x, stores[15].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[15].x, stores[15].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[16].x, stores[16].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[16].x, stores[16].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[17].x, stores[17].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[17].x, stores[17].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[18].x, stores[18].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[18].x, stores[18].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[19].x, stores[19].y, 0.0f, 0.0f, 1.0f),

            Vertex(stores[19].x, stores[19].y ,0.0f, 0.0f, 1.0f),
            Vertex(stores[20].x, stores[20].y, 0.0f, 0.0f, 1.0f),//47

            /////////////////////////////////////////////half

            Vertex(stores[0].x, stores[0].y, 0.0f, 0.0f, 1.0f), //48
            Vertex(-stores[1].x, stores[1].y,0.0f, 0.0f, 1.0f), //49


            Vertex(-stores[1].x, stores[1].y ,0.0f, 0.0f, 1.0f),   //10
            Vertex(-stores[2].x, stores[2].y, 0.0f, 0.0f, 1.0f),    //11


            Vertex(-stores[2].x, stores[2].y ,0.0f, 0.0f, 1.0f),//12
            Vertex(-stores[3].x, stores[3].y, 0.0f, 0.0f, 1.0f), //13

            Vertex(-stores[3].x, stores[3].y ,0.0f, 0.0f, 1.0f),//14
            Vertex(-stores[4].x, stores[4].y, 0.0f, 0.0f, 1.0f), //15

            Vertex(-stores[4].x, stores[4].y ,0.0f, 0.0f, 1.0f),//16
            Vertex(-stores[5].x, stores[5].y, 0.0f, 0.0f, 1.0f), //17

            Vertex(-stores[5].x, stores[5].y ,0.0f , 0.0f, 1.0f),
            Vertex(-stores[6].x, stores[6].y, 0.0f , 0.0f, 1.0f),

            Vertex(-stores[6].x, stores[6].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[7].x, stores[7].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[7].x, stores[7].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[8].x, stores[8].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[8].x, stores[8].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[9].x, stores[9].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[9].x, stores[9].y , 0.0f, 0.0f, 1.0f),
            Vertex(-stores[10].x, stores[10].y,0.0f, 0.0f, 1.0f),

            Vertex(-stores[10].x, stores[10].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[11].x, stores[11].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[11].x, stores[11].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[12].x, stores[12].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[12].x, stores[12].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[13].x, stores[13].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[13].x, stores[13].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[14].x, stores[14].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[14].x, stores[14].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[15].x, stores[15].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[15].x, stores[15].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[16].x, stores[16].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[16].x, stores[16].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[17].x, stores[17].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[17].x, stores[17].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[18].x, stores[18].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[18].x, stores[18].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[19].x, stores[19].y, 0.0f, 0.0f, 1.0f),

            Vertex(-stores[19].x, stores[19].y ,0.0f, 0.0f, 1.0f),
            Vertex(-stores[20].x, stores[20].y, 0.0f, 0.0f, 1.0f),
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
            //Circle
            0,1,2,
            0,2,3,
            0,3,4,
            0,4,5,
            0,5,6,
            0,6,7,
            0,7,8,
            0,8,9,
            0,9,10,
            0,10,11,
            0,11,12,
            0,12,13,
            0,13,14,
            0,14,15,
            0,15,16,
            0,16,17,
            0,17,18,
            0,18,19,
            0,19,20,
            0,20,21,
            0,21,22,
            0,22,23,
            0,23,24,
            0,24,25,
            0,25,26,
            0,26,27,
            0,27,28,
            0,28,29,
            0,29,30,
            0,30,31,
            0,31,32,
            0,32,33,
            0,33,34,
            0,34,35,
            0,35,36,
            0,36,37,
            0,37,38,
            0,38,39,

            ////////
            0,39,40,
            0,40,41,
            0,41,42,
            0,42,43,
            0,43,44,
            0,44,45,

            0,45,46,
            0,46,47,
            0,47,48,
            0,48,49,
            0,49,50,
            0,50,51,
            0,51,52,
            0,52,53,
            0,53,54,
            0,54,55,
            0,55,56,
            0,56,57,
            0,57,58,
            0,58,59,
            0,59,60,
            0,60,61,
            0,61,62,
            0,62,63,
            0,63,64,
            0,64,65,
            0,65,66,
            0,66,67,
            0,67,68,
            0,68,69,
            0,69,70,
            0,70,71,
            0,71,72,
            0,72,73,
            0,73,74,
            0,74,75,
            0,75,76,
            0,76,77,
            0,77,78,
            0,78,79,
            0,79,80,

        };

        //Load index data

        hr = this->indexBuffer.Initialize(this->device, indices, ARRAYSIZE(indices));
        if (FAILED(hr))
        {
            ErrorLogger::Log(hr, "Failed to create indices buffer");
            return hr;
        }
      //  this->SetPosition(0.0f, 0.0f, 0.0f);
       // this->SetRotation(0.0f, 0.0f, 0.0f);
    }
    else if (MeshType == Rectangle) {
      
        Vertex v[] = {
                // Rectangle & texturing
                Vertex(-0.7f, -0.5f, 0.0f, 1.0f, 1.0f), //FRONT Bottom Left
                Vertex(-0.7f, 0.5f, 0.0f, 1.0f, 0.0f), //FRONT Top Left    
                Vertex(0.7f, 0.5f, 0.0f, 0.0f, 0.0f), //FRONT Top Right   
                Vertex(0.7f, -0.5f, 0.0f, 0.0f, 1.0f), //FRONT Top Right
            };
        HRESULT hr = this->vertexBuffer.Initialize(this->device, v, ARRAYSIZE(v));
        if (FAILED(hr))
        {
            ErrorLogger::Log(hr, "Failed to create vertex buffer.");
            return false;
        }
        DWORD indices[] =
        { 0,1,2,
          0,2,3

        };
        hr = this->indexBuffer.Initialize(this->device, indices, ARRAYSIZE(indices));
        if (FAILED(hr))
        {
            ErrorLogger::Log(hr, "Failed to create indices buffer");
            return hr;
        }
        this->translation = { -2.0f, 1.2f };
    }
    else if (MeshType == Triangle)
    {
        Vertex v[] = {
            //Triangle
            Vertex(1.25f, 0.25f, 0.0f, 0.0f, 1.0f),
            Vertex(2.0f, 1.45f, 0.0f, 0.0f, 0.0f),
            Vertex(2.75f, 0.25f, 0.0f, 1.0f, 1.0f),
        };
        HRESULT hr = this->vertexBuffer.Initialize(this->device, v, ARRAYSIZE(v));
        if (FAILED(hr))
        {
            ErrorLogger::Log(hr, "Failed to create vertex buffer.");
            return false;
        }
        DWORD indices[] =
        {
            0,1,2
        };
        hr = this->indexBuffer.Initialize(this->device, indices, ARRAYSIZE(indices));
        if (FAILED(hr))
        {
            ErrorLogger::Log(hr, "Failed to create indices buffer");
            return hr;
        }
    }
    else if (MeshType == Quad)
    {
        Vertex v[] = {
            //Quad
            Vertex(-2.50f, -2.25f, 0.0f, 0.0f, 1.0f),//7
            Vertex(-2.50f, -1.25f, 0.0f, 0.0f, 0.0f),//8
            Vertex(-1.0f, -1.0f, 0.0f, 1.0f, 0.0f), //9
            Vertex(-1.0f, -2.5f, 0.0f, 1.0f, 1.0f), //10
        };
        HRESULT hr = this->vertexBuffer.Initialize(this->device, v, ARRAYSIZE(v));
        if (FAILED(hr))
        {
            ErrorLogger::Log(hr, "Failed to create vertex buffer.");
            return false;
        }
        DWORD indices[] =
        {
         0, 1, 2,
          0,2,3
        };
        hr = this->indexBuffer.Initialize(this->device, indices, ARRAYSIZE(indices));
        if (FAILED(hr))
        {
            ErrorLogger::Log(hr, "Failed to create indices buffer");
            return hr;
        }
    }
    else if (MeshType == Line)
    {
    Vertex v[] = {
        Vertex(0.5f, -1.5f, 0.0f, 0.0f, 0.0f),
        Vertex(2.5f, -0.97f, 0.0f, 0.0f, 0.0f),

    };
    HRESULT hr = this->vertexBuffer.Initialize(this->device, v, ARRAYSIZE(v));
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create vertex buffer.");
        return false;
    }
    DWORD indices[] =
    {
         0, 1, 
    };
    hr = this->indexBuffer.Initialize(this->device, indices, ARRAYSIZE(indices));
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create indices buffer");
        return hr;
    }
    }


    this->UpdateWorldMatrix();
    return true;
}

void Model::SetTexture(ID3D11ShaderResourceView * texture)
{
    this->texture = texture;
}

void Model::Draw(const matrix4<float> & viewProjectionMatrix)
{
    
    UpdateWorldMatrix();
    //Update Constant buffer with WVP Matrix
    this->cb_vs_vertexshader->data.mat = this->worldMatrix * viewProjectionMatrix; //Calculate World-View-Projection Matrix
  
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
   // matrix4<float> theResult = MATRIX4::build_identity<float>();

  //  this->worldMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z) * XMMatrixTranslation(this->translation.x, this->pos.y, this->pos.z);
    matrix4<float> _translation = MATRIX4::build_translation<float>(translation.x, translation.y);
    matrix4<float> _rotation = MATRIX4::build_rotation<float>(angle);
    matrix4<float> _scale = MATRIX4::build_scale<float>(scale.x, scale.y);
    
    this->worldMatrix = _translation * _rotation * _scale;//_scale * _rotation * _translation;
    this->worldMatrix = MATRIX4::transpose(this->worldMatrix);
/*
   this->worldMatrix = MATRIX4::build_identity<float>();
    this->worldMatrix *= MATRIX4::build_translation<float>(translation.x, translation.y,0.0f) * MATRIX4::build_rotation<float>(angle) * MATRIX4::build_scale<float>(scale.x, scale.y, 0.0f);
  */ // this->worldMatrix = MATRIX4::transpose(this->worldMatrix);
}

void Model::AdjustPosition(float x, float y, float z)
{
    this->translation.x += x;
    this->translation.y += y;
   
  //  this->translation.z = 0.0f;
    this->UpdateWorldMatrix();
}

void Model::AdjustScale(float scaleX, float scaleY)
{
    this->scale.x += scaleX;
    this->scale.y += scaleY;
}

void Model::AdjustRotation(float __angle)
{
    angle += __angle;

    this->UpdateWorldMatrix();
}
