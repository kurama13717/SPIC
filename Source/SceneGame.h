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
#include "Space.h"


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
	SpaceDome* SpDome = nullptr;
	Bullet* bullet = nullptr;
	Mark* mark = nullptr;

	CameraController* cameracontroller = nullptr;

	EnemySlime* enemyslime = nullptr;
	Sprite* gauge = nullptr;
	CoordinateTransformation* coordinateTransformation = nullptr;
	Shake& shake = Shake::Instance();

	std::unique_ptr<AudioSource> GameBGM;


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
	int selectedsurface = 0;
	int moveTimer_Surface = 0;

	// 入力制限用
	float axisX = 0;
	float axisY = 0;
	bool inputtable = false;
	bool input_Right = false;
	bool input_Left = false;
	bool input_Up = false;
	bool input_Down = false;
	bool moving_Right = false;
	bool moving_Left = false;
	bool moving_Up = false;
	bool moving_Down = false;

	bool BackFlag = false;
	float PushPower = 0;

	bool isClear = false;
	bool isClear2 = false;
	int countForTest = 0;
	int clearTimer = 0;

	//保持
	DirectX::XMFLOAT3 KeepAngle;

	// クロスヘア
	Sprite* cross = nullptr;

	Sprite* Filter = nullptr;
	Sprite* MenuGame = nullptr;
	Sprite* MenuHelp = nullptr;
	Sprite* MenuTitle = nullptr;

	Sprite* SpeedSprite_Slow = nullptr;
	Sprite* SpeedSprite_Normal = nullptr;
	Sprite* SpeedSprite_Fast = nullptr;

	Sprite* clearSprite = nullptr;
	Sprite* nextSprite = nullptr;
	Sprite* toTitleSptite = nullptr;

	Sprite* cameraModeSprite_Surface = nullptr;
	Sprite* cameraModeSprite_Fire = nullptr;
	Sprite* cameraModeSprite_Fly = nullptr;

	bool isMenuFlag = false;
	int MenuMode = 0;
	int select_Clear = 0;

	float MenuWidth = 300;
	float MenuHeight = 100;

	float clearWidth = 600;
	float clearHeight = 100;

	Sprite* Rule = nullptr;
	Sprite* Signal = nullptr;
	Sprite* B = nullptr;
	bool HelpFlag = false;
	int SignalTimer = 0;
	int SceneCount = 1;
	float RulePosX = 0.0f;
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

	DirectX::XMFLOAT2 clearNextPos = { screenWidth / 2 - clearWidth / 2,400 };
	DirectX::XMFLOAT2 clearNextSize = { clearWidth,clearHeight };
	DirectX::XMFLOAT2 clearToTitlePos = { screenWidth / 2 - clearWidth / 2,600 };
	DirectX::XMFLOAT2 clearToTitleSize = { clearWidth,clearHeight };

	int speedNo = 0;
	float rollSpeeds[3] =
	{
		1.5f,
		1.0f,
		0.2f,
	};
	float color_slow = 0.0f;
	float color_normal = 0.0f;
	float color_fast = 0.0f;

	float color_Surface = 0.0f;
	float color_Fire = 0.0f;
	float color_Fly = 0.0f;
};