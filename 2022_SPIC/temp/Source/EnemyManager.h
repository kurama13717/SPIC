#pragma once
#include <vector>
#include "Enemy.h"

class EnemyManager
{
private:
    EnemyManager() {}
    ~EnemyManager() {}
    //�G�l�~�[�̓��m�̏Փ�
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
    //�G�l�~�[�o�^
    void Register(Enemy* enemy);
    void Clear();
    //�G�l�~�[�̐��擾
    int GetEnemyCount() const { return static_cast<int>(enemies.size()); }
    //�G�l�~�[�擾
    Enemy* GetEnemy(int index) { return enemies.at(index); }
    //�G�l�~�[�폜
    void Remove(Enemy* enemy);
private:
    std::vector<Enemy*> enemies;
    std::vector<Enemy*> remove;
};