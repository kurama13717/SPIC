
#include "Input/Input.h"
#include "SceneSelectStage.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneLoading.h"

void SceneSelectStage::Initialize()
{
    SelectStage = new Sprite("Data/Sprite/SceneSelect.png");
    Number1 = new Sprite("Data/Sprite/Bbutton.png");
    Number2 = new Sprite("Data/Sprite/Bbutton.png");
    Number3 = new Sprite("Data/Sprite/Bbutton.png");
    Number4 = new Sprite("Data/Sprite/Bbutton.png");
    Number5 = new Sprite("Data/Sprite/Bbutton.png");
}

void SceneSelectStage::Finalize()
{
    if (SelectStage != nullptr)
    {
        delete SelectStage;
        SelectStage = nullptr;
    }
}

void SceneSelectStage::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_A)
    {
        //ステージ選択で番号を持たせMarkの引数に渡して遷移する
        StageManager::Instance().SetStageNum(2);
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
    }
    if (gamePad.GetButtonDown() & GamePad::BTN_B)
    {
        SceneManager::Instance().ChangeScene(new SceneTitle);
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
    //2Dスプライト描画
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float number1width = static_cast<float>(Number1->GetTextureWidth());
        float number1height = static_cast<float>(Number1->GetTextureHeight());

        SelectStage->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, 
            static_cast<float>(SelectStage->GetTextureWidth()), static_cast<float>(SelectStage->GetTextureHeight()),
            0,
            1, 1, 1, 1);
    }
}
