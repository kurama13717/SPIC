#pragma once
#include "Graphics/Shader.h"
#include "Character.h"
class EnemyManager;
class Enemy : public Character
{
public:
    Enemy() {}
    ~Enemy() override {}
    virtual void DrawDebugPrimitive();
    void Destroy();
    virtual void Update(float elapsedTime) = 0;
    virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;
protected:
    EnemyManager* manager = nullptr;
};
