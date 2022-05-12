#pragma once

#include <vector>
#include "Stage.h"

class StageManager
{
private:
    StageManager() {}
    ~StageManager() {}
public:
    static StageManager& Instance()
    {
        static StageManager instance;
        return instance;
    }
    void Update(float elapsedTime);
    void Render(ID3D11DeviceContext* context, Shader* shader,int flag);
    void Register(Stage* stage);
    void Clear();
    bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);
    void Remove(Stage* stage);

   
  


    int hitObject = 0;

    bool flag0_r = false;
    bool flag1_r = false;
    bool flag2_r = false;

private:
    std::vector<Stage*> stages;
    std::vector<Stage*> removes;

    Stage* currentState = nullptr;

};