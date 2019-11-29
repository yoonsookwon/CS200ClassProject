#include  "Graphics.h"

bool Graphics::Init(HWND hwnd, int width, int height)
{
    this->windowWidth = width;
    this->windowHeight = height;
    if (!InitDirectX(hwnd))
        return  false;

    if (!InitShaders())
        return false;

    if (!InitScene())
        return false;

    return  true;
}

void Graphics::RenderFrame()
{
    //Able to set up background color
    float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);
    this->deviceContext->ClearDepthStencilView(this->depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


    this->deviceContext->IASetInputLayout(this->vertexshader.GetInputLayout());
    this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    this->deviceContext->RSSetState(this->rasterizerState.Get());
    this->deviceContext->OMSetDepthStencilState(this->depthStencilState.Get(), 0);
    this->deviceContext->PSSetSamplers(0, 1, this->samplerState.GetAddressOf());
    this->deviceContext->VSSetShader(vertexshader.GetShader(), NULL, 0);
    this->deviceContext->PSSetShader(pixelshader.GetShader(), NULL, 0);

    UINT offset = 0;


    //���⼭ �̹��� ��ġ�� �ٲ�
    //Update Constant Buffer
    
    /// �̷������� static �������� ���������� �ָ鼭 �̹����� ��� �����̰� ����� ����
    /*
    static float yOff = 0.5f;
    yOff -= 0.01f;
    */
    //DirectX::XMMatrixRotationRollPitchYaw(0.0f,0.0f, DirectX::XM_PIDIV2); -> 90�� �ݽð�������� ������
    //DirectX::Translation.. d�̵�
    XMMATRIX world = XMMatrixIdentity();
    
    camera.AdjustPosition(0.0f, 0.01f, 0.0f);
    camera.SetLookAtPos(XMFLOAT3(0.0f, 0.0f, 0.0f));
    constantBuffer.data.mat = world * camera.GetViewMatrix() * camera.GetProjectionMatrix();
    constantBuffer.data.mat = DirectX::XMMatrixTranspose(constantBuffer.data.mat);
    
    
    if (!constantBuffer.ApplyChanges())
        return;
    this->deviceContext->VSSetConstantBuffers(0,1, this->constantBuffer.GetAddressOf());
    /*D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT hr = this->deviceContext->Map(constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    CopyMemory(mappedResource.pData, &data, sizeof(CB_VS_vertexshader));
    this->deviceContext->Unmap(constantBuffer.Get(), 0);
    this->deviceContext->VSSetConstantBuffers(0,1, constantBuffer.GetAddressOf());
*/

    //Square
    /*�̹��� �ε��ϴ� �ڵ�*/  this->deviceContext->PSSetShaderResources(0, 1, this->myTexture.GetAddressOf());
    /*�̹��� �ε��ϴ� �ڵ�*/ this->deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
    this->deviceContext->IASetIndexBuffer(indicesBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    //������ִµ��� ����صڿ� ���⿡ ������ŭ ������ ������Ѵ�.

    this->deviceContext->DrawIndexed(indicesBuffer.BufferSize(), 0, 0);

    //Draw Text
    spriteBatch->Begin();
    spriteFont->DrawString(spriteBatch.get(), L"HELLO I'M ROBIN!!", DirectX::XMFLOAT2(0, 0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
    spriteBatch->End();

    //If want to turn on the vSync put the value 1, otherwise put 0 
    this->swapChain->Present(1, NULL);
}

bool Graphics::InitDirectX(HWND hwnd)
{
    std::vector<AdapterData> adapters = AdapterReader::GetAdapters();

    if (adapters.size() < 1)
    {
        ErrorLogger::Log("No IDXGI Adapters found.");
        return false;
    }

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferDesc.Width = this->windowWidth;
    scd.BufferDesc.Height = this->windowHeight;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;

    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;

    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;
    scd.OutputWindow = hwnd;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    //Ʃ�丮�� 9
    HRESULT hr;
    hr = D3D11CreateDeviceAndSwapChain(adapters[0].pAdapter,
        D3D_DRIVER_TYPE_UNKNOWN,
        NULL,
        NULL,
        NULL,
        0,
        D3D11_SDK_VERSION,
        &scd,
        this->swapChain.GetAddressOf(),
        this->device.GetAddressOf(),
        NULL,
        this->deviceContext.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create device and swapchain.");
        return  false;
    }

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backbuffer;
    hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backbuffer.GetAddressOf()));

    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "GetBuffer Failed");
        return  false;
    }

    hr = this->device->CreateRenderTargetView(backbuffer.Get(), NULL, this->renderTargetView.GetAddressOf());

    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create render target view");
        return  false;
    }
    //Describe our Depth/Stencil buffer
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    depthStencilDesc.Width = this->windowWidth;
    depthStencilDesc.Height = this->windowHeight;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    hr = this->device->CreateTexture2D(&depthStencilDesc, NULL, this->depthStencilBuffer.GetAddressOf());
    if (hr != S_OK)
    {
        ErrorLogger::Log(hr, "Failed to create depth stencil buffer.");
        return false;
    }

    hr = this->device->CreateDepthStencilView(this->depthStencilBuffer.Get(), NULL, this->depthStencilView.GetAddressOf());
    if (hr != S_OK)
    {
        ErrorLogger::Log(hr, "Failed to create depth stencil view.");
        return false;
    }

    this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), this->depthStencilView.Get());

    //Create depth stecil State
    D3D11_DEPTH_STENCIL_DESC depthstencildesc;
    ZeroMemory(&depthstencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    depthstencildesc.DepthEnable = true;
    depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
    depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

    hr = this->device->CreateDepthStencilState(&depthstencildesc, this->depthStencilState.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create depth stencil state.");
        return false;
    }

    //Create Viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = this->windowWidth;
    viewport.Height = this->windowHeight;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    //Set the viewport
    this->deviceContext->RSSetViewports(1, &viewport);

    //Create Rasterizer State
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

    //RasterizerDesc!! 
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
    /* rasterizerDesc.FrontCounterClockwise = TRUE;*/

    hr = this->device->CreateRasterizerState(&rasterizerDesc, this->rasterizerState.GetAddressOf());
    if (hr != S_OK)
    {
        ErrorLogger::Log(hr, "Failed to create rasterizer state.");
        return false;
    }

    spriteBatch = std::make_unique<DirectX::SpriteBatch>(this->deviceContext.Get());
    spriteFont = std::make_unique<DirectX::SpriteFont>(this->device.Get(), L"Data\\Fonts\\robins_sprite_ms_16.spritefont");

    //Create sampler description for sampler state
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = this->device->CreateSamplerState(&sampDesc, this->samplerState.GetAddressOf());

    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create sampler state.");
        return false;
    }

    return  true;
}

