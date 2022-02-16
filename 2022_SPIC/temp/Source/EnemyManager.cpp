#include "EnemyManager.h"
#include "Graphics/Graphics.h"
#include "Collision.h"

void EnemyManager::Update(float elapsedTime)
{
    for (Enemy* enemy : enemies)
    {
        enemy->Update(elapsedTime);
    }
    CollisionEnemyVsEnemies();

    for (Enemy* enemy : remove)
    {
        std::vector<Enemy*>::iterator it = std::find(enemies.begin(), enemies.end(), enemy);
        if (it != enemies.end())
        {
            enemies.erase(it);
        }
        delete enemy;
    }
    remove.clear();
}
void EnemyManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{

    for (Enemy* enemy : enemies)
    {
        enemy->Render(dc,shader);
    }
}
void EnemyManager::DrawDebugPrimitive()
{
    for (Enemy* enemy : enemies)
    {
        enemy->DrawDebugPrimitive();
    }
}
//エネミー登録
void EnemyManager::Register(Enemy* enemy)
{
    enemies.emplace_back(enemy);
}

//エネミー削除
void EnemyManager::Remove(Enemy* enemy)
{
    remove.emplace_back(enemy);
}
void EnemyManager::Clear()
{
    for (Enemy* enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}

void EnemyManager::CollisionEnemyVsEnemies()
{
    int enemyCount = GetEnemyCount();
    for (size_t i = 0; i < enemies.size(); ++i)
    { 
        Enemy* enemyA = enemies.at(i);
        for (size_t j = i + 1; j < enemies.size(); ++j)
        {
            Enemy* enemyB = enemies.at(j);
            DirectX::XMFLOAT3 outPosition;
            //if (Collision::IntersectSphereVsSphere(enemyA->GetPosition(), enemyA->GetRadius(), enemyB->GetPosition(), enemyB->GetRadius(), outPosition))
            //{
            //    enemyB->SetPosition(outPosition);
            //}
            if (Collision::IntersectCylinderVsCylinder(enemyA->GetPosition(),enemyA->GetRadius(),enemyA->GetHeight(),enemyB->GetPosition(),enemyB->GetRadius(),enemyB->GetHeight(),outPosition))
            {
                enemyB->SetPosition(outPosition);
            }
        }

        
    }
}
