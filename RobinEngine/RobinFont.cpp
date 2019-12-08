#include  "RobinFont.h"
#include <iostream>
#include  <WICTextureLoader.h>

void RobinFont::Init(ID3D11Device* _device, ID3D11DeviceContext* _device_context, ConstantBuffer<CB_VS_vertexshader>& _constant_vsBuffer)
{
    this->device = _device;
    this->device_context = _device_context;
    this->constant_vsBuffer = &_constant_vsBuffer;

    if (!robin_font.LoadFromFile("Data\\Fonts\\bitmap.fnt"))
    {
        return;
    }
    //MUST be png file????
    HRESULT hr = DirectX::CreateWICTextureFromFile(this->device, L"Data\\Fonts\\bitmap_0.png", nullptr, font.GetAddressOf());

    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to Load texts");
    }
}

void RobinFont::Update()
{
    device_context->VSSetConstantBuffers(0, 1, this->constant_vsBuffer->GetAddressOf());
    device_context->PSSetShaderResources(0, 1, font.GetAddressOf());
    device_context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
    UINT offset = 0;

    device_context->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
    device_context->DrawIndexed(this->indexBuffer.BufferSize(), 0, 0);
}

void RobinFont::SetText(std::wstring text,  float offsetX, float offsetY)
{

    BitmapFont::character charInfo;
    int countIndex = 0;
    float offset = offsetX;
    float offset_Y = offsetY;
   
    v = new Vertex[6 * text.size()];
    indices = new DWORD[6 * text.size()];

    for (int i = 0; i < text.size(); i++)
    {
        charInfo = robin_font.GetCharacter(text.at(i));
        vector2<float> text_leftTop = { static_cast<float>(charInfo.x) / static_cast<float>(robin_font.GetInformation().imageWidth),
                                        static_cast<float>(charInfo.y) / static_cast<float>(robin_font.GetInformation().imageWidth) };

        vector2<float> text_rightTop = { text_leftTop.x + static_cast<float>(charInfo.width) / static_cast<float>(robin_font.GetInformation().imageWidth),
                                         text_leftTop.y };

        vector2<float> text_leftBottom = { text_leftTop.x,
                                            text_leftTop.y + static_cast<float>(charInfo.height) / static_cast<float>(robin_font.GetInformation().imageHeight) };

        vector2<float> text_rightBottom = { text_rightTop.x, text_leftBottom.y };

        float text_Offset = static_cast<float>(charInfo.width) / static_cast<float>(robin_font.GetInformation().imageWidth);


        v[countIndex] = Vertex(offset, offset_Y, 0.0f, text_leftBottom.x, text_leftTop.y);
        v[countIndex + 1] = Vertex(offset, offset_Y - 0.2f, 0.0f, text_leftTop.x, text_leftBottom.y);
        v[countIndex + 2] = Vertex(offset + text_Offset, offset_Y, 0.0f, text_rightTop.x, text_rightTop.y);
        v[countIndex + 3] = Vertex(offset + text_Offset, offset_Y, 0.0f, text_rightTop.x, text_rightTop.y);
        v[countIndex + 4] = Vertex(offset, offset_Y - 0.2f, 0.0f, text_leftBottom.x, text_rightBottom.y);
        v[countIndex + 5] = Vertex(offset + text_Offset, offset_Y - 0.2f, 0.0f, text_rightTop.x, text_rightBottom.y);

        indices[countIndex] = countIndex;
        indices[countIndex + 1] = countIndex + 1;
        indices[countIndex + 2] = countIndex + 2;
        indices[countIndex + 3] = countIndex + 3;
        indices[countIndex + 4] = countIndex + 4;
        indices[countIndex + 5] = countIndex + 5;

        countIndex += 6;
        offset += (text_Offset +0.04f);
    }
    HRESULT hr = this->vertexBuffer.Initialize(this->device, v, text.size() * 6);
    hr = this->indexBuffer.Initialize(this->device, indices, text.size() * 6);

    delete[]v;
    delete[]indices;
}
