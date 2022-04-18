#pragma once
#include "Graphics/Model.h"
#include "Stage.h"
class StageMain : public Stage
{
public:
    StageMain();
    ~StageMain()override;
    void Update(float elapsedTime)override;
    void Render(ID3D11DeviceContext* dc, Shader* shader,int flag)override;
    bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;
    static Stage& Instance();
private:
    Model* model = nullptr;
};