#include "EnemySlime.h"
#include "Graphics/Graphics.h"
#include "Mathf.h"
#include "Player.h"
#include "Collision.h"
EnemySlime::EnemySlime()
{
    model = new Model("Data/Model/Slime/Slime.mdl");
    scale.x = scale.y = scale.z = 0.01f;
    radius = 0.5f;
    height = 1.0f;
    TransitionWanderState();
}
EnemySlime::~EnemySlime()
{
    delete model;
}
void EnemySlime::Update(float elapsedTime)
{
    switch (state)
    {
    case State::Wander:
        UpdateWanderState(elapsedTime);
        break;
    case State::Idle:
        UpdateIdleState(elapsedTime);
        break;
    case State::Pursuit:
        UpdatePursuitState(elapsedTime);
        break;
    case State::Attack:
        UpdateAttackState(elapsedTime);
        break;
    case State::IdleBattle:
        UpdateIdleBattleState(elapsedTime);
        break;
    case State::Damage:
        UpdateDamageState(elapsedTime);
        break;
    case State::Death:
        UpdateDeathState(elapsedTime);
        break;
    }
    UpdateTransform();
    UpdateInvincibleTimer(elapsedTime);
    UpdateVelocity(elapsedTime);
    model->UpdateAnimation(elapsedTime);
    model->UpdateTransform(transform);
}
void EnemySlime::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}
void EnemySlime::OnDamaged()
{
    TransitionDamageState();
}

void EnemySlime::OnDead()
{
    //Destroy();
    TransitionDeathState();
}

void EnemySlime::DrawDebugPrimitive()
{
    Enemy::DrawDebugPrimitive();

    DebugRenderer* debugRemder = Graphics::Instance().GetDebugRenderer();

    debugRemder->DrawCylinder(territoryOrigin, territoryRange, 1.0f, DirectX::XMFLOAT4(0, 1, 0, 1));
    debugRemder->DrawSphere(targetPosition, radius, DirectX::XMFLOAT4(1, 1, 0, 1));
    debugRemder->DrawCylinder(position, searchRange, 1.0f, DirectX::XMFLOAT4(0, 0, 1, 1));
    debugRemder->DrawCylinder(position, attackRenge, 1.0f, DirectX::XMFLOAT4(1, 0, 0, 1));
}

void EnemySlime::SetTerritory(const DirectX::XMFLOAT3& origin, float range)
{
    territoryOrigin = origin;
    territoryRange = range;
}
void EnemySlime::SetRandomTargetPosition()
{
    float theta = Mathf::RandomRange(-DirectX::XM_PI, DirectX::XM_PI);
    float range = Mathf::RandomRange(0.0f, territoryRange);
    targetPosition.x = territoryOrigin.x + sinf(theta) * range;
    targetPosition.y = territoryOrigin.y;
    targetPosition.z = territoryOrigin.z + cosf(theta) * range;
}
void EnemySlime::MoveToTarget(float elapsedTime, float speedRate)
{
    float vx = targetPosition.x - position.x;
    float vz = targetPosition.z - position.z;
    float dist = sqrtf(vx * vx + vz * vz);
    vx /= dist;
    vz /= dist;
    Move(vx, vz, moveSpeed * speedRate);
    Turn(elapsedTime, vx, vz, turnSpeed * speedRate);
}

void EnemySlime::TransitionWanderState()
{
    state = State::Wander;
    SetRandomTargetPosition();
    model->PlayAnimation(Anim_WalkFWD, true);
}
void EnemySlime::UpdateWanderState(float elapsedTime)
{
    float vx = targetPosition.x - position.x;
    float vz = targetPosition.z - position.z;
    float distSq = vx * vx + vz * vz;
    if (distSq < radius * radius)
    {
        //SetRandomTargetPosition();
        TransitionIdleState();
    }
    MoveToTarget(elapsedTime, 0.5f);
    if (SearchPlayer())
    {
        TransitionPursuitState();
    }
}

void EnemySlime::TransitionIdleState()
{
    state = State::Idle;
    stateTimer = Mathf::RandomRange(3.0f, 5.0f);
    model->PlayAnimation(Anim_IdleNormal, true);
}
void EnemySlime::UpdateIdleState(float elapsedTime)
{
    stateTimer -= elapsedTime;
    if (stateTimer < 0.0f)
    {
        TransitionWanderState();
    }
    if (SearchPlayer())
    {
        TransitionPursuitState();
    }
}

