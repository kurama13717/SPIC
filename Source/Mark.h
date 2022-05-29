#pragma once
#include "Graphics/Model.h"
#include "Stage.h"
#include "StageManager.h"
#include "Audio/Audio.h"
#include"BulletManager.h"
#include "Input/Input.h"



class Mark : public Stage
{
public:
	Mark(int StageNum);
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



	std::vector<std::unique_ptr<Model>> model;

	//std::vector<std::unique_ptr<MarkSplit>> markSplit;

	//std::vector<std::unique_ptr<MarkSplit>> marksplit;


	//std::vector<std::unique_ptr<Model>> modelsplit;

	//std::vector<std::unique_ptr<AudioSource>> MusicalScales;

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
	std::unique_ptr<AudioSource> Fa;
	std::unique_ptr<AudioSource> So;
	std::unique_ptr<AudioSource> Ra;

};


class MarkSplit : public Stage
{
public:

	MarkSplit();
	~MarkSplit()override {};


	void UpdateTransform();


	void Update(float elapsedTime)override;

	void Render(ID3D11DeviceContext* dc, Shader* shader) {};

	void DrawDebugGUI();

	void Render(ID3D11DeviceContext* dc, Shader* shader, int flag = false)override;

	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;


private:
	std::vector<std::unique_ptr<Model>> modelsplit;
	std::vector<std::unique_ptr<Model>> modelcrack;  //‹T—ôƒ‚ƒfƒ‹
	std::vector<MarkSplit> marksp[10];
	DirectX::XMFLOAT3 velocity = { 0,0,0 };
	bool MarkSpflag[50];
	bool testSpflag[10];
	bool scaleFlag = false;

	int a = 5;
	int b = -5;
	float c = 0.0f;

	float fram = 300.0f;



};

