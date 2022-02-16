#include "Enemy.h"
#include "EnemyManager.h"
#include "Graphics/Graphics.h"

void Enemy::DrawDebugPrimitive()
{
    DebugRenderer* debugRendere = Graphics::Instance().GetDebugRenderer();
    debugRendere->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 1, 0, 1));
}

void Enemy::Destroy()
{
    EnemyManager::Instance().Remove(this);
}