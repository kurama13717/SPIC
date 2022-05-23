#include <thread>//マルチスレッド
#include "Graphics/Graphics.h"
#include "Input/Input.h"
#include "SceneLoading.h"
#include "SceneManager.h"

void SceneLoading::Initialize()
{
    sprite = new Sprite("Data/Sprite/yazirusigauge.png");
    //スレッド開始
    //コンストラクタに関数のポインタを渡す
    //自分のクラスの関数をマルチスレッドにする場合、thisポインタを渡す
    //(メンバ関数ポインタ、オブジェクトポインタ、引数)
    std::thread thread(LoadingThred, this);
    thread.detach();
}
void SceneLoading::Finalize()
{
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
}
void SceneLoading::Update(float elapsedTime)
{
    constexpr float speed = 180;
    angle += speed * elapsedTime;
    
    //準備完了ならシーン遷移
    if (nextScene->IsReady())
    {
        SceneManager::Instance().ChangeScene(nextScene);
        nextScene = nullptr;
    }

}
void SceneLoading::Render()
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
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        float positionX = screenWidth - textureWidth;
        float positionY = screenHeight - textureHeight;

        //タイトル描画
        sprite->Render(dc,
            positionX, positionY, textureWidth, textureHeight,
            0, 0, textureWidth, textureHeight,
            angle,
            1, 1, 1, 1);
    }
}

//ローディングスレッド
void SceneLoading::LoadingThred(SceneLoading* scene)
{
    // COM関連の初期化でスレッド毎に呼ぶ必要がある//必要かわからん
    CoInitialize(nullptr);
    // 次のシーンの初期化を行う
    scene->nextScene->Initialize();
    // スレッドが終わる前にCOM関連の終了化
    CoUninitialize();
    // 次のシーンの準備完了設定
    scene->nextScene->SetReady();
}
