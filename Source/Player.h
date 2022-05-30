#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "Effect.h"
#include "BulletManager.h"
#include "CameraController.h"

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

    void SpectatorUpdate(float elapsedTime);

    void Render(ID3D11DeviceContext* dc, Shader* shader);
    //�f�o�b�O
    void DrawDebugGUI();
    void DrawDebugPrimitive();

    // �e�ۓ��͏���
    void InputBullet();

    //�@�e�ۂ̏���
    void DestroyBullet();

    //�W�����v���͏���
    bool InputJump();

    //�v���C���[�ƃG�l�~�[�Փ�
    void CollisionPlayerVsEnemies();

    bool GetisFire()const { return isFire; }
    void SetisFire(const bool isfire) { this->isFire = isfire; }

    bool GetPredictionFlag()const { return bullet2Flag; }
    void SetPredictionFlag(const bool bullet2Flag) { this->bullet2Flag = bullet2Flag; }
    
    DirectX::XMFLOAT3 ct = {};

    DirectX::XMFLOAT3 moveVec;

    
    static Player& Instance();
protected:
    void OnLanding() override;
    void OnDamaged()override;
    void OnDead()override;
private:
    DirectX::XMFLOAT3 GetMoveVec() const;
    
    bool InputMove(float elapsedTime);

    bool InputAttack();
    //�ҋ@�X�e�[�g�J��
    void TransitionIdleState();
    //�ҋ@�X�e�[�g�X�V����
    void UpdateIdleState(float elapsedTime);
    //�ړ��X�e�[�g�֑J��
    void TransitionMoveState();
    //�ړ��X�e�[�g�X�V����
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
    //�X�e�[�g
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
    Bullet* bullet = nullptr;
    Bullet* bullet2 = nullptr;
    float moveSpeed = 5.0f;
    float turnSpeed = DirectX::XMConvertToRadians(720);

    float jumpSpeed = 20.0f;
    int jumpCount = 0;
    int jumpLimit = 2;

    int L1 = 0;
    

    Effect* hitEffect = nullptr;
    float leftHandRadius = 0.4f;
    bool attackCollisionFlag = false;

    //���˒��̃t���O
    bool Firing = false;

    bool bullet2Flag = false;         //�O���\��ON�AOFF

    //BulletManager bulletManager;

    CameraController* camera;

    bool isFire = false;
};