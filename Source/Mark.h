#pragma once
#include "Graphics/Model.h"
#include "Stage.h"
#include "StageManager.h"
#include "Audio/Audio.h"
#include"BulletManager.h"


class Mark : public Stage
{
public:
	Mark();
	~Mark()override;
	void Update(float elapsedTime)override;
	void Render(ID3D11DeviceContext* dc, Shader* shader) {};
	void Render(ID3D11DeviceContext* dc, Shader* shader, int flag = false);
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;
	void UpdateTransform();
	void Destroy();
	bool ClearFlag();
	void DrawDebugGUI();

	void Check();

private:
	Model* mark0 = nullptr;
	Model* mark1 = nullptr;
	Model* mark2 = nullptr;



	std::vector<std::unique_ptr<Model>> model;


	//std::vector<std::tuple<std::unique_ptr<Model>, std::unique_ptr<Stage>>> ms;
	//
	//std::get<1>(ms[0]);


	
	int MarkHitCount = 0;

	bool flag0 = false;
	bool flag1 = false;
	bool flag2 = false;

	bool flag[50];


	Stage* stage = nullptr;
	std::unique_ptr<AudioSource> Do;
	std::unique_ptr<AudioSource> Re;
	std::unique_ptr<AudioSource> Mi;

};