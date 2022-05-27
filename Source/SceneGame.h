#pragma once
#include "Player.h"
#include "CameraController.h"
#include "EnemyManager.h"
#include "EnemySlime.h"
#include "Scene.h"
#include "Graphics/Sprite.h"
#include "CoordinateTransformation.h"
#include "Audio/Audio.h"
#include "Audio/AudioSource.h"
#include "Shake.h"
#include "Cube.h"
#include "BulletStraite.h"
#include "Bullet.h"
#include "Mark.h"


// ゲームシーン
class SceneGame : public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// 初期化
	void Initialize()override;

	// 終了化
	void Finalize()override;

	// 更新処理
	void Update(float elapsedTime)override;

	// 描画処理
	void Render()override;



private:
	//エネミーHP削除
	void RenderEnemyGauge(ID3D11DeviceContext* dc,
		const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection);

	// 一人称カメライニシャライズ
	void FpsCameraInitialize(int BeforeMode);
	// 面選択カメライニシャライズ
	void ViewCameraInitialize();
	// 飛び回りカメライニシャライズ
	void SpectatorCameraInitialize(int BeforeMode);

	// 面選択
	void ChooseSurface();

	// カメラスピード関連
	void ChangeSpeed();

	void SetObjects();

	// ゲームシーンヘルプ
	void Help();

private:
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();
	RenderContext rc;
	Player* player = nullptr;
	Cube* cube = nullptr;
	Bullet* bullet = nullptr;
	Mark* mark = nullptr;

	CameraController* cameracontroller = nullptr;

	EnemySlime* enemyslime = nullptr;
	Sprite* gauge = nullptr;
	CoordinateTransformation* coordinateTransformation = nullptr;
	Shake& shake = Shake::Instance();


private:
	float screenWidth = static_cast<float>(graphics.GetScreenWidth());
	float screenHeight = static_cast<float>(graphics.GetScreenHeight());
	// カメラモード
	//int cameramode = 0;
	enum  Mode
	{
		viewMode,
		fpsMode,
		spectatorMode,
	};

	int BeforeCM = 0;

	// 打ち出し位置
	DirectX::XMFLOAT3 fixedpositions[4];
	DirectX::XMFLOAT3 fixedangles[4];

	// 面選択用
	bool delayflag, delayflag2 = false;
	float delaytimer, delaytimer2 = 0.0f;
	int selectedsurface = 0;
	float axisX = 0;

	bool BackFlag = false;
	float PushPower = 0;

	//保持
	DirectX::XMFLOAT3 KeepAngle;

	// クロスヘア
	Sprite* cross = nullptr;

	Sprite* Menu = nullptr;
	Sprite* MenuGame = nullptr;
	Sprite* MenuHelp = nullptr;
	Sprite* MenuTitle = nullptr;

	Sprite* SpeedSprite_Slow = nullptr;
	Sprite* SpeedSprite_Normal = nullptr;
	Sprite* SpeedSprite_Fast = nullptr;

	bool isMenuFlag = false;
	int MenuMode = 0;
	float axisY = 0;
	bool MenuMove_U = false;
	bool MenuMove_D = false;
	bool Moveble = false;

	bool selectable = false;
	bool slide_R = false;
	bool slide_L = false;

	float MenuWidth = 300;
	float MenuHeight = 100;

	Sprite* Rule = nullptr;
	Sprite* Signal = nullptr;
	Sprite* B = nullptr;
	bool HelpFlag = false;
	int SignalTimer = 0;
	int SceneCount = 1;
	float RulePosX = 0.0f;
	bool RuleMove_R = false;
	bool RuleMove_L = false;
	DirectX::XMFLOAT2 Pos = { 0.0f,0.0f };

	enum  menu
	{
		menuGame,
		menuHelp,
		menuTitle,
	};
	int menuDelayTimer = 0;
	DirectX::XMFLOAT4 menuGameColor = { 1,1,1,1 };
	DirectX::XMFLOAT4 menuHelpColor = { 1,1,1,1 };
	DirectX::XMFLOAT4 menuTitleColor = { 1,1,1,1 };

	DirectX::XMFLOAT2 menuGamePos = { screenWidth / 2 - MenuWidth / 2,200 };
	DirectX::XMFLOAT2 menuHelpPos = { screenWidth / 2 - MenuWidth / 2,400 };
	DirectX::XMFLOAT2 menuTitlePos = { screenWidth / 2 - MenuWidth / 2,600 };

	DirectX::XMFLOAT2 menuGameSize = { MenuWidth,MenuHeight };
	DirectX::XMFLOAT2 menuHelpSize = { MenuWidth,MenuHeight };
	DirectX::XMFLOAT2 menuTitleSize = { MenuWidth,MenuHeight };

	int speedNo = 0;
	float rollSpeeds[3] =
	{
		0.5f,
		1.0f,
		1.5f
	};
	float color_slow = 0.0f;
	float color_normal = 0.0f;
	float color_fast = 0.0f;
};