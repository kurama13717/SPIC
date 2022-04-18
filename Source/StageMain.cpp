#include "StageMain.h"

StageMain::StageMain()
{
    model = new Model("Data/Model/Stage/flat.mdl");//�X�e�[�W�ǂݍ���
    
}

StageMain::~StageMain()
{
    delete model;
}

void StageMain::Update(float elapsedTime)
{

}

void StageMain::Render(ID3D11DeviceContext* dc, Shader* shader,int falg)
{
    shader->Draw(dc,model);
}

bool StageMain::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
    return Collision::IntersectRayVsModel(start, end, model, hit);
}