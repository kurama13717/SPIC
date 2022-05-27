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
private:
    DirectX::XMFLOAT2 position = {};
    DirectX::XMFLOAT2 ballPosition = {};
    DirectX::XMFLOAT2 ballCurrentPosition = {};
    DirectX::XMFLOAT2 ballSize = {};
    float speed = 5.0f;
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

    float i = 0;
};