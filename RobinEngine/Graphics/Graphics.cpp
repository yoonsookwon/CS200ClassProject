#include  "Graphics.h"

bool Graphics::Init(HWND hwnd, int width, int height)
{
    this->windowWidth = static_cast<FLOAT>(width);
    this->windowHeight = static_cast<FLOAT>(height);
    this->fpsTimer.Start();
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
    this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
    this->deviceContext->RSSetState(this->rasterizerState.Get());
    this->deviceContext->OMSetDepthStencilState(this->depthStencilState.Get(), 0);
    this->deviceContext->OMSetBlendState(/*this->blendState.Get()*/NULL, NULL, 0xFFFFFFFF);
    this->deviceContext->PSSetSamplers(0, 1, this->samplerState.GetAddressOf());
    this->deviceContext->VSSetShader(vertexshader.GetShader(), NULL, 0);
    this->deviceContext->PSSetShader(pixelshader.GetShader(), NULL, 0);


    //UINT offset = 0;


    {//Chicken
       // camera.UpdateViewMatrix();
        if (current_state == LEVEL1) {
            this->Line.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
            this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            this->Elipse.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
            this->Rectangle.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
            this->Triangle.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
            this->Quad.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
            this->description[0].Update();
            this->description[1].Update();
            this->description[2].Update();
            this->description[3].Update();
            this->description[4].Update();

            this->description[5].Update();
            this->description[6].Update();
            this->description[7].Update();
            this->description[8].Update();
            this->description[9].Update();
            this->description[10].Update();
            this->description[11].Update();
            //this->description2.Update();

        }
        else if (current_state == LEVEL2)
        {
            //InitScene();
            this->camera.SetPosition(0, 0);
            this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            //this->Triangle.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
          //  this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            this->ChulLArm.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
            this->ChulRArm.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
            this->Chullegs.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
            this->ChulBody.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
            this->ChulHead.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
        }
    }

    //Draw Text
    static int fpsCounter = 0;
    static std::string fpsString = "FPS: 0";
    fpsCounter += 1;
    if (fpsTimer.GetMilisecondsElapsed() > 1000.0)
    {
        fpsString = "FPS: " + std::to_string(fpsCounter);
        fpsCounter = 0;
        fpsTimer.Restart();
    }

    spriteBatch->Begin();
    ////spriteFont->DrawString(spriteBatch.get(), L"HELLO I'M ROBIN!!", DirectX::XMFLOAT2(0, 0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
    spriteFont->DrawString(spriteBatch.get(), StringConverter::StringToWide(fpsString).c_str(), DirectX::XMFLOAT2(0, 0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
    spriteBatch->End();

    //If want to turn on the vSync put the value 1, otherwise put 0
    //if (vSync) {
    //}
    this->swapChain->Present(is_vSyncOn, NULL);

}

void Graphics::FULLSCREEN(bool toggle)
{
    swapChain->SetFullscreenState(toggle, nullptr);
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

    scd.BufferDesc.Width = static_cast<UINT>(this->windowWidth);
    scd.BufferDesc.Height = static_cast<UINT>(this->windowHeight);
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
    ///////////////////////////////////////////½ºÅ©¸°¼¦ backbuffer
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
    depthStencilDesc.Width = static_cast<UINT>(this->windowWidth);
    depthStencilDesc.Height = static_cast<UINT>(this->windowHeight);
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
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    /* rasterizerDesc.FrontCounterClockwise = TRUE;*/

    hr = this->device->CreateRasterizerState(&rasterizerDesc, this->rasterizerState.GetAddressOf());
    if (hr != S_OK)
    {
        ErrorLogger::Log(hr, "Failed to create rasterizer state.");
        return false;
    }

    //Create Blend State
    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));

    D3D11_RENDER_TARGET_BLEND_DESC rtbd;
    ZeroMemory(&rtbd, sizeof(rtbd));

    rtbd.BlendEnable = true;
    rtbd.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
    rtbd.DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
    rtbd.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
    rtbd.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
    rtbd.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
    rtbd.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
    rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

    blendDesc.RenderTarget[0] = rtbd;

    hr = this->device->CreateBlendState(&blendDesc, this->blendState.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create blend state.");
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
    //Initialize Constant Buffer(s)
    HRESULT hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\chicken.png", nullptr, myTexture.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create wic texture from file.");
        return false;
    }
    hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\ttuck.png", nullptr, ttuckBokki_Texture.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create wic texture from file.");
        return false;
    }
    hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\ramen.png", nullptr, ramen_Texture.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create wic texture from file.");
        return false;
    }
    hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\CHULJJA.png", nullptr, ChulHead_Texture.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create wic texture from file.");
        return false;
    }

    hr = this->cb_vs_vertexshader.Initialize(this->device.Get(), this->deviceContext.Get());
    if (FAILED(hr)) {
        ErrorLogger::Log(hr, "Failed to initialize constant buffer.");
        return false;
    }
    hr = this->cb_ps_pixelshader.Initialize(this->device.Get(), this->deviceContext.Get());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to initialize constant buffer.");
        return false;
    }
    hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\Chulbody.png", nullptr, ChulBody_Texture.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create wic texture from file.");
        return false;
    }
    hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\ChulLeg1.png", nullptr, Chullegs_Texture.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create wic texture from file.");
        return false;
    }
    hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\rightArm.png", nullptr, ChulLarm_Texture.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create wic texture from file.");
        return false;
    }
    hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\leftArm.png", nullptr, ChulRarm_Texture.GetAddressOf());
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create wic texture from file.");
        return false;
    }

    //Initialize Model
    if (!Line.Initialize(this->device.Get(), this->deviceContext.Get(), this->myTexture.Get(), cb_vs_vertexshader, Line.Line)) {
        return false;
    }
    if (!Triangle.Initialize(this->device.Get(), this->deviceContext.Get(), this->myTexture.Get(), cb_vs_vertexshader, Triangle.Triangle)) {
        return false;
    }
    if (!Quad.Initialize(this->device.Get(), this->deviceContext.Get(), this->ttuckBokki_Texture.Get(), cb_vs_vertexshader, Quad.Quad)) {
        return false;
    }
    if (!Rectangle.Initialize(this->device.Get(), this->deviceContext.Get(), this->ramen_Texture.Get(), cb_vs_vertexshader, Rectangle.Rectangle)) {
        return false;
    }
    if (!Elipse.Initialize(this->device.Get(), this->deviceContext.Get(), this->myTexture.Get(), cb_vs_vertexshader, Elipse.Elipse)) {
        return false;
    }


    if (!ChulHead.Initialize(this->device.Get(), this->deviceContext.Get(), this->ChulHead_Texture.Get(), cb_vs_vertexshader, Elipse.Rectangle)) {
        return false;
    }
    ChulHead.translation.x += 2.f;
    ChulHead.scale.x += 0.2f;
    ChulHead.scale.y += 0.2f;
    if (!ChulBody.Initialize(this->device.Get(), this->deviceContext.Get(), this->ChulBody_Texture.Get(), cb_vs_vertexshader, ChulBody.Rectangle)) {
        return false;
    }
    ChulBody.HierarchicalTYPE = Model::HierarchicalBODY;
    ChulBody.translation.x += 2.0f;
    ChulBody.translation.y -= 1.3f;
    ChulBody.scale.x += 0.5f;
    ChulBody.scale.y += 0.8f;
    if (!Chullegs.Initialize(this->device.Get(), this->deviceContext.Get(), this->Chullegs_Texture.Get(), cb_vs_vertexshader, ChulBody.Rectangle)) {
        return false;
    }
    Chullegs.translation.x += 2.0f;
    Chullegs.translation.y -= 2.5f;

    if (!ChulLArm.Initialize(this->device.Get(), this->deviceContext.Get(), this->ChulLarm_Texture.Get(), cb_vs_vertexshader, ChulBody.Rectangle)) {
        return false;
    }

    ChulLArm.translation.x += 0.5f;
    ChulLArm.translation.y -= 1.3f;
    if (!ChulRArm.Initialize(this->device.Get(), this->deviceContext.Get(), this->ChulRarm_Texture.Get(), cb_vs_vertexshader, ChulBody.Rectangle)) {
        return false;
    }

    ChulRArm.translation.x += 3.5f;
    ChulRArm.translation.y -= 1.3f;

    //Custom Font
    description[0].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[0].SetText(L"-CAMERA- ", -3.0f, 3.5f);

    description[1].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[1].SetText(L"MOVE : W A S D", -3.0f, 3.2f);

    description[2].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[2].SetText(L"ROTATION : Z X", -3.0f, 2.9f);

    description[3].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[3].SetText(L"ZOOM IN : MOUSE WHEEL UP", -3.0f, 2.6f);

    description[4].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[4].SetText(L"ZOOM OUT : MOUSE WHEEL DOWN", -3.0f, 2.3f);

    //OBJECT
    description[5].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[5].SetText(L"-OBJECT-", 1.f, 3.7f);

    description[6].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[6].SetText(L"MOVE : ARROW KEYS ", 1.f, 3.4f);

    description[7].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[7].SetText(L"ROTATION : NUM 1 2", 1.f, 3.1f);

    description[8].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[8].SetText(L"X SCALE : NUM 3 4", 1.f, 2.8f);

    description[9].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[9].SetText(L"Y SCALE : NUM 5 6", 1.f, 2.5f);

    description[10].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[10].SetText(L"SCREEN SHOT : P", 1.f, 2.0f);

    description[11].Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    description[11].SetText(L"V SYNC ON/OFF : V", 1.f, 1.7f);


    
    //description2.Init(this->device.Get(), this->deviceContext.Get(), this->cb_vs_vertexshader);
    //description.SetText(L"CAMERA ROTATE : Z X", -3.0f, 3.0f);

    camera.SetPosition(0.0f, -0.2f);
    //camera.SetProjectionValues(90.0f, static_cast<float>(windowWidth)/static_cast<float>(windowHeight),0.1f, 1000.0f);
    return true;
}
