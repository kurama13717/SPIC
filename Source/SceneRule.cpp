#include "Graphics/Graphics.h"
#include "Input/Input.h"
#include "SceneRule.h"
#include "SceneTitle.h"
#include "SceneManager.h"

void SceneRule::Initialize()
{
    Rule = new Sprite("Data/Sprite/Rule.png");
    Signal = new Sprite("Data/Sprite/Signal.png");
    B = new Sprite("Data/Sprite/Bbutton.png");
}
void SceneRule::Finalize()
{
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
}
void SceneRule::Update(float elapsedTime)
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
            SceneManager::Instance().ChangeScene(new SceneTitle);
            //SceneManager::Instance().ChangeScene(nextScene);
        }
    }
    // ルール画面移動処理(右回り)
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
    // ルール画面移動処理(左回り)
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
void SceneRule::Render()
{
    Graphics& graphics = Graphics::Instance();
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
        float RuleWidth = static_cast<float>(Rule->GetTextureWidth());
        float RuleHeight = static_cast<float>(Rule->GetTextureHeight());
        float SignalWidth = static_cast<float>(Signal->GetTextureWidth());
        float SignalHeight = static_cast<float>(Signal->GetTextureHeight());

        Rule->Render(dc,
            0, 0, screenWidth*3, screenHeight,
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
}
