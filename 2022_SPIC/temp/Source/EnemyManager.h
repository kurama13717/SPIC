#pragma once
#include <vector>
#include "Enemy.h"

class EnemyManager
{
private:
    EnemyManager() {}
    ~EnemyManager() {}
    //エネミーの同士の衝突
    void CollisionEnemyVsEnemies();
public:
    static EnemyManager& Instance()
    {
        static EnemyManager instance;
        return instance;
    }
    void Update(float elapsedTime);
    void Render(ID3D11DeviceContext* dc, Shader* shader);
    void DrawDebugPrimitive();
    //エネミー登録
    void Register(Enemy* enemy);
    void Clear();
    //エネミーの数取得
    int GetEnemyCount() const { return static_cast<int>(enemies.size()); }
    //エネミー取得
    Enemy* GetEnemy(int index) { return enemies.at(index); }
    //エネミー削除
    void Remove(Enemy* enemy);
private:
    std::vector<Enemy*> enemies;
    std::vector<Enemy*> remove;
};