#include "Graphics/Graphics.h"
#include<imgui.h>
#include "EffectManager.h"
#include "SceneGame.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "EnemySlime.h"
#include "Input/Input.h"
#include "StageManager.h"
#include "StageMain.h"
#include "Cube.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneTitle.h"
#include "SceneRule.h"

// ������
void SceneGame::Initialize()
{
	//�F�����
	SpDome = new SpaceDome();


	cube = new Cube();
	//stageManager.Register(stageMain);


	mark = new Mark(StageManager::Instance().GetStageNum());
	//stageManager.Register(mark);
	
	StageManager& stageManager = StageManager::Instance();
	BulletManager& bulletManager = BulletManager::Instance();
	
	GameBGM = Audio::Instance().LoadAudioSource("Data/BGM/wav/GameBGM.wav");

	player = new Player();
	cameracontroller = new CameraController();
	//shake.SetShake(2.0f, 5.0f, 8.0f);
	//�J���������ݒ�

	camera.SetLookAt(DirectX::XMFLOAT3(0, 10, -10), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 1, 0));
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);
	cameracontroller->SetAngle(DirectX::XMFLOAT3(DirectX::XMConvertToRadians(15), 0.0f, 0.0f));
	cameracontroller->SetFov(90.0f);

	CameraController::Instance().SetCameraMode(Mode::viewMode);
	ViewCameraInitialize();

	fixedpositions[0] = { 0.0f,20.0f,-18.0f };
	fixedpositions[1] = { 18.0f,20.0f,0.0f };
	fixedpositions[2] = { 0.0f,20.0f,18.0f };
	fixedpositions[3] = { -18.0f,20.0f,0.0f };

	fixedangles[0] = { 0.0f,3.142f,0.0f };
	fixedangles[1] = { 0.0f,1.71f,0.0f };
	fixedangles[2] = { 0.0f,0.0f,0.0f };
	fixedangles[3] = { 0.0f,-1.71f,0.0f };

	speedNo = 1;

	// �X�v���C�g
	gauge = new Sprite("Data/Sprite/yazirusigauge.png");
	cross = new Sprite("Data/Sprite/CrossHair.png");

	Menu = new Sprite();
	MenuGame = new Sprite("Data/Sprite/MenuGame.png");
	MenuHelp = new Sprite("Data/Sprite/MenuHelp.png");
	MenuTitle = new Sprite("Data/Sprite/MenuTitle.png");

	SpeedSprite_Slow = new Sprite("Data/Sprite/CameraSlow.png");
	SpeedSprite_Normal = new Sprite("Data/Sprite/CameraNormal.png");
	SpeedSprite_Fast = new Sprite("Data/Sprite/CameraFast.png");

	Rule = new Sprite("Data/Sprite/Rule.png");
	Signal = new Sprite("Data/Sprite/Signal.png");
	B = new Sprite("Data/Sprite/Bbutton.png");

	ID3D11Device* device = graphics.GetDevice();
}

