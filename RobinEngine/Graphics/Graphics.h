#pragma once
#include "AdapterReader.h"
#include  "Shaders.h"
//#include "Vertex.h"
#include  <SpriteBatch.h>
#include  <SpriteFont.h>
#include <WICTextureLoader.h>
//#include "vertexbuffer.h"
//#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Camera.h"
#include "Model.h"

class Graphics
{
public:
    bool Init(HWND hwnd, int width, int height);
    void RenderFrame();
    Camera camera;
    Model model;

private:
    bool InitDirectX(HWND hwnd);
    bool InitShaders();
    bool InitScene();

    //Work like smart pointer
    Microsoft::WRL::ComPtr<  ID3D11Device> device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>renderTargetView;


    VertexShader vertexshader;
    PixelShader pixelshader;
    ConstantBuffer<CB_VS_vertexshader> cb_vs_vertexshader;
    ConstantBuffer<CB_PS_pixelshader> cb_ps_pixelshader;


    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>depthStencilView;
    Microsoft::WRL::ComPtr<ID3D11Texture2D>depthStencilBuffer;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState>depthStencilState;

    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blendState;
   

    std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
    std::unique_ptr<DirectX::SpriteFont> spriteFont;

    Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> myTexture;

    int windowWidth = 0;
    int windowHeight = 0;
};
