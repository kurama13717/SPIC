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

// 初期化
void SceneGame::Initialize()
{
	//宇宙空間
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
	//カメラ初期設定

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

	// スプライト
	gauge = new Sprite("Data/Sprite/yazirusigauge.png");
	cross = new Sprite("Data/Sprite/CrossHair.png");

	Filter = new Sprite();
	MenuGame = new Sprite("Data/Sprite/MenuGame.png");
	MenuHelp = new Sprite("Data/Sprite/MenuHelp.png");
	MenuTitle = new Sprite("Data/Sprite/MenuTitle.png");

	SpeedSprite_Slow = new Sprite("Data/Sprite/CameraSlow.png");
	SpeedSprite_Normal = new Sprite("Data/Sprite/CameraNormal.png");
	SpeedSprite_Fast = new Sprite("Data/Sprite/CameraFast.png");

	Rule = new Sprite("Data/Sprite/Rule.png");
	Signal = new Sprite("Data/Sprite/Signal.png");
	B = new Sprite("Data/Sprite/Bbutton.png");

	clearSprite = new Sprite("Data/Sprite/Clear.png");
	nextSprite = new Sprite("Data/Sprite/ClearNext.png");
	toTitleSptite = new Sprite("Data/Sprite/ClearTitle.png");

	cameraModeSprite_Surface = new Sprite("Data/Sprite/ModeSelect.png");
	cameraModeSprite_Fire = new Sprite("Data/Sprite/ModeFire.png");
	cameraModeSprite_Fly = new Sprite("Data/Sprite/ModeFly.png");

	ID3D11Device* device = graphics.GetDevice();
}

