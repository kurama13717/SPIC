#pragma once

#include "Graphics/Shader.h"
#include "Collision.h"

class Stage
{
public:
    Stage() {}
    virtual ~Stage() {}
    virtual void Update(float elapsedTime) = 0;
   // virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;
    virtual void Render(ID3D11DeviceContext* dc, Shader* shader, int flag) = 0;
    virtual bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit) = 0;

protected:
    DirectX::XMFLOAT3   position[10] = {};
    DirectX::XMFLOAT3   angle[10] = {};
    DirectX::XMFLOAT3   scale[10] = {};
    DirectX::XMFLOAT4X4 transform[10];

};