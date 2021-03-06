
#include "Input/Input.h"
#include "SceneSelectStage.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneLoading.h"


void SceneSelectStage::Initialize()
{
    SelectStage = new Sprite("Data/Sprite/SceneSelect.png");

    cursor = new Cursor();

    SelectStageBGM = Audio::Instance().LoadAudioSource("Data/BGM/wav/HelpBGM.wav");
    SelectSE = Audio::Instance().LoadAudioSource("Data/Sound/Select.wav");
    flag = false;
}

void SceneSelectStage::Finalize()
{
    if (SelectStage != nullptr)
    {
        delete SelectStage;
        SelectStage = nullptr;
    }
    if (cursor != nullptr)
    {
        delete cursor;
        cursor = nullptr;
    }
}

void SceneSelectStage::Update(float elapsedTime)
{
    cursor->Update();
    SelectStageBGM->Play(true, 0.5f);

    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_A && !flag)
    {
        if (cursor->GetonCursorNo() <= 3) {
            SelectSE->Play(false, 5.0f);
            flag = true;
        }
    }
    if (gamePad.GetButtonDown() & GamePad::BTN_B)
    {
        SceneManager::Instance().ChangeScene(new SceneTitle);
    }

    if (flag)
    {
        ChangeTimer++;
    }

    if (ChangeTimer > 60.0f)
    {
        if (cursor->GetonCursorNo() < 5)
        {
            //ステージ選択で番号を持たせMarkの引数に渡して遷移する
            StageManager::Instance().SetStageNum(cursor->GetonCursorNo() + 1);
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
        }
        flag = false;
    }


}

void SceneSelectStage::Render()
{
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    //画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    Shader* shader = graphics.GetShader(2);

    //2Dスプライト描画
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());

        SelectStage->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, 
            static_cast<float>(SelectStage->GetTextureWidth()), static_cast<float>(SelectStage->GetTextureHeight()),
            0,
            1, 1, 1, 1);
    }
    cursor->Render(dc);
}