// 終了化
void SceneGame::Finalize()
{
	// スプライト終了化
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
	if (Filter != nullptr)
	{
		delete Filter;
		Filter = nullptr;
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
	if (clearSprite != nullptr)
	{
		delete clearSprite;
		clearSprite = nullptr;
	}
	if (nextSprite != nullptr)
	{
		delete nextSprite;
		nextSprite = nullptr;
	}
	if (toTitleSptite != nullptr)
	{
		delete toTitleSptite;
		toTitleSptite = nullptr;
	}
	if (cameraModeSprite_Surface != nullptr)
	{
		delete cameraModeSprite_Surface;
		cameraModeSprite_Surface = nullptr;
	}	
	if (cameraModeSprite_Fire != nullptr)
	{
		delete cameraModeSprite_Fire;
		cameraModeSprite_Fire = nullptr;
	}	
	if (cameraModeSprite_Fly != nullptr)
	{
		delete cameraModeSprite_Fly;
		cameraModeSprite_Fly = nullptr;
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

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	GameBGM->Play(true, 0.5f);
	isClear = StageManager::Instance().GetStageClear();
	if (isClear == true)clearTimer++;
	if (clearTimer > 60)
	{
		isClear2 = true;
		isClear = false;
		clearTimer = 0;
	}
	if (isClear2 == true)
	{
		axisY = gamePad.GetAxisLY();
		input_Up = input_Down = false;
		if (axisY == 0) inputtable = true;
		if (axisY > 0.8f)input_Up = true;
		if (axisY < -0.8f)input_Down = true;
		if (input_Down && inputtable)
		{
			select_Clear++;
			inputtable = false;
		}
		if (input_Up && inputtable)
		{
			select_Clear--;
			inputtable = false;
		}
		if (select_Clear > 1)select_Clear = 1;
		if (select_Clear < 0)select_Clear = 0;

		clearNextPos = { screenWidth / 2 - clearWidth / 2,400 };
		clearNextSize = { clearWidth,clearHeight };
		clearToTitlePos = { screenWidth / 2 - clearWidth / 2,600 };
		clearToTitleSize = { clearWidth,clearHeight };

		if (StageManager::Instance().GetStageNum() == 4)
		{
			select_Clear = 1;
		}
		switch (select_Clear)
		{
		case 0:
			clearNextPos = { screenWidth / 2 - clearWidth / 2 - 50,400 - 50 };
			clearNextSize = { clearWidth + 100,clearHeight + 50 };
			if (gamePad.GetButtonDown() & GamePad::BTN_A)
			{
				StageManager::Instance().SetStageNum(1 + StageManager::Instance().GetStageNum());
				SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame()));
			}
			break;
		case 1:
			clearToTitlePos = { screenWidth / 2 - clearWidth / 2 - 50,600 - 50 };
			clearToTitleSize = { clearWidth + 100,clearHeight + 50 };
			if (gamePad.GetButtonDown() & GamePad::BTN_A)
			{
				SceneManager::Instance().ChangeScene(new SceneTitle);
			}
			break;
		}
	}
	if (gamePad.GetButtonDown() & GamePad::BTN_Y)
		isMenuFlag = true;
	if (isMenuFlag == true)
	{
		axisY = gamePad.GetAxisLY();
		input_Up = input_Down = false;
		if (axisY == 0) inputtable = true;
		if (axisY > 0.8f)input_Up = true;
		if (axisY < -0.8f)input_Down = true;
		if (input_Down && inputtable)
		{
			MenuMode++;
			inputtable = false;
		}
		if (input_Up && inputtable)
		{
			MenuMode--;
			inputtable = false;
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
		// メニュモード
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

	if(isMenuFlag == false && isClear2 == false)
	{
		if (color_Surface > 0)color_Surface -= 0.01f;
		if (color_Fire > 0)color_Fire -= 0.01f;
		if (color_Fly > 0)color_Fly -= 0.01f;
		// カメラモードで分岐
		switch (CameraController::Instance().GetCameraMode())
		{
		case Mode::viewMode:
			// 面選択処理
			ChooseSurface();

			// カメラの専用アップデート呼び出し
			cameracontroller->SetTarget({ 0,15,0 });
			cameracontroller->ViewUpdate(elapsedTime);

			// FPSモードへ移行
			if (gamePad.GetButtonDown() & GamePad::BTN_A && moveTimer_Surface == 0)FpsCameraInitialize(cameracontroller->GetCameraMode());


			if (gamePad.GetButtonDown() & GamePad::BTN_X)SpectatorCameraInitialize(CameraController::Instance().GetCameraMode());
			break;

		case Mode::fpsMode:
			// プレイヤーアップデート呼び出し
			player->Update(elapsedTime);

			// カメラ専用アップデート呼び出し
			cameracontroller->SetEye(player->GetPosition());
			cameracontroller->FpsUpdate(elapsedTime);

			// カメラ速度関連
			if (color_slow > 0)color_slow -= 0.01f;
			if (color_normal > 0)color_normal -= 0.01f;
			if (color_fast > 0)color_fast -= 0.01f;
			if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT_SHOULDER)ChangeSpeed();

			// Viewモードへ移行
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

			// スペクテイターモードへ移行
			if (gamePad.GetButtonDown() & GamePad::BTN_X)SpectatorCameraInitialize(CameraController::Instance().GetCameraMode());

			break;

		case Mode::spectatorMode:

		
			// プレイヤーアップデート呼び出し
			player->SpectatorUpdate(elapsedTime);

			// カメラ専用アップデート呼び出し
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
				switch (BeforeCM)	// スペクテイターモードに入った際のモードで分岐
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
		//エフェクト更新処理
		EffectManager::Instance().Update(elapsedTime);

		shake.ShakeUpdate(elapsedTime);

		player->ct = cameracontroller->GetForward();

		SpDome->Update(elapsedTime);

	}
}

// 描画処理
void SceneGame::Render()
{
	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0〜1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// 描画処理

	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ライト方向（下方向）

	//カメラパラメーター設定
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);
	

#if true

	// 3Dモデル描画
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
	//3Dエフェクト描画
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}
	// 3Dデバッグ描画
	{
		//プリミティブデバック描画
		player->DrawDebugPrimitive();
		//EnemyManager::Instance().DrawDebugPrimitive();
		// ラインレンダラ描画実行
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);
		// デバッグレンダラ描画実行
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
	}

