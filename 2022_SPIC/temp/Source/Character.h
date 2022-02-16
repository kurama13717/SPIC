#pragma once
#include<DirectXMath.h>
class Character
{
public:
    Character() {}
    virtual ~Character() {}
    void UpdateTransform();

    //�Q�b�^�[�Z�b�^�[
    const DirectX::XMFLOAT3& GetPosition()const { return position; }
    void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }
    const DirectX::XMFLOAT3& GetAngle()const { return angle; }
    void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }
    const DirectX::XMFLOAT3& GetScale() const { return scale; }
    void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }
    //�Ռ���^����
    void AddImpulse(const DirectX::XMFLOAT3& impulse);
    //���a�擾
    float GetRadius() const { return radius; }
    //�����擾
    float GetHeight()const { return height; }
    bool IsGround()const { return isGround; }
    //�_���[�W�^����
    bool applyDamage(int damage, float invincibleTime);

    //���N��Ԏ擾
    int GetHealth()const { return health; }
    //�ő匒�N���
    int GetMaxHealth()const { return maxHealth; }
private:
    //�������x�X�V
    void UpdateVerticalVelocity(float elapsedTime);
    //�����ړ��X�V
    void UpdateVerticalMove(float elapsedTime);
    //�������x�X�V����
    void UpdateHorizontalVelocity(float elapasedFrame);
    //�����ړ��X�V����
    void UpdateHorizontalMove(float elapsedTime);
protected:
    //void Move(float elapsedTime, float vx, float vz, float speed);
    void Move(float vx, float vy, float speed);
    void Turn(float elapsedTime, float vx, float vz, float speed);
    void Jump(float speed);
    void UpdateVelocity(float elapsedTime);
    //���G���ԍX�V
    void UpdateInvincibleTimer(float elapsedTime);
    virtual void OnLanding() {}
    virtual void OnDamaged() {}
    virtual void OnDead() {}
protected:
    DirectX::XMFLOAT3   position = { 0,0,0 };
    DirectX::XMFLOAT3   angle = { 0,0,0 };
    DirectX::XMFLOAT3   scale = { 1,1,1 };
    DirectX::XMFLOAT4X4 transform = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
    };
    float radius = 0.5f;
    float height = 2.0f;
    float gravity = -1.0f;
    DirectX::XMFLOAT3 velocity = { 0,0,0 };
    bool isGround = false;
    int health = 5;
    int maxHealth = 5;
    float invincibleTimer = 1.0f;
    float friction = 0.5f;
    float acceleration = 1.0f;
    float maxMoveSpeed = 5.0f;
    float moveVecX = 0.0f;
    float moveVecZ = 0.0f;

    float airControl = 3.0f;
    
    float stepOffset = 1.0f;

    float slopeRate = 1.0f;
    
};