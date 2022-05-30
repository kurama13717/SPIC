#pragma once

#include "Graphics/Sprite.h"
#include "Audio/AudioSource.h"
#include "Scene.h"

class SceneRule : public Scene
{
public:
    SceneRule() {}
    //SceneRule(Scene* nextScene) :nextScene(nextScene) {}
    //SceneLoading() {}
    ~SceneRule() {}
    void Initialize() override;
    void Finalize() override;
    void Update(float elapsedTime)override;
    void Render()override;
private:
    //Scene* nextScene = nullptr;
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
    std::unique_ptr<AudioSource> HelpBGM;
    std::unique_ptr<AudioSource> SelectSE;
    bool flag = false;
    float ChangeTimer = 0.0f;


};