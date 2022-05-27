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


// �Q�[���V�[��
class SceneGame : public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// ������
	void Initialize()override;

	// �I����
	void Finalize()override;

	// �X�V����
	void Update(float elapsedTime)override;

	// �`�揈��
	void Render()override;



private:
	//�G�l�~�[HP�폜
	void RenderEnemyGauge(ID3D11DeviceContext* dc,
		const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection);

	// ��l�̃J�����C�j�V�����C�Y
	void FpsCameraInitialize(int BeforeMode);
	// �ʑI���J�����C�j�V�����C�Y
	void ViewCameraInitialize();
	// ��щ��J�����C�j�V�����C�Y
	void SpectatorCameraInitialize(int BeforeMode);

	// �ʑI��
	void ChooseSurface();

	// �J�����X�s�[�h�֘A
	void ChangeSpeed();

	void SetObjects();

	// �Q�[���V�[���w���v
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
	// �J�������[�h
	//int cameramode = 0;
	enum  Mode
	{
		viewMode,
		fpsMode,
		spectatorMode,
	};

	int BeforeCM = 0;

	// �ł��o���ʒu
	DirectX::XMFLOAT3 fixedpositions[4];
	DirectX::XMFLOAT3 fixedangles[4];

	// �ʑI��p
	bool delayflag, delayflag2 = false;
	float delaytimer, delaytimer2 = 0.0f;
	int selectedsurface = 0;
	float axisX = 0;

	bool BackFlag = false;
	float PushPower = 0;

	//�ێ�
	DirectX::XMFLOAT3 KeepAngle;

	// �N���X�w�A
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