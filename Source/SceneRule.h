#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"

class SceneRule : public Scene
{
public:
    SceneRule() {}
    //SceneLoading() {}
    ~SceneRule() {}
    void Initialize() override;
    void Finalize() override;
    void Update(float elapsedTime)override;
    void Render()override;
private:
    Sprite* Rule = nullptr;
    Sprite* Signal = nullptr;
    Sprite* B = nullptr;
    int SignalTimer = 0;
    int SceneCount = 1;
    float axisX = 0;
    float RulePosX = 0.0f;
    bool RuleMove_R = false;
    bool RuleMove_L = false;
    DirectX::XMFLOAT2 Pos = { 0.0f,0.0f };
};