bool Graphics::InitShaders()
{
    std::wstring shaderfolder = L"";
#pragma  region DetermineShaderPath

    if (IsDebuggerPresent() == TRUE)
    {
#ifdef  _DEBUG // Debug mode
#ifdef  _WIN64 //x64
        shaderfolder = L"..\\x64\\Debug\\";
#else //x86(Win32)
        shaderfloder = L"..\\Debug\\";
#endif
#else // Release mode
#ifdef _WIN64
        shaderfolder = L"..\\x64\\Release\\";
#else
        shaderfolder = L"..\\Release\\";
#endif
#endif
    }

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION",0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA}
    };

    UINT numElements = ARRAYSIZE(layout);


    if (!vertexshader.Initialize(this->device, shaderfolder + L"vertexshader.cso", layout, numElements))
        return  false;

    if (!pixelshader.Initialize(this->device, shaderfolder + L"pixelshader.cso"))
        return false;

    return true;
}

bool Graphics::InitScene()
{
    //Triangle (Red)
    Vertex v[] = {
         Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f),//bottom left [0]
         Vertex(-0.5f, 0.5f,0.0f, 0.0f,0.0f), //top left [1]

         Vertex(0.5f, 0.5f,0.0f, 1.0f,0.0f), //top right [2]
         Vertex(0.5f, -0.5f, 0.0f,1.0f,1.0f), //bottom right [3]
    };

    //Load Vertex Data
    HRESULT hr = this->vertexBuffer.Initialize(this->device.Get(), v, ARRAYSIZE(v));
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create vertex buffer.");
        return false;
    }

    DWORD indices[] =
    {   
        0,1,2,
        0,2,3
    };


    //Load index data
    hr = this->indicesBuffer.Initialize(this->device.Get(), indices, ARRAYSIZE(indices));
     if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create indices buffer");
        return hr;
    }

    //�̹��� �����°�
    hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\chicken.png", nullptr, myTexture.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create wic texture from file.");
        return false;
    }

    //Initialize Constant Buffer(s)
    
    hr = this->constantBuffer.Initialize(this->device.Get(),this->deviceContext.Get());
    if (FAILED(hr)) {
        ErrorLogger::Log(hr, "Failed to initialize constant buffer.");
        return false;
    }

    camera.SetPosition(0.0f, 0.0f, -2.0f);
    camera.SetProjectionValues(90.0f, static_cast<float>(windowWidth)/static_cast<float>(windowHeight),0.1f, 1000.0f);
    return true;
}