#endif

	// 2Dスプライト描画
	{
		Shader* shader = graphics.GetShader(2);
		shader->Begin(dc, rc);

		float crossWidth = static_cast<float>(cross->GetTextureWidth());
		float crossHeight = static_cast<float>(cross->GetTextureHeight());
		// ゲージの MAX 長さと高さ
		const float gaugeWidth = static_cast<float>(gauge->GetTextureWidth());
		const float gaugeHeight = static_cast<float>(gauge->GetTextureHeight());
		// 現在 HP/MAXHP で 0.0(HP-MIN)〜1.0(HP-MAX)の比率を出す。

		float RuleWidth = static_cast<float>(Rule->GetTextureWidth());
		float RuleHeight = static_cast<float>(Rule->GetTextureHeight());
		float SignalWidth = static_cast<float>(Signal->GetTextureWidth());
		float SignalHeight = static_cast<float>(Signal->GetTextureHeight());

		float camraModeSprite_Width = 400;
		float camraModeSprite_Height = 100;
		cameraModeSprite_Surface->Render(dc,
			0, 0, camraModeSprite_Width, camraModeSprite_Height,
			0, 0, camraModeSprite_Width, camraModeSprite_Height,
			0,
			1, 1, 1, color_Surface);
		cameraModeSprite_Fire->Render(dc,
			0, 0, camraModeSprite_Width, camraModeSprite_Height,
			0, 0, camraModeSprite_Width, camraModeSprite_Height,
			0,
			1, 1, 1, color_Fire);
		cameraModeSprite_Fly->Render(dc,
			0, 0, camraModeSprite_Width, camraModeSprite_Height,
			0, 0, camraModeSprite_Width, camraModeSprite_Height,
			0,
			1, 1, 1, color_Fly);

		if (isClear2 == true)
		{
			Filter->Render(dc,
				0, 0,
				screenWidth,
				screenHeight,
				0, 0, screenWidth, screenHeight,
				0,
				1, 1, 1, 0.5f);
			clearSprite->Render(dc,
				0, 0, screenWidth, screenHeight,
				0, 0, 1280, 720,
				0,
				1, 1, 1, 1);
			if (StageManager::Instance().GetStageNum() != 4)
			{
				nextSprite->Render(dc,
					clearNextPos.x, clearNextPos.y,
					clearNextSize.x,
					clearNextSize.y,
					0, 0, clearWidth, clearHeight,
					0,
					1, 1, 1, 1);
				toTitleSptite->Render(dc,
					clearToTitlePos.x, clearToTitlePos.y,
					clearToTitleSize.x,
					clearToTitleSize.y,
					0, 0, clearWidth, clearHeight,
					0,
					1, 1, 1, 1);
			}
			else
			{
				toTitleSptite->Render(dc,
					clearToTitlePos.x, clearToTitlePos.y,
					clearToTitleSize.x,
					clearToTitleSize.y,
					0, 0, clearWidth, clearHeight,
					0,
					1, 1, 1, 1);
			}
		}

		if (CameraController::Instance().GetCameraMode() == Mode::fpsMode && !isClear2)
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
			Filter->Render(dc,
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
	// 2DデバッグGUI描画
	{
		player->DrawDebugGUI();
		cube->DrawDebugGUI();
		mark->DrawDebugGUI();
		cameracontroller->cameraDebugGUI();

		// 弾の情報表示
		int count = BulletManager::Instance().GetBulletCount() - 1;
		if (count < 0)
			return;

		auto bullet = BulletManager::Instance().GetBullet(count);
		bullet->DrawDebugGUI();
	}
#endif // _DEBUG
	
}

// FPSカメライニシャライズ
void SceneGame::FpsCameraInitialize(int BeforeMode)
{
	color_Fire = 1;
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
	// モード切り替え
	CameraController::Instance().SetCameraMode(Mode::fpsMode);

}

// Viewカメライニシャライズ
void SceneGame::ViewCameraInitialize()
{
	color_Surface = 1;
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

	// モード切り替え
	//cameramode = Mode::viewMode;
	CameraController::Instance().SetCameraMode(Mode::viewMode);
}

// スペクテイターカメライニシャライズ
void SceneGame::SpectatorCameraInitialize(int BeforeMode)
{
	color_Fly = 1;
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

	// モード切り替え
	//cameramode = Mode::spectatorMode;
	CameraController::Instance().SetCameraMode(Mode::spectatorMode);
}

// 面選択
void SceneGame::ChooseSurface()
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float axisX = gamePad.GetAxisLX();
	input_Right = input_Left = false;
	if (axisX == 0 && !moving_Right && !moving_Left) inputtable = true;
	if (axisX > 0.8f)input_Right = true;
	if (axisX < -0.8f)input_Left = true;

	if (input_Right && inputtable)
	{
		moving_Right = true;
		inputtable = false;
	}
	if (input_Left && inputtable)
	{
		moving_Left = true;
		inputtable = false;
	}
	if (moving_Right)
	{
		moveTimer_Surface++;
		if (moveTimer_Surface > 45)
		{
			selectedsurface++;
			moveTimer_Surface = 0;
			moving_Right = false;
		}
	}
	if (moving_Left)
	{
		moveTimer_Surface++;
		if (moveTimer_Surface > 45)
		{
			selectedsurface--;
			moveTimer_Surface = 0;
			moving_Left = false;
		}
	}
	if (selectedsurface < 0)selectedsurface = 3;
	if (selectedsurface > 3)selectedsurface = 0;
}

