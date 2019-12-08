/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#pragma once
#include "AdapterReader.h"
#include  "Shaders.h"
#include  <SpriteBatch.h>
#include  <SpriteFont.h>
#include <WICTextureLoader.h>
#include "ConstantBuffer.h"
#include "Camera.h"
#include "Model.h"
#include "vector2.hpp"
#include <..\\RobinFont.h>
#include "..\\Timer.h"

enum STATE
{
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
};
class Graphics
{
public:
    bool Init(HWND hwnd, int width, int height);
    void RenderFrame();
    void FULLSCREEN(bool toggle);

    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;

    Camera camera;

    Model Triangle;
    Model Quad;
    Model Line;
    Model Rectangle;
    Model Elipse;

    Model ChulHead;
    Model ChulBody;
    Model Chullegs;
    Model ChulLArm;
    Model ChulRArm;
    Model FixLastPoint;

    RobinFont description[20];
    RobinFont Level2Text[2];
    //RobinFont description2;
    //RobinFont description3;

 
    bool is_vSyncOn = true;

    STATE current_state = LEVEL1;
    Microsoft::WRL::ComPtr<  ID3D11Device> device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backbuffer;

     
private:
    bool InitDirectX(HWND hwnd);
    bool InitShaders();
    bool InitScene();

    //Work like smart pointer
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
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ttuckBokki_Texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ramen_Texture;


    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ChulHead_Texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ChulBody_Texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Chullegs_Texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ChulLarm_Texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ChulRarm_Texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Nothing_Texture;
   // Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ramen_Texture;

    FLOAT windowWidth = 0;
    FLOAT windowHeight = 0;
    Timer fpsTimer;
};
