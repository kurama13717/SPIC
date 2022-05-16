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

   
    bool GetRetry() { return Retry; }
    void SetRetry(bool Retry) { this->Retry = Retry; }

    bool GetStageClear() { return StageClearFlag; }
    void SetStageClear(bool StageClearFlag) { this->StageClearFlag = StageClearFlag; }


    //bool Getflag0_r() { return flag0_r; }
    //bool Getflag1_r() { return flag1_r; }
    //bool Getflag2_r() { return flag2_r; }
    //void Setflag0_r(bool flag0_r) { this->flag0_r = flag0_r; }
    //void Setflag1_r(bool flag1_r) { this->flag1_r = flag1_r; }
    //void Setflag2_r(bool flag2_r) { this->flag2_r = flag2_r; }


    bool Getflag_r(int index) { return flag_r[index]; }
    
    
    //bool GetCheckFlag() { return checkFlag; }
    //void SetCheckFlag(bool checkFlag) { this->checkFlag = checkFlag; }


    //反射した回数でクリアしたかをとる
    int GetHitCount() { return HitCount; }
    void SetHitCount(int HitCount) { this->HitCount = HitCount; } 


    //的が何枚あるかでクリアしたときに反射処理を通らないようにする
    int GetMarkCount() { return MarkCount; }
    void SetMarkCount(int MarkCount) { this->MarkCount = MarkCount; }

    bool ClearFlag(int MarkCount, int HitCount);






    int hitObject = 0;

    int HitCount = 0;
    int MarkCount = 0;

    bool flag0_r = false;
    bool flag1_r = false;
    bool flag2_r = false;
    
    bool checkFlag = false;

    bool flag_r[50];

    


private:
    std::vector<Stage*> stages;
    std::vector<Stage*> removes;

    Stage* currentState = nullptr;

    bool Retry = false;           // 的全てに的中せず弾が外に当たった時にゲームをリトライするのフラグ
    bool StageClearFlag = false;  // 的全てに的中してクリアしたときに判定をとるフラグ

};