bool EnemySlime::SearchPlayer()
{
    const DirectX::XMFLOAT3& playerPosition = Player::Instance().GetPosition();
    float vx = playerPosition.x - position.x;
    float vy = playerPosition.y - position.y;
    float vz = playerPosition.z - position.z;
    float dist = sqrtf(vx * vx + vy * vy + vz * vz);
    if (dist < searchRange)
    {
        float distXZ = sqrtf(vx * vx + vz * vz);
        vx /= distXZ;
        vz /= distXZ;
        float frontX = sinf(angle.y);
        float frontZ = cosf(angle.y);
        float dot = (frontX * vx) + (frontZ * vz);
        if (dot > 0.0f)
        {
            return true;
        }
    }
    return false;
}

void EnemySlime::TransitionPursuitState()
{
    state = State::Pursuit;
    stateTimer = Mathf::RandomRange(3.0f, 5.0f);
    model->PlayAnimation(Anim_RunFWD, true);
}
void EnemySlime::UpdatePursuitState(float elapsedTime)
{
    targetPosition = Player::Instance().GetPosition();
    MoveToTarget(elapsedTime, 1.0f);
    stateTimer -= elapsedTime;
    if (stateTimer < 0.0f)
    {
        TransitionIdleState();
    }
    float vx = targetPosition.x - position.x;
    float vy = targetPosition.y - position.y;
    float vz = targetPosition.z - position.z;
    float dist = sqrtf(vx * vx + vy * vy + vz * vz);
    if (dist < attackRenge)
    {
        TransitionAttackState();
    }
}

void EnemySlime::CollisitionNodeVsPlayer(const char* nodeName, float nodeRadius)
{
    Model::Node* node = model->FindNode(nodeName);
    if (node != nullptr)
    {
        DirectX::XMFLOAT3 nodePosition(
            node->worldTransform._41,
            node->worldTransform._42,
            node->worldTransform._43
        );
        Graphics::Instance().GetDebugRenderer()->DrawSphere(
            nodePosition, nodeRadius, DirectX::XMFLOAT4(0, 0, 1, 1));

        Player& player = Player::Instance();
        DirectX::XMFLOAT3 outPosition;
        if (Collision::IntersectSphereVsCylinder(
            nodePosition,
            nodeRadius,
            player.GetPosition(),
            player.GetRadius(),
            player.GetHeight(),
            outPosition))
        {
            if (player.applyDamage(1, 0.5f))
            {
                DirectX::XMFLOAT3 vec;
                vec.x = outPosition.x - nodePosition.x;
                vec.z = outPosition.z - nodePosition.z;
                float length = sqrtf(vec.x * vec.x + vec.z * vec.z);
                vec.x /= length;
                vec.z /= length;

                float power = 10.0f;
                vec.x *= power;
                vec.z *= power;
                vec.y = 5.0f;
                player.AddImpulse(vec);
            }
        }
    }
}

void EnemySlime::TransitionAttackState()
{
    state = State::Attack;
    model->PlayAnimation(Anim_Attack1, false);
}
void EnemySlime::UpdateAttackState(float elapsedTimer)
{
    float animationTime = model->GetCurrentAnimationSeconds();
    if (animationTime >= 0.1f && animationTime <= 0.35f)
    {
        CollisitionNodeVsPlayer("EyeBall", 0.2f);
    }
    //攻撃が終わったら攻撃待機モードに移行
    if (!model->IsPlayAnimation())
    {
        TransitionIdleBattleState();
    }
}

void EnemySlime::TransitionIdleBattleState()
{
    state = State::IdleBattle;
    stateTimer = Mathf::RandomRange(2.0f, 3.0f);
    model->PlayAnimation(Anim_IdleBattle, true);
}
void EnemySlime::UpdateIdleBattleState(float elapsedTime)
{
    targetPosition = Player::Instance().GetPosition();
    stateTimer -= elapsedTime;
    if (stateTimer < 0.0f)
    {
        float vx = targetPosition.x - position.x;
        float vy = targetPosition.y - position.y;
        float vz = targetPosition.z - position.z;
        float dist = sqrtf(vx * vx + vy * vy + vz * vz);
        if (dist < attackRenge)
        {
            TransitionAttackState();
        }
        else
        {
            TransitionWanderState();
        }
    }
    MoveToTarget(elapsedTime, 0.0f);
}

void EnemySlime::TransitionDamageState()
{
    state = State::Damage;
    model->PlayAnimation(Anim_GetHit, false);
}
void EnemySlime::UpdateDamageState(float elapsedTime)
{
    if (!model->IsPlayAnimation())
    {
        TransitionIdleBattleState();
    }
}

void EnemySlime::TransitionDeathState()
{
    state = State::Death;
    model->PlayAnimation(Anim_Die, false);
}
void EnemySlime::UpdateDeathState(float elapsedTime)
{
    if (!model->IsPlayAnimation())
    {
        Destroy();
    }
}