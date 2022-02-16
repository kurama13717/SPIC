#pragma once
#include<DirectXMath.h>
class Character
{
public:
    Character() {}
    virtual ~Character() {}
    void UpdateTransform();

    //ゲッターセッター
    const DirectX::XMFLOAT3& GetPosition()const { return position; }
    void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }
    const DirectX::XMFLOAT3& GetAngle()const { return angle; }
    void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }
    const DirectX::XMFLOAT3& GetScale() const { return scale; }
    void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }
    //衝撃を与える
    void AddImpulse(const DirectX::XMFLOAT3& impulse);
    //半径取得
    float GetRadius() const { return radius; }
    //高さ取得
    float GetHeight()const { return height; }
    bool IsGround()const { return isGround; }
    //ダメージ与える
    bool applyDamage(int damage, float invincibleTime);

    //健康状態取得
    int GetHealth()const { return health; }
    //最大健康状態
    int GetMaxHealth()const { return maxHealth; }
private:
    //垂直速度更新
    void UpdateVerticalVelocity(float elapsedTime);
    //垂直移動更新
    void UpdateVerticalMove(float elapsedTime);
    //水平速度更新処理
    void UpdateHorizontalVelocity(float elapasedFrame);
    //水平移動更新処理
    void UpdateHorizontalMove(float elapsedTime);
protected:
    //void Move(float elapsedTime, float vx, float vz, float speed);
    void Move(float vx, float vy, float speed);
    void Turn(float elapsedTime, float vx, float vz, float speed);
    void Jump(float speed);
    void UpdateVelocity(float elapsedTime);
    //無敵時間更新
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