// カメラスピード関連
void SceneGame::ChangeSpeed()
{
	speedNo++;
	if (speedNo > 2)speedNo = 0;

	if (speedNo == 0)
	{
		color_fast = 1;
		color_slow = 0;
		color_normal = 0;
	}
	if (speedNo == 1)
	{
		color_fast = 0;
		color_normal = 1;
		color_slow = 0;
	}
	if (speedNo == 2)
	{
		color_fast = 0;
		color_normal = 0;
		color_slow = 1;
	}


	cameracontroller->SetRollSpeed(rollSpeeds[speedNo]);
}

// ヘルプ画面
void SceneGame::Help()
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	axisX = gamePad.GetAxisLX();
	Graphics& graphics = Graphics::Instance();
	float screenWidth = static_cast<float>(graphics.GetScreenWidth());

	if (moving_Right == false && moving_Left == false)
	{
		if (axisX > 0.8f)
		{
			if (Pos.x < 1280 * 2)
			{
				RulePosX = Pos.x;
				moving_Right = true;
			}
		}

		if (axisX < -0.8f)
		{
			if (Pos.x > 0)
			{
				RulePosX = Pos.x;
				moving_Left = true;
			}
		}

		if (Pos.x == 1280 * 2 && gamePad.GetButtonDown() & GamePad::BTN_B)
		{
			HelpFlag = false;
		}
	}
	// ルール画面移動処理(右回り)
	if (moving_Right == true)
	{
		Pos.x += 20;
		if (Pos.x > RulePosX + 1280)
		{
			moving_Right = false;
			SceneCount++;
			Pos.x = RulePosX + 1280;
		}
	}
	// ルール画面移動処理(左回り)
	if (moving_Left == true)
	{
		Pos.x -= 20;
		if (Pos.x < RulePosX - 1280)
		{
			moving_Left = false;
			SceneCount--;
			Pos.x = RulePosX - 1280;
		}
	}
	SignalTimer++;
}