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
//���x�����X�V
void Character::UpdateVelocity(float elapsedTime)
{
    //�o�߃t���[��
    float elapsedFrame = 60.0f * elapsedTime;
    ////�������͍X�V����
    //UpdateVerticalVelocity(elapsedFrame);
    ////�����ړ��X�V
    //UpdateVerticalMove(elapsedTime);
    //�������͍X�V����
    UpdateHorizontalVelocity(elapsedFrame);
    //�����ړ��X�V����
    UpdateHorizontalMove(elapsedTime);
}
//�Ռ�
void Character::AddImpulse(const DirectX::XMFLOAT3& impulse)
{
    velocity.x += impulse.x;
    velocity.y += impulse.y;
    velocity.z += impulse.z;
}
//�������x�X�V����
void Character::UpdateVerticalVelocity(float elapsedTime)
{
    //�d�͏���
    velocity.y += gravity * elapsedTime;
}
//�����ړ��X�V
void Character::UpdateVerticalMove(float elapsedTime)
{
#if 0
    //�ړ�����
    position.y += velocity.y * elapsedTime;
    //�n�ʔ���
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
    //�L�����N�^�[��Y�������̃x�N�g��
    DirectX::XMFLOAT3 normal = { 0,1,0 };
    //�����̍������n��(0.0f)��艺�̎�
    if (my < 0.0f)
    {
        DirectX::XMFLOAT3 start = { position.x ,position.y + stepOffset,position.z };
        DirectX::XMFLOAT3 end = { position.x,position.y + my,position.z };
        
        HitResult hit;
        if (StageManager::Instance().RayCast(start, end, hit))
        {
            //�@���x�N�g��
            normal = hit.normal;
            position = hit.position;
            //�X�Η��̌v�Z
            float normalLengthXZ = sqrtf(hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z);
            slopeRate = 1.0f - (hit.normal.y / (normalLengthXZ + hit.normal.y));
            if (!isGround)
            {
                OnLanding();
            }
            isGround = true;
            velocity.y = 0.0f;
            // ��]
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
     //�n�ʂ̌����ɉ����悤��XZ����]

    {
        // Y�����@���x�N�g�������Ɍ����I�C���[�p��]���Z�o����
        angle.x = atan2f(normal.z, normal.y);
        angle.z = -atan2f(normal.x, normal.y);
        //���`�⊮�Ŋ��炩�ɉ�]����
        float ax = atan2f(normal.z, normal.y);
        float az = -atan2f(normal.x, normal.y);
        angle.x = Mathf::Lerp(angle.x, ax, 0.2f);
        angle.z = Mathf::Lerp(angle.z, az, 0.2f);
    }
#endif
}
void Character::UpdateHorizontalVelocity(float elapasedFrame)
{
    //�΂߂̑���
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
            //������
            float acceleration = this->acceleration * elapasedFrame;
            if (!IsGround())acceleration *= airControl;
            velocity.x += moveVecX * acceleration;
            velocity.z += moveVecZ * acceleration;
            //�ő呬�x����
            float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
            if (length > maxMoveSpeed)
            {
                float vx = velocity.x / length;
                float vz = velocity.z / length;
                velocity.x = vx * maxMoveSpeed;
                velocity.z = vz * maxMoveSpeed;
            }
            //������␳
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

    //�������͗ʌv�Z
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
            //�t�x�N�g���Ɩ@���x�N�g���̓���
            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(DirectX::XMVectorNegate(Vec), Normal);

            // �␳�ʒu�̌v�Z
            //�@���x�N�g��*����+���C�̏I�[//R�x�N�g�����߂�
            DirectX::XMVECTOR CollectPosition = DirectX::XMVectorMultiplyAdd(Normal, Dot, End);
            DirectX::XMFLOAT3 collectPosition;
            DirectX::XMStoreFloat3(&collectPosition, CollectPosition);
            // �ǂ�������փ��C�L���X�g
            HitResult hit2;
            if (!StageManager::Instance().RayCast(hit.position, collectPosition, hit2))
            {
                // �ǂ�������ŕǂɓ�����Ȃ�������␳�ʒu�Ɉړ�
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
    //�i�s�x�N�g�����[���x�N�g���Ŏ��s���Ȃ�
    float length = sqrtf(vx * vx + vz * vz);
    if (vx == 0 && vz == 0)  return;
    //�i�s�x�N�g���P�ʉ�
    vx /= length;
    vz /= length;
    //��]����O���������߂�
    float frontX = sinf(angle.y);
    float frontZ = cosf(angle.y);

    //�O��
    float dot = (vx * frontX) + (vz * frontZ);
    //�p�x�������Ȃ�ƒl��0�ɂ���
    float rot = 1.0f - dot;
    if (rotateSpeed > rot)  rotateSpeed = rot;
    //���E����̂��߂̓��όv�Z
    float cross = (vx * frontZ) - (vz * frontX);
    //2D�̊O�ϒl�����������ɂ���č��E���肪�����Ȃ���
    //���E����������Ȃ����Ƃō��E��]��I������
    if (cross < 0.0f)//����]
    {
        angle.y -= rotateSpeed;
    }
    else//�E��]
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

//���G���ԍX�V
void Character::UpdateInvincibleTimer(float elapsedTime)
{
    if (invincibleTimer > 0.0f)
    {
        invincibleTimer -= elapsedTime;
    }
}


