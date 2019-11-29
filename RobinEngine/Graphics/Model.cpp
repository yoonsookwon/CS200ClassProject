#include "Model.h"

bool Model::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView * texture, ConstantBuffer<CB_VS_vertexshader>& cb_vs_vertexshader)
{
    this->device = device;
    this->deviceContext = deviceContext;
    this->texture = texture;
    this->cb_vs_vertexshader = &cb_vs_vertexshader;

    Vertex v[] = {

            Vertex(-0.5f,  -0.5f, -0.5f, 0.0f, 1.0f), //FRONT Bottom Left   - [0]
            Vertex(-0.5f,   0.5f, -0.5f, 0.0f, 0.0f), //FRONT Top Left      - [1]
            Vertex(0.5f,   0.5f, -0.5f, 1.0f, 0.0f), //FRONT Top Right     - [2]
            Vertex(0.5f,  -0.5f, -0.5f, 1.0f, 1.0f), //FRONT Bottom Right   - [3]
      //  //square
      //   Vertex(-3.0f, 0.5f, 0.0f, 0.0f,1.0f),//bottom left [0]
      //   Vertex(-3.0f, 1.5f,0.0f, 0.0f,0.0f), //top left [1]

      //   Vertex(-2.0f, 1.5f,0.0f, 1.0f,0.0f), //top right [2]
      //   Vertex(-2.0f, 0.5f, 0.0f,1.0f,1.0f), //bottom right [3]

      ////Triangle (Red)
      //   Vertex(-2.0f, 0.5f, 0.0f, 0.0f, 1.0f),
      //   Vertex(-1.5f, 1.5f, 0.0f, 0.0f, 1.0f),
      //   Vertex(-1.0f, 0.5f, 0.0f, 0.0f, 1.0f),
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
            0, 1, 2, //FRONT
            0, 2, 3, //FRONT
    };

    //Load index data
    hr = this->indexBuffer.Initialize(this->device, indices, ARRAYSIZE(indices));
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create indices buffer");
        return hr;
    }

    this->UpdateWorldMatrix();
    return true;
}

void Model::SetTexture(ID3D11ShaderResourceView * texture)
{
    this->texture = texture;
}

void Model::Draw(const XMMATRIX & viewProjectionMatrix)
{
    this->cb_vs_vertexshader->data.mat = this->worldMatrix * viewProjectionMatrix;
    this->cb_vs_vertexshader->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader->data.mat);
    this->cb_vs_vertexshader->ApplyChanges();
    this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader->GetAddressOf());

    this->deviceContext->PSSetShaderResources(0, 1, &this->texture);
    this->deviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT,0);


    UINT offset = 0; 
    this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
    this->deviceContext->DrawIndexed(this->indexBuffer.BufferSize(), 0, 0);
}

void Model::UpdateWorldMatrix()
{
    this->worldMatrix = XMMatrixIdentity();
}
