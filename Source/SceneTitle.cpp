#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneSelectStage.h"
#include "Input/Input.h"

// 変更点
#include "SceneRule.h"

void SceneTitle::Initialize()
{
    sprite = new Sprite("Data/Sprite/Title.png");
    Title = new Sprite("Data/Sprite/ReflecT ne.png");
    arrow = new Sprite("Data/Sprite/arrow.png");
    TitleGame =new Sprite("Data/Sprite/TitleGame.png");
    TitleHelp =new Sprite("Data/Sprite/TitleHelp.png");
    TitleEnd = new Sprite("Data/Sprite/TitleEnd.png");
    cameracontroller = new CameraController();

    TitleBGM = Audio::Instance().LoadAudioSource("Data/BGM/wav/TitleBGM.wav");
    SelectSE = Audio::Instance().LoadAudioSource("Data/Sound/Select.wav");
    


    screenWidth = static_cast<float>(graphics.GetScreenWidth());
    screenHeight = static_cast<float>(graphics.GetScreenHeight());

    //カメラ初期設定
    camera.SetLookAt(DirectX::XMFLOAT3(0, 10, -10), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 1, 0));
    camera.SetPerspectiveFov(
        DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
        0.1f,
        1000.0f
    );
    cameracontroller->SetAngle(DirectX::XMFLOAT3(DirectX::XMConvertToRadians(15), 0.0f, 0.0f));
    cameracontroller->SetFov(35.0f);
    //フォント初期化
    {
        font = std::make_unique<Font>(device, "Data/Font/MS Gothic.fnt", 1024);
    }
    StageManager::Instance().SetStageClear(false);
  
    flag = false;

}
void SceneTitle::Finalize()
{
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
    if (Title != nullptr)
    {
        delete Title;
        Title = nullptr;
    }
    if (arrow != nullptr)
    {
        delete arrow;
        arrow = nullptr;
    }
    if (TitleGame != nullptr)
    {
        delete TitleGame;
        TitleGame = nullptr;
    }
    if (TitleHelp != nullptr)
    {
        delete TitleHelp;
        TitleHelp = nullptr;
    }
    if (TitleEnd != nullptr)
    {
        delete TitleEnd;
        TitleEnd = nullptr;
    }
    if (cameracontroller != nullptr)
    {
        delete cameracontroller;
        cameracontroller = nullptr;
    }
}
void SceneTitle::Update(float elapsedTime)
{
    TitleBGM->Play(true,0.5f);
    
    if (flag)
    {
        ChangeTimer++;
    }
    if (ChangeTimer > 60.0f) {
        if (/*Selectflag*/TitleMode == title::titleGame) 
        {
            SceneManager::Instance().ChangeScene(new SceneSelectStage);
        }
        if (TitleMode == title::titleHelp)
        {
            SceneManager::Instance().ChangeScene(new SceneRule);
        }
        ChangeTimer = 0.0f;
        flag = false;
    }


    cameracontroller->Update(elapsedTime);
    //UpdateTransform();
    TitleInput();
    // 変更点
    
    Timer++;
}
//void SceneTitle::UpdateTransform()
//{
//    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
//    DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
//    DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
//    DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
//    DirectX::XMMATRIX R = X * Y * Z;
//    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
//    DirectX::XMMATRIX W = S * R * T;
//    DirectX::XMStoreFloat4x4(&transform, W);
//
//}
void SceneTitle::TitleInput()
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    axisY = gamePad.GetAxisLY();
    TitleMove_D = TitleMove_U = false;
    if (axisY == 0) Moveble = true;
    if (axisY > 0.8f)TitleMove_U = true;
    if (axisY < -0.8f)TitleMove_D = true;
    if (TitleMove_D && Moveble)
    {
        TitleMode++;
        Moveble = false;
    }
    if (TitleMove_U && Moveble)
    {
        TitleMode--;
        Moveble = false;
    }
    
    if (TitleMode > 2)TitleMode = 2;
    if (TitleMode < 0)TitleMode = 0;
    
    titleGamePos = { screenWidth / 2 - TitleWidth / 2,350 };
    titleHelpPos = { screenWidth / 2 - TitleWidth / 2,500 };
    titleEndPos = { screenWidth / 2 - TitleWidth / 2,650 };
    
    titleGameSize = { TitleWidth,TitleHeight };
    titleHelpSize = { TitleWidth,TitleHeight };
    titleEndSize = { TitleWidth,TitleHeight };
    
    titleGameAlpha = 1;
    titleHelpAlpha = 1;
    titleEndAlpha = 1;
    if (Timer % 60 >= 6)
    {
        alpha = 1;
    }
    else
    {
        alpha = 0;
    }
    // メニュモード
    switch (TitleMode)
    {
    case title::titleGame:
        titleGamePos = { screenWidth / 2 - TitleWidth / 2 - 50,350 - 50 };
        titleGameSize = { TitleWidth + 100,TitleHeight + 50 };
        titleGameAlpha = alpha;
        if (gamePad.GetButtonDown() & GamePad::BTN_A && !flag)
        {
            SelectSE->Play(false,5.0f);
            flag = true;
            
        }
        break;
    case title::titleHelp:
        titleHelpPos = { screenWidth / 2 - TitleWidth / 2 - 50,500 - 50 };
        titleHelpSize = { TitleWidth + 100,TitleHeight + 50 };
        titleHelpAlpha = alpha;
        if (gamePad.GetButtonDown() & GamePad::BTN_A)
        {
            SelectSE->Play(false,5.0f);
            flag = true;
            //SceneManager::Instance().ChangeScene(new SceneRule);
        }
        break;
    case title::titleEnd:
        titleEndPos = { screenWidth / 2 - TitleWidth / 2 - 50,650 - 50 };
        titleEndSize = { TitleWidth + 100,TitleHeight + 50 };
        titleEndAlpha = alpha;
        if (gamePad.GetButtonDown() & GamePad::BTN_A)
        {
            SelectSE->Play(false,5.0f);
            PostQuitMessage(0);
        }
        break;
    }
}
void SceneTitle::DrawDebugGUI()
{

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("title", nullptr, ImGuiWindowFlags_None))
    {
    }
    ImGui::End();
}
void SceneTitle::Render()
{
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();
    Shader* shader = graphics.GetShader(0);

    //画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    camera.SetPerspectiveFov(
        DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
        0.1f,
        1000.0f
    );
    //カメラ設定
    {
        rc.view = camera.GetView();
        rc.projection = camera.GetProjection();
    }
   // rc.lightDirection = { light_angle.x, light_angle.y, light_angle.z, 0.0f };// ライト方向（下方向）
  //3Dモデル描画
    //{
    //    shader->Begin(dc, rc);
    //    shader->Draw(dc, title_model);
    //    //BottenManager::Instance().Render(deviceContext, shader);
    //    //bottenManager.Render(deviceContext,shader);
    //    shader->End(dc);
    //}
    
    //2Dスプライト描画
    {
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        float arrowWidth = static_cast<float>(arrow->GetTextureWidth());
        float arrowHeight = static_cast<float>(arrow->GetTextureHeight());

        //タイトル描画
        sprite->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0,
            1, 1, 1, 1);

        Title->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0,
            1, 1, 1, 1);


        TitleGame->Render(dc,
            titleGamePos.x, titleGamePos.y,
            titleGameSize.x,
            titleGameSize.y,
            0, 0, TitleWidth, TitleHeight,
            0,
            1, 1, 1, titleGameAlpha);

        TitleHelp->Render(dc,
            titleHelpPos.x, titleHelpPos.y,
            titleHelpSize.x,
            titleHelpSize.y,
            0, 0, TitleWidth, TitleHeight,
            0,
            1, 1, 1, titleHelpAlpha);

        TitleEnd->Render(dc,
            titleEndPos.x, titleEndPos.y,
            titleEndSize.x,
            titleEndSize.y,
            0, 0, TitleWidth, TitleHeight,
            0,
            1, 1, 1, titleEndAlpha);

        //if (Timer % 60 >= 6)
        //{
        //    arrow->Render(dc,
        //        arrowPosX, 480, 100, 100,
        //        0, 0, arrowWidth, arrowHeight,
        //        0,
        //        1, 1, 1, 1);
        //}

        //if (flagX == true)
        //{
        //    834, 75;
        //}
    }
    // フォントの描画
    {
        //float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        //float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        //font->Begin(dc);
        //font->Draw(screenWidth *0.25f, screenHeight * 0.25f  + 150, L"めんどくさい~\nX O X", 1.5f, 1.5f, 1.0f, 1.0f, 1.0f, 1.0f);
        //font->End(dc);
    }
#ifdef _DEBUG
    DrawDebugGUI();
#endif //_DEBUG
}