// �I����
void SceneGame::Finalize()
{
	// �X�v���C�g�I����
	if (gauge != nullptr)
	{
		delete gauge;
		gauge = nullptr;
	}
	if (cross != nullptr)
	{
		delete cross;
		cross = nullptr;
	}
	if (Menu != nullptr)
	{
		delete Menu;
		Menu = nullptr;
	}
	if (MenuGame != nullptr)
	{
		delete MenuGame;
		MenuGame = nullptr;
	}
	if (MenuHelp != nullptr)
	{
		delete MenuHelp;
		MenuHelp = nullptr;
	}
	if (MenuTitle != nullptr)
	{
		delete MenuTitle;
		MenuTitle = nullptr;
	}
	if (Rule != nullptr)
	{
		delete Rule;
		Rule = nullptr;
	}
	if (Signal != nullptr)
	{
		delete Signal;
		Signal = nullptr;
	}
	if (B != nullptr)
	{
		delete B;
		B = nullptr;
	}
	if (SpeedSprite_Slow != nullptr)
	{
		delete SpeedSprite_Slow;
		SpeedSprite_Slow = nullptr;
	}
	if (SpeedSprite_Normal != nullptr)
	{
		delete SpeedSprite_Normal;
		SpeedSprite_Normal = nullptr;
	}
	if (SpeedSprite_Fast != nullptr)
	{
		delete SpeedSprite_Fast;
		SpeedSprite_Fast = nullptr;
	}
	/*EnemyManager& enemyManager = EnemyManager::Instance();
	enemyManager.Clear();*/
	//EnemyManager::Instance().Clear();
	StageManager::Instance().Clear();
	BulletManager::Instance().Clear();
	if (cameracontroller != nullptr)
	{
		delete cameracontroller;
		cameracontroller = nullptr;
	}
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	if (SpDome != nullptr)
	{
		delete SpDome;
		SpDome = nullptr;
	}
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	GameBGM->Play(true, 0.5f);

	if (gamePad.GetButtonDown() & GamePad::BTN_Y)
		isMenuFlag = true;
	if (isMenuFlag == true)
	{
		axisY = gamePad.GetAxisLY();
		MenuMove_D = MenuMove_U = false;
		if (axisY == 0) Moveble = true;
		if (gamePad.GetButtonDown() & GamePad::BTN_UP||axisY > 0.8f)MenuMove_U = true;
		if (gamePad.GetButtonDown() & GamePad::BTN_DOWN||axisY < -0.8f)MenuMove_D = true;
		if (MenuMove_D && Moveble)
		{
			MenuMode++;
			Moveble = false;
		}
		if (MenuMove_U && Moveble)
		{
			MenuMode--;
			Moveble = false;
		}

		if (MenuMode > 2)MenuMode = 2;
		if (MenuMode < 0)MenuMode = 0;
		menuGameColor = { 1,1,1,1 };
		menuHelpColor = { 1,1,1,1 };
		menuTitleColor = { 1,1,1,1 };

		menuGamePos = { screenWidth / 2 - MenuWidth / 2,200 };
		menuHelpPos = { screenWidth / 2 - MenuWidth / 2,400 };
		menuTitlePos = { screenWidth / 2 - MenuWidth / 2,600 };

		menuGameSize = { MenuWidth,MenuHeight };
		menuHelpSize = { MenuWidth,MenuHeight };
		menuTitleSize = { MenuWidth,MenuHeight };
		// ���j�����[�h
		switch (MenuMode)
		{
		case menu::menuGame:
			//menuGameColor = { 1,0,0,1 };
			menuGamePos = { screenWidth / 2 - MenuWidth / 2 - 50,200 - 50 };
			menuGameSize = { MenuWidth + 100,MenuHeight + 50 };
			if (gamePad.GetButtonDown() & GamePad::BTN_A)
				isMenuFlag = false;
			break;
		case menu::menuHelp:
			//menuHelpColor = { 1,0,0,1 };
			menuHelpPos = { screenWidth / 2 - MenuWidth / 2 - 50,400 - 50 };
			menuHelpSize = { MenuWidth + 100,MenuHeight + 50 };
			if (gamePad.GetButtonDown() & GamePad::BTN_A)
			{
				HelpFlag = true;
			}
			break;
		case menu::menuTitle:
			//menuTitleColor = { 1,0,0,1 };
			menuTitlePos = { screenWidth / 2 - MenuWidth / 2 - 50,600 - 50 };
			menuTitleSize = { MenuWidth + 100,MenuHeight + 50 };
			if (gamePad.GetButtonDown() & GamePad::BTN_A)
			{
				isMenuFlag = false;
				SceneManager::Instance().ChangeScene(new SceneTitle);
			}
			break;
		}
		if (HelpFlag)
			Help();
	}

	else
	{
		// �J�������[�h�ŕ���
		switch (CameraController::Instance().GetCameraMode())
		{
		case Mode::viewMode:
			// �ʑI������
			ChooseSurface();

			// �J�����̐�p�A�b�v�f�[�g�Ăяo��
			cameracontroller->SetTarget({ 0,15,0 });
			cameracontroller->ViewUpdate(elapsedTime);

			// FPS���[�h�ֈڍs
			if (gamePad.GetButtonDown() & GamePad::BTN_A && delaytimer == 0 && delaytimer2 == 0)FpsCameraInitialize(cameracontroller->GetCameraMode());


			if (gamePad.GetButtonDown() & GamePad::BTN_X)SpectatorCameraInitialize(CameraController::Instance().GetCameraMode());
			break;

		case Mode::fpsMode:
			// �v���C���[�A�b�v�f�[�g�Ăяo��
			player->Update(elapsedTime);

			// �J������p�A�b�v�f�[�g�Ăяo��
			cameracontroller->SetEye(player->GetPosition());
			cameracontroller->FpsUpdate(elapsedTime);

			// �J�������x�֘A
			if (color_slow > 0)color_slow -= 0.01f;
			if (color_normal > 0)color_normal -= 0.01f;
			if (color_fast > 0)color_fast -= 0.01f;
			if (gamePad.GetButtonDown() & GamePad::BTN_B)ChangeSpeed();

			// View���[�h�ֈڍs
			if (PushPower > 0)
				PushPower -= 2.0f;
			if (PushPower == 0)
				BackFlag = false;
			if (gamePad.GetButton() & GamePad::BTN_B)
			{
				BackFlag = true;
				PushPower += 6.0f;
			}
			if (PushPower > 360)
			{
				BackFlag = false;
				ViewCameraInitialize();
			}

			// �X�y�N�e�C�^�[���[�h�ֈڍs
			if (gamePad.GetButtonDown() & GamePad::BTN_X)SpectatorCameraInitialize(CameraController::Instance().GetCameraMode());

			break;

		case Mode::spectatorMode:

		
			// �v���C���[�A�b�v�f�[�g�Ăяo��
			player->SpectatorUpdate(elapsedTime);

			// �J������p�A�b�v�f�[�g�Ăяo��
			cameracontroller->SetEye(player->GetPosition());
			cameracontroller->SpectatorUpdate(elapsedTime);

			if (PushPower > 0)
				PushPower -= 2.0f;
			if (PushPower == 0)
				BackFlag = false;
			if (gamePad.GetButton() & GamePad::BTN_B)
			{
				BackFlag = true;
				PushPower += 6.0f;
			}
			if (PushPower > 360)
			{
				BackFlag = false;
				switch (BeforeCM)	// �X�y�N�e�C�^�[���[�h�ɓ������ۂ̃��[�h�ŕ���
				{
				case Mode::viewMode:
					ViewCameraInitialize();
					break;
				case Mode::fpsMode:
					FpsCameraInitialize(CameraController::Instance().GetCameraMode());
					break;
				}
			}

			break;
		}

		StageManager::Instance().Update(elapsedTime);
		//stageMain->Update(elapsedTime);
		//player->Update(elapsedTime);
		//EnemyManager::Instance().Update(elapsedTime);
		//�G�t�F�N�g�X�V����
		EffectManager::Instance().Update(elapsedTime);

		shake.ShakeUpdate(elapsedTime);

		player->ct = cameracontroller->GetForward();

		SpDome->Update(elapsedTime);

	}
}

