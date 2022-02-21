#pragma once
#include "Graphics/Model.h"
#include "Stage.h"



class Cube : public Stage
{
public:
	Cube();
	~Cube()override;
	void Update(float elapsedTime)override;
	void Render(ID3D11DeviceContext* dc, Shader* shader) {};
	void Render(ID3D11DeviceContext* dc, Shader* shader, bool flag = false);
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;
	void UpdateTransform();

	void DrawDebugGUI();

private:
	Model* flat_Down = nullptr;
	Model* flat_Up = nullptr;
	Model* flat_Left = nullptr;
	Model* flat_Right = nullptr;
	Model* flat_Forward = nullptr;
	Model* flat_Back = nullptr;

};