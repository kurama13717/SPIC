#include "Character.h"
#include "Mathf.h"
#include "StageManager.h"
void Character::UpdateTransform()
{
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x,scale.y,scale.z);
    //DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x,angle.y,angle.z);
    DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
    DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
    DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
    DirectX::XMMATRIX R = Y * X * Z;
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x,position.y,position.z);
    DirectX::XMMATRIX W = S * R * T;
    DirectX::XMStoreFloat4x4(&transform, W);

}
void Character::Move(float vx, float vz, float speed)
{
    //speed *= elapsedTime;
    //position.x += vx * speed;
    //position.z += vz * speed;
    moveVecX = vx;
    moveVecZ = vz;
    maxMoveSpeed = speed;
}
//void Character::Move(float elapsedTime, float vx, float vz, float speed)
//{
//    speed *= elapsedTime;
//    position.x += vx * speed;
//    position.z += vz * speed;
//}
void Character::Jump(float speed)
{
    velocity.y += speed;
}
//速度処理更新
void Character::UpdateVelocity(float elapsedTime)
{
    //経過フレーム
    float elapsedFrame = 60.0f * elapsedTime;
    ////垂直速力更新処理
    //UpdateVerticalVelocity(elapsedFrame);
    ////垂直移動更新
    //UpdateVerticalMove(elapsedTime);
    //水平速力更新処理
    UpdateHorizontalVelocity(elapsedFrame);
    //水平移動更新処理
    UpdateHorizontalMove(elapsedTime);
}
//衝撃
void Character::AddImpulse(const DirectX::XMFLOAT3& impulse)
{
    velocity.x += impulse.x;
    velocity.y += impulse.y;
    velocity.z += impulse.z;
}
//垂直速度更新処理
void Character::UpdateVerticalVelocity(float elapsedTime)
{
    //重力処理
    velocity.y += gravity * elapsedTime;
}
//垂直移動更新
void Character::UpdateVerticalMove(float elapsedTime)
{
#if 0
    //移動処理
    position.y += velocity.y * elapsedTime;
    //地面判定
    if (position.y < 0.0f)
    {
        position.y = 0.0f;
        velocity.y = 0.0f;
        if (!IsGround())
        {
            OnLanding();
        }
        isGround = true;
    }
    else
    {
        isGround = false;
    }
#else 
    float my = velocity.y * elapsedTime;
    slopeRate = 0.0f;
    //キャラクターのY軸方向のベクトル
    DirectX::XMFLOAT3 normal = { 0,1,0 };
    //自分の高さが地面(0.0f)より下の時
    if (my < 0.0f)
    {
        DirectX::XMFLOAT3 start = { position.x ,position.y + stepOffset,position.z };
        DirectX::XMFLOAT3 end = { position.x,position.y + my,position.z };
        
        HitResult hit;
        if (StageManager::Instance().RayCast(start, end, hit))
        {
            //法線ベクトル
            normal = hit.normal;
            position = hit.position;
            //傾斜率の計算
            float normalLengthXZ = sqrtf(hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z);
            slopeRate = 1.0f - (hit.normal.y / (normalLengthXZ + hit.normal.y));
            if (!isGround)
            {
                OnLanding();
            }
            isGround = true;
            velocity.y = 0.0f;
            // 回転
            angle.y += hit.rotation.y;
        }
        else
        {
            position.y += my;
            isGround = false;
        }

    }
    else if (my > 0.0f)
    {
        position.y += my;
        isGround = false;
    }
     //地面の向きに沿うようにXZ軸回転

    {
        // Y軸が法線ベクトル方向に向くオイラー角回転を算出する
        angle.x = atan2f(normal.z, normal.y);
        angle.z = -atan2f(normal.x, normal.y);
        //線形補完で滑らかに回転する
        float ax = atan2f(normal.z, normal.y);
        float az = -atan2f(normal.x, normal.y);
        angle.x = Mathf::Lerp(angle.x, ax, 0.2f);
        angle.z = Mathf::Lerp(angle.z, az, 0.2f);
    }
#endif
}
void Character::UpdateHorizontalVelocity(float elapasedFrame)
{
    //斜めの速力
    float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
    if (length > 0.0f)
    {
        float friction = this->friction * elapasedFrame;
        if (!IsGround())friction *= airControl;

        if (length > friction)
        {
            float vx = velocity.x / length;
            float vz = velocity.z / length;
            velocity.x -= vx * friction;
            velocity.z -= vz * friction;
        }
        else
        {
            velocity.x = 0;
            velocity.z = 0;
        }
    }

    if (length <= maxMoveSpeed)
    {
        float moveVecLength = sqrtf(moveVecX * moveVecX + moveVecZ * moveVecZ);
        if (moveVecLength > 0.0f)
        {
            //加速力
            float acceleration = this->acceleration * elapasedFrame;
            if (!IsGround())acceleration *= airControl;
            velocity.x += moveVecX * acceleration;
            velocity.z += moveVecZ * acceleration;
            //最大速度制限
            float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
            if (length > maxMoveSpeed)
            {
                float vx = velocity.x / length;
                float vz = velocity.z / length;
                velocity.x = vx * maxMoveSpeed;
                velocity.z = vz * maxMoveSpeed;
            }
            //下り坂を補正
            if (isGround && slopeRate > 0.0f)
            {
                velocity.y -= length * slopeRate * elapasedFrame;
            }
        }
    }
    moveVecX = 0.0f;
    moveVecZ = 0.0f;

}
void Character::UpdateHorizontalMove(float elapsedTime)
{
    //position.x += velocity.x * elapsedTime;
    //position.z += velocity.z * elapsedTime

    //水平速力量計算
    float velocityLengthXZ = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
    if (velocityLengthXZ > 0.0f)
    {
        float mx = velocity.x * elapsedTime;
        float mz = velocity.z * elapsedTime;

        DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
        DirectX::XMFLOAT3 end = { position.x + mx, position.y + stepOffset, position.z + mz };

        HitResult hit;
        if (StageManager::Instance().RayCast(start, end, hit))
        {
            DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&start);
            DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);
            DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(End, Start);

            DirectX::XMVECTOR Normal = DirectX::XMLoadFloat3(&hit.normal);
            //逆ベクトルと法線ベクトルの内積
            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(DirectX::XMVectorNegate(Vec), Normal);

            // 補正位置の計算
            //法線ベクトル*内積+レイの終端//Rベクトル求める
            DirectX::XMVECTOR CollectPosition = DirectX::XMVectorMultiplyAdd(Normal, Dot, End);
            DirectX::XMFLOAT3 collectPosition;
            DirectX::XMStoreFloat3(&collectPosition, CollectPosition);
            // 壁ずり方向へレイキャスト
            HitResult hit2;
            if (!StageManager::Instance().RayCast(hit.position, collectPosition, hit2))
            {
                // 壁ずり方向で壁に当たらなかったら補正位置に移動
                position.x = collectPosition.x;
                position.z = collectPosition.z;
            }
            else
            {
                position.x = hit2.position.x;
                position.z = hit2.position.z;
            }
        }
        else
        {
            position.x += mx;
            position.z += mz;
        }
    }
}
void Character::Turn(float elapsedTime, float vx, float vz, float speed)
{
    float rotateSpeed = speed * elapsedTime;
    //進行ベクトルがゼロベクトルで実行しない
    float length = sqrtf(vx * vx + vz * vz);
    if (vx == 0 && vz == 0)  return;
    //進行ベクトル単位化
    vx /= length;
    vz /= length;
    //回転から前方向を求める
    float frontX = sinf(angle.y);
    float frontZ = cosf(angle.y);

    //外積
    float dot = (vx * frontX) + (vz * frontZ);
    //角度が狭くなると値を0にする
    float rot = 1.0f - dot;
    if (rotateSpeed > rot)  rotateSpeed = rot;
    //左右判定のための内積計算
    float cross = (vx * frontZ) - (vz * frontX);
    //2Dの外積値が正か負かによって左右判定がおこなえる
    //左右判定をおこなうことで左右回転を選択する
    if (cross < 0.0f)//左回転
    {
        angle.y -= rotateSpeed;
    }
    else//右回転
    {
        angle.y += rotateSpeed;
    }
}

bool Character::applyDamage(int damage, float invincibleTime)
{
    if (damage == 0)
        return false;
    if (health <= 0)
        return false;
    if (invincibleTimer <= 0.0f)
    {
        health -= damage;
        invincibleTimer = invincibleTime;
    }
    if (health <= 0)
    {
        OnDead();
    }
    else
    {
        OnDamaged();
    }
    return true;
}

//無敵時間更新
void Character::UpdateInvincibleTimer(float elapsedTime)
{
    if (invincibleTimer > 0.0f)
    {
        invincibleTimer -= elapsedTime;
    }
}


