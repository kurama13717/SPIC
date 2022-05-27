#pragma once
#include <string>
#include <memory>
#include "Graphics/Graphics.h"
#include "Graphics/Sprite.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "CameraController.h"
#include "Scene.h"
#include "Font.h"
#include "PerlinNoise.h"
#include "CoordinateTransformation.h"
#include "Audio/Audio.h"
#include "Audio/AudioSource.h"

class SceneTitle :public Scene
{
public: 
    SceneTitle() {}
    ~SceneTitle() override {}
    void Initialize() override;
    void Finalize() override;
    void Update(float elapsedTime)override;
    void Render()override;
    void TitleInput();
    void UpdateTransform();
    void DrawDebugGUI();
    float lerp(float start, float end, float t)
    {
        return (1 - t) * start + t * end;
    }
private:
    Graphics& graphics = Graphics::Instance();
    ID3D11Device* device = graphics.GetDevice();
    RenderContext rc;
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    Microsoft::WRL::ComPtr<ID3D11DeviceContext>		immediateContext;
    Sprite* sprite = nullptr;
    Sprite* Title = nullptr;
    Sprite* o = nullptr;
    Sprite* arrow = nullptr;
    float arrowPosX = 500;
    //Camera
    Camera& camera = Camera::Instance();
    CameraController* cameracontroller = nullptr;
    float fov = 65;
    //Font
    std::unique_ptr<Font>				font;
    //audio
    std::unique_ptr<AudioSource>bgm = nullptr;
    std::unique_ptr<AudioSource>se = nullptr;
    std::unique_ptr<AudioSource>noise = nullptr;
    //PwrlinNoise
    PerlinNoise pn;

    DirectX::XMFLOAT3   position = { 0,0,0 };
    DirectX::XMFLOAT3   angle = { 0,0,0 };
    DirectX::XMFLOAT3   scale = { 1,1,1 };
    DirectX::XMFLOAT4X4 transform = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
    };

    // ïœçXì_
    int Timer = 0;
    //XMFLOAT2 opos = { 1000,82 };
    XMFLOAT2 opos = { 1000,82 };
    XMFLOAT2 oSpeed = { 10,10 };
    int oCount = 0;
    float screenWidth;
    float screenHeight;
    XMFLOAT2 oCurrntPos = {};
    float i;

    float axisY = 0;
    bool TitleMove_U = false;
    bool TitleMove_D = false;
    bool Moveble = false;
    int TitleMode = 0;
    Sprite* TitleGame = nullptr;
    Sprite* TitleHelp = nullptr;
    Sprite* TitleEnd = nullptr;
    enum  title
    {
        titleGame,
        titleHelp,
        titleEnd,
    };
    float TitleWidth = 300;
    float TitleHeight = 100;
    DirectX::XMFLOAT2 titleGamePos ={};
    DirectX::XMFLOAT2 titleHelpPos ={};
    DirectX::XMFLOAT2 titleEndPos  ={};
    DirectX::XMFLOAT2 titleGameSize={};
    DirectX::XMFLOAT2 titleHelpSize={};
    DirectX::XMFLOAT2 titleEndSize ={};
    float titleGameAlpha;
    float titleHelpAlpha;
    float titleEndAlpha;
    float alpha = 0;
};