// �`�揈��
void SceneGame::Render()
{
	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0�`1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// �`�揈��

	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ���C�g�����i�������j

	//�J�����p�����[�^�[�ݒ�
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);
	

#if true

	// 3D���f���`��
	{
		Shader* shader = graphics.GetShader(0);
		shader->Begin(dc, rc);
		StageManager::Instance().Render(dc, shader,false);
		cube->Render(dc, shader, CameraController::Instance().GetCameraMode(), selectedsurface);
		BulletManager::Instance().Render(dc, shader);
		shader->End(dc);


		shader = graphics.GetShader(1);
		shader->Begin(dc, rc);
		SpDome->Render(dc, shader, false);

		
		shader->End(dc);
	}
	//3D�G�t�F�N�g�`��
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}
	// 3D�f�o�b�O�`��
	{
		//�v���~�e�B�u�f�o�b�N�`��
		player->DrawDebugPrimitive();
		//EnemyManager::Instance().DrawDebugPrimitive();
		// ���C�������_���`����s
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);
		// �f�o�b�O�����_���`����s
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
	}

#endif

	// 2D�X�v���C�g�`��
	{
		Shader* shader = graphics.GetShader(2);
		shader->Begin(dc, rc);

		float crossWidth = static_cast<float>(cross->GetTextureWidth());
		float crossHeight = static_cast<float>(cross->GetTextureHeight());
		// �Q�[�W�� MAX �����ƍ���
		const float gaugeWidth = static_cast<float>(gauge->GetTextureWidth());
		const float gaugeHeight = static_cast<float>(gauge->GetTextureHeight());
		// ���� HP/MAXHP �� 0.0(HP-MIN)�`1.0(HP-MAX)�̔䗦���o���B

		float RuleWidth = static_cast<float>(Rule->GetTextureWidth());
		float RuleHeight = static_cast<float>(Rule->GetTextureHeight());
		float SignalWidth = static_cast<float>(Signal->GetTextureWidth());
		float SignalHeight = static_cast<float>(Signal->GetTextureHeight());

		if (CameraController::Instance().GetCameraMode() == Mode::fpsMode)
		{
			cross->Render(dc,
				screenWidth / 2 - crossWidth / 4, screenHeight / 2 - crossHeight / 4,
				crossWidth / 2,
				crossHeight / 2,
				0, 0, crossWidth, crossHeight,
				0,
				1, 1, 1, 1);
			float speedWidth = 800;
			float speedHeight = 100;
			SpeedSprite_Slow->Render(dc,
				0, 0, speedWidth, speedHeight,
				0, 0, speedWidth, speedHeight,
				0,
				1, 1, 1, color_slow);
			SpeedSprite_Normal->Render(dc,
				0, 0, speedWidth, speedHeight,
				0, 0, speedWidth, speedHeight,
				0,
				1, 1, 1, color_normal);
			SpeedSprite_Fast->Render(dc,
				0, 0, speedWidth, speedHeight,
				0, 0, speedWidth, speedHeight,
				0,
				1, 1, 1, color_fast);
		}
		if (BackFlag)
		{
			gauge->Render(dc,
				screenWidth - gaugeWidth, screenHeight - gaugeHeight,
				gaugeWidth,
				gaugeHeight,
				0, 0, gaugeWidth, gaugeHeight,
				PushPower,
				1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (isMenuFlag)
		{
			Menu->Render(dc,
				0, 0,
				screenWidth,
				screenHeight,
				0, 0, screenWidth, screenHeight,
				0,
				0, 0, 0, 0.5f);

			MenuGame->Render(dc,
				menuGamePos.x, menuGamePos.y,
				menuGameSize.x,
				menuGameSize.y,
				0, 0, MenuWidth, MenuHeight,
				0,
				menuGameColor.x, menuGameColor.y, menuGameColor.z, menuGameColor.w);

			MenuHelp->Render(dc,
				menuHelpPos.x, menuHelpPos.y,
				menuHelpSize.x,
				menuHelpSize.y,
				0, 0, MenuWidth, MenuHeight,
				0,
				menuHelpColor.x, menuHelpColor.y, menuHelpColor.z, menuHelpColor.w);

			MenuTitle->Render(dc,
				menuTitlePos.x, menuTitlePos.y,
				menuTitleSize.x,
				menuTitleSize.y,
				0, 0, MenuWidth, MenuHeight,
				0,
				menuTitleColor.x, menuTitleColor.y, menuTitleColor.z, menuTitleColor.w);
		}
		if (HelpFlag)
		{
			Rule->Render(dc,
				0, 0, screenWidth * 3, screenHeight,
				Pos.x, 0, RuleWidth, RuleHeight,
				0,
				1, 1, 1, 1);

			if (SignalTimer % 60 >= 6)
			{
				if (SceneCount == 1)
				{
					Signal->Render(dc,
						screenWidth - SignalWidth / 2, screenHeight / 2 - SignalHeight / 4, SignalWidth / 2, SignalHeight / 2,
						0, 0, SignalWidth, SignalHeight,
						0,
						1, 1, 1, 1);
				}
				if (SceneCount == 2)
				{
					Signal->Render(dc,
						0, screenHeight / 2 - SignalHeight / 4, SignalWidth / 2, SignalHeight / 2,
						0, 0, SignalWidth, SignalHeight,
						180,
						1, 1, 1, 1);
					Signal->Render(dc,
						screenWidth - SignalWidth / 2, screenHeight / 2 - SignalHeight / 4, SignalWidth / 2, SignalHeight / 2,
						0, 0, SignalWidth, SignalHeight,
						0,
						1, 1, 1, 1);
				}
				if (SceneCount == 3)
				{
					Signal->Render(dc,
						0, screenHeight / 2 - SignalHeight / 4, SignalWidth / 2, SignalHeight / 2,
						0, 0, SignalWidth, SignalHeight,
						180,
						1, 1, 1, 1);
					B->Render(dc,
						screenWidth - SignalWidth / 2, screenHeight / 2 - SignalHeight / 4, SignalWidth / 2, SignalHeight / 2,
						0, 0, SignalWidth, SignalHeight,
						0,
						1, 1, 1, 1);
				}
			}
		}
		shader->End(dc);

	}
#ifdef _DEBUG
	// 2D�f�o�b�OGUI�`��
	{
		player->DrawDebugGUI();
		cube->DrawDebugGUI();
		mark->DrawDebugGUI();
		cameracontroller->cameraDebugGUI();

		// �e�̏��\��
		int count = BulletManager::Instance().GetBulletCount() - 1;
		if (count < 0)
			return;

		auto bullet = BulletManager::Instance().GetBullet(count);
		bullet->DrawDebugGUI();
	}
#endif // _DEBUG
	
}

// FPS�J�����C�j�V�����C�Y
void SceneGame::FpsCameraInitialize(int BeforeMode)
{
	PushPower = 0;

	switch (BeforeMode)
	{
	case Mode::viewMode:
		cameracontroller->SetAngle({ cameracontroller->GetAngle().x,cameracontroller->GetAngle().y + DirectX::XM_PI,cameracontroller->GetAngle().z });
		cameracontroller->SetTarget({ 0,15,0 });
		cameracontroller->SetCurrentAngle(cameracontroller->GetAngle());
		player->SetPosition(fixedpositions[selectedsurface]);
		//player->SetAngle()
		break;
	case Mode::spectatorMode:
		//cameracontroller->SetAngle(fixedangles[selectedsurface]);
		cameracontroller->SetAngle(KeepAngle);
		cameracontroller->SetTarget({ 0,15,0 });
		cameracontroller->SetCurrentAngle(cameracontroller->GetAngle());
		player->SetPosition(fixedpositions[selectedsurface]);
		break;
	}
	// ���[�h�؂�ւ�
	CameraController::Instance().SetCameraMode(Mode::fpsMode);

}

// View�J�����C�j�V�����C�Y
void SceneGame::ViewCameraInitialize()
{
	PushPower = 0;
	//cameracontroller->SetAngle({ 0,cameracontroller->GetAngle().y + DirectX::XM_PI,0 });

	switch (selectedsurface)
	{
	case 0:
		cameracontroller->SetAngle({ 0,0,0 });
		break;
	case 1:
		cameracontroller->SetAngle({ 0,-DirectX::XM_PI * 0.5f,0 });
		break;
	case 2:
		cameracontroller->SetAngle({ 0,-DirectX::XM_PI,0 });
		break;
	case 3:
		cameracontroller->SetAngle({ 0,-DirectX::XM_PI * 1.5,0 });
		break;
	}

	// ���[�h�؂�ւ�
	//cameramode = Mode::viewMode;
	CameraController::Instance().SetCameraMode(Mode::viewMode);
}

// �X�y�N�e�C�^�[�J�����C�j�V�����C�Y
void SceneGame::SpectatorCameraInitialize(int BeforeMode)
{
	BeforeCM = BeforeMode;
	PushPower = 0;
	KeepAngle = cameracontroller->GetAngle();

	switch (BeforeMode)
	{
	case Mode::viewMode:
		cameracontroller->SetAngle({ cameracontroller->GetAngle().x,cameracontroller->GetAngle().y + DirectX::XM_PI,cameracontroller->GetAngle().z });
		cameracontroller->SetTarget({ 0,15,0 });
		cameracontroller->SetCurrentAngle(cameracontroller->GetAngle());
		player->SetPosition(cameracontroller->GetEye());
		break;
	case Mode::fpsMode:
		break;
	}

	// ���[�h�؂�ւ�
	//cameramode = Mode::spectatorMode;
	CameraController::Instance().SetCameraMode(Mode::spectatorMode);
}

// �ʑI��
void SceneGame::ChooseSurface()
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	axisX = gamePad.GetAxisLX();
	if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT || axisX > 0.8f)
	{
		if (delaytimer == 0 && delaytimer2 == 0)
			delayflag = true;
	}
	if (delayflag == true)delaytimer++;
	if (delaytimer > 45)
	{
		selectedsurface++;
		delaytimer = 0;
		delayflag = false;
	}
	if (gamePad.GetButtonDown() & GamePad::BTN_LEFT || axisX < -0.8f)
	{
		if (delaytimer == 0 && delaytimer2 == 0)delayflag2 = true;
	}
	if (delayflag2 == true)delaytimer2++;
	if (delaytimer2 > 45)
	{
		selectedsurface--;
		delaytimer2 = 0;
		delayflag2 = false;
	}
	if (selectedsurface < 0)selectedsurface = 3;
	if (selectedsurface > 3)selectedsurface = 0;
}

