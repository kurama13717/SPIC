#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "Effect.h"
#include "BurretManager.h"

enum Animation
{
    Anim_Attack,
    Anim_Death,
    Anim_Falling,
    Anim_GetHit1,
    Anim_GetHit2,
    Anim_Idle,
    Anim_Jump,
    Anim_Jump_Flip,
    Anim_Landing,
    Anim_Revive,
    Anim_Running,
    Anim_Walking,
};

class Player : public Character
{
public:
    Player();
    ~Player() override;
    void  Update(float elapsedTime);
    void Render(ID3D11DeviceContext* dc, Shader* shader);
    //デバッグ
    void DrawDebugGUI();
    void DrawDebugPrimitive();

    // 弾丸入力処理
    void InputBurret();

    //ジャンプ入力処理
    bool InputJump();

    //プレイヤーとエネミー衝突
    void CollisionPlayerVsEnemies();
    
    
    
    static Player& Instance();
protected:
    void OnLanding() override;
    void OnDamaged()override;
    void OnDead()override;
private:
    DirectX::XMFLOAT3 GetMoveVec() const;
    
    bool InputMove(float elapsedTime);

    bool InputAttack();
    //待機ステート遷移
    void TransitionIdleState();
    //待機ステート更新処理
    void UpdateIdleState(float elapsedTime);
    //移動ステートへ遷移
    void TransitionMoveState();
    //移動ステート更新処理
    void UpdateMoveState(float elapsedTime);
    void TransitionJumpState();
    void UpdateJumpState(float elapsedTime);
    void TransitionLandState();
    void UpdateLandState(float elapsedTime);
    void TransitionAttackState();
    void UpdateAttackState(float elapsedTime);
    void TransitionDamageState();
    void UpdateDamageState(float elapsedTime);
    void TransitionDeathState();
    void UpdateDeathState(float elapsedTime);
    void TransitonReviveState();
    void UpdateReviveState(float elapsedTime);
    void CollisionNodeVsEnemies(const char* nodeName, float nodeRadius);
private:
    //ステート
    enum class State
    {
        Idle,
        Move,
        Jump,
        Land,
        Attack,
        Damage,
        Death,
        Revive,
    };
    State state = State::Idle;
    Model* model = nullptr;
    float moveSpeed = 5.0f;
    float turnSpeed = DirectX::XMConvertToRadians(720);

    float jumpSpeed = 20.0f;
    int jumpCount = 0;
    int jumpLimit = 2;

    Effect* hitEffect = nullptr;
    float leftHandRadius = 0.4f;
    bool attackCollisionFlag = false;

    BurretManager burretManager;
};