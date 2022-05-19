#include "StageManager.h"

void StageManager::Update(float elapsedTime)
{
    for (Stage* stage : stages)
    {
        stage->Update(elapsedTime);
    }

    //破棄処理
    for (Stage* stage : removes)
    {
        //std::vectorから要素を削除する場合はイテレーターで削除しなければならない
        std::vector<Stage*>::iterator it = std::find(stages.begin(), stages.end(), stage);

        if (it != stages.end())
        {
            stages.erase(it);
        }

        //弾丸の破棄処理
        delete stage;
    }
    //破棄リストをクリア
    removes.clear();
}
void StageManager::Render(ID3D11DeviceContext* context, Shader* shader, int flag)
{
    for (Stage* stage : stages)
    {
        stage->Render(context, shader,flag);
    }
}
void StageManager::Register(Stage* stage)
{
    stages.emplace_back(stage);
}
void StageManager::Clear() 
{
    for (Stage* stage : stages)
    {
        delete stage;
    }
    stages.clear();
}
bool StageManager::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
    bool result = false;
    hit.distance = FLT_MAX;
    for (Stage* stage : stages)
    {
        HitResult tmp;
        if (stage->RayCast(start, end, tmp))
        {
            if (hit.distance > tmp.distance)
            {
                hit = tmp;
                result = true;
            }
        }
    }
    return result;
}

void StageManager::Remove(Stage* stage)
{
    //破棄リストに追加
    removes.emplace_back(stage);
}

bool StageManager::ClearFlag(int MarkCount, int HitCount)
{

    if (MarkCount == HitCount)
    {
        //StageClearFlag = true;
        return true;
    }
    return false;

}