#pragma once

#include "Graphics/Graphics.h"
#include "Graphics/Sprite.h"
#include "Scene.h"

class SceneSelectStage : public Scene
{
public:
    SceneSelectStage() {}
    ~SceneSelectStage() {}
    void Initialize() override;
    void Finalize() override;
    void Update(float elapsedTime)override;
    void Render()override;
private:
    Graphics& graphics = Graphics::Instance();
    DirectX::XMFLOAT2 NumbersPos[5] =
    {
        {0.0f,graphics.GetScreenHeight()},
        {0,0},
        {0,0},
        {0,0},
        {graphics.GetScreenWidth(),graphics.GetScreenHeight()},
    };

    Sprite* SelectStage = nullptr;
    Sprite* Number1 = nullptr;
    Sprite* Number2 = nullptr;
    Sprite* Number3 = nullptr;
    Sprite* Number4 = nullptr;
    Sprite* Number5 = nullptr;
};
