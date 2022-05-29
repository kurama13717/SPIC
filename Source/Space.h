#pragma once
#include "Graphics/Model.h"
#include "Stage.h"


class SpaceDome : Stage
{
public:
	SpaceDome();
	~SpaceDome()override {};

	void Update(float elapsedTime)override;

	void Render(ID3D11DeviceContext* dc, Shader* shader, int flag)override;
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override { return false; }
	void UpdateTransform();
private:
	std::vector<std::unique_ptr<Model>> model;

};