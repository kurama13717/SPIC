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


    bool Getflag_r(int index) { return flag_r[index]; }
    
    
   
    //���˂����񐔂ŃN���A���������Ƃ�
    int GetHitCount() { return HitCount; }
    void SetHitCount(int HitCount) { this->HitCount = HitCount; } 


    int GetStageNum() { return StageNum; }
    void SetStageNum(int StageNum) { this->StageNum = StageNum; }


    //�I���������邩�ŃN���A�����Ƃ��ɔ��ˏ�����ʂ�Ȃ��悤�ɂ���
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

    bool Retry = false;           // �I�S�ĂɓI�������e���O�ɓ����������ɃQ�[�������g���C����̃t���O
    bool StageClearFlag = false;  // �I�S�ĂɓI�����ăN���A�����Ƃ��ɔ�����Ƃ�t���O

    int StageNum = 0;
};