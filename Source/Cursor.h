#pragma once
#include "Graphics/Sprite.h"
#include "Graphics/Graphics.h"

class Cursor
{
public:
    Cursor();
    ~Cursor();
    void Update();
    void Render(ID3D11DeviceContext* dc);
    void Launch();
    void DrawDebugGUI();
    float lerp(float start, float end, float t) {
        return (1 - t) * start + t * end;
    }
    int GetonCursorNo(){ return onCursorNo; }
private:
    DirectX::XMFLOAT2 position = {};
    DirectX::XMFLOAT2 ballPosition = {};
    DirectX::XMFLOAT2 ballCurrentPosition = {};
    DirectX::XMFLOAT2 ballSize = {};
    float speed = 10.0f;
    float axisX = 0.0f;
    float axisY = 0.0f;
    bool moveble = false;
    Sprite* CursorSprite;
    Sprite* BallSprite;
    Graphics& graphics = Graphics::Instance();
    float cursorWidth;
    float cursorHeight;
    float ballWidth;
    float ballHeight;
    float screenWidth;
    float screenHeight;
    float StagesWidth;
    float StagesHeight;

    float i = 0;

    Sprite* Stage1 = nullptr;
    Sprite* Stage2 = nullptr;
    Sprite* Stage3 = nullptr;
    Sprite* Stage4 = nullptr;
    Sprite* Stage5 = nullptr;
    Sprite* Stage6 = nullptr;

    float Radius = 140.0f;
    float distance[6] = {};
    DirectX::XMFLOAT2 StageNumPos[6] =
    {
        {284,320},
        {675,326},
        {286,700},
        {674,695},
        //{525,650},
        //{840,650},
    };
    int onCursorNo = 10;
    int keep = 0;
    bool flag = false;
};