// �J�����X�s�[�h�֘A
void SceneGame::ChangeSpeed()
{
	speedNo++;
	if (speedNo > 2)speedNo = 0;

	if (speedNo == 0)
	{
		color_slow = 1;
		color_normal = 0;
		color_fast = 0;
	}
	if (speedNo == 1)
	{
		color_slow = 0;
		color_normal = 1;
		color_fast = 0;
	}
	if (speedNo == 2)
	{
		color_slow = 0;
		color_normal = 0;
		color_fast = 1;
	}


	cameracontroller->SetRollSpeed(rollSpeeds[speedNo]);
}

// �w���v���
void SceneGame::Help()
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	axisX = gamePad.GetAxisLX();
	Graphics& graphics = Graphics::Instance();
	float screenWidth = static_cast<float>(graphics.GetScreenWidth());

	if (RuleMove_R == false && RuleMove_L == false)
	{
		if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT || axisX > 0.8f)
		{
			if (Pos.x < 1280 * 2)
			{
				RulePosX = Pos.x;
				RuleMove_R = true;
			}
		}

		if (gamePad.GetButtonDown() & GamePad::BTN_LEFT || axisX < -0.8f)
		{
			if (Pos.x > 0)
			{
				RulePosX = Pos.x;
				RuleMove_L = true;
			}
		}

		if (Pos.x == 1280 * 2 && gamePad.GetButtonDown() & GamePad::BTN_B)
		{
			HelpFlag = false;
		}
	}
	// ���[����ʈړ�����(�E���)
	if (RuleMove_R == true)
	{
		Pos.x += 20;
		if (Pos.x > RulePosX + 1280)
		{
			RuleMove_R = false;
			SceneCount++;
			Pos.x = RulePosX + 1280;
		}
	}
	// ���[����ʈړ�����(�����)
	if (RuleMove_L == true)
	{
		Pos.x -= 20;
		if (Pos.x < RulePosX - 1280)
		{
			RuleMove_L = false;
			SceneCount--;
			Pos.x = RulePosX - 1280;
		}
	}
	SignalTimer++;
}