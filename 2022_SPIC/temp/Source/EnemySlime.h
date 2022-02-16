#pragma once
#include "Graphics/Model.h"
#include "Enemy.h"

class EnemySlime : public Enemy
{
public:
    EnemySlime();
    ~EnemySlime() override;
    void Update(float elapsedTime) override;
    void Render(ID3D11DeviceContext* dc, Shader* shader)override;
    void DrawDebugPrimitive()override;
    //縄張り設定
    void SetTerritory(const DirectX::XMFLOAT3& origin, float range);
private:
    //ターゲット位置をランダム設定
    void SetRandomTargetPosition();
    //目的位置に移動
    void MoveToTarget(float elapsedTime,float speedRate);
    //徘徊ステートへ遷移
    void TransitionWanderState();
    //徘徊ステート更新処理
    void UpdateWanderState(float elapsedTime);
    void TransitionIdleState();
    void UpdateIdleState(float elapsedTime);
    void TransitionPursuitState();
    void UpdatePursuitState(float elapsedTime);
    bool SearchPlayer();
    void CollisitionNodeVsPlayer(const char* nodeName, float boneRadius);
    void TransitionAttackState();
    void UpdateAttackState(float elapsedTimer);
    void TransitionIdleBattleState();
    void UpdateIdleBattleState(float elapsedTime);
    void TransitionDamageState();
    void UpdateDamageState(float elapsedTime);
    void TransitionDeathState();
    void UpdateDeathState(float elapsedTime);
protected:
    void OnDead()override;
    void OnDamaged()override;
private:
    enum class State
    {
        Wander,
        Idle,
        Pursuit,
        Attack,
        IdleBattle,
        Damage,
        Death,
    };
    enum Animation
    {
        Anim_IdleNormal,
        Anim_IdleBattle,
        Anim_Attack1,
        Anim_Attack2,
        Anim_WalkFWD,
        Anim_WalkBWD,
        Anim_WalkLeft,
        Anim_WalkRight,
        Anim_RunFWD,
        Anim_SenseSomthingST,
        Anim_SenseSomthingPRT,
        Anim_Taunt,
        Anim_Victory,
        Anim_GetHit,
        Anim_Dizzy,
        Anim_Die
    };
private:
    Model* model = nullptr;
    State state = State::Wander;
    DirectX::XMFLOAT3 targetPosition = { 0,0,0 };
    DirectX::XMFLOAT3 territoryOrigin = { 0,0,0 };
    float territoryRange = 10.0f;
    float moveSpeed = 3.0f;
    float turnSpeed = DirectX::XMConvertToRadians(360);
    float stateTimer = 0.0f;
    float searchRange = 5.0f;
    float attackRenge = 1.5f;
};