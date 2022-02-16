#include "Graphics/Graphics.h"
#include "EffectManager.h"

void EffectManager::Initialize()
{
    Graphics& graphics = Graphics::Instance();
    //EffekseerRenderer生成
    effekseerRenderer = EffekseerRendererDX11::Renderer::Create(graphics.GetDevice(), graphics.GetDeviceContext(), 2048);
    //EffekseerManager生成
    effekseerManager = Effekseer::Manager::Create(2048);
    //EffekseerRenderer各種設定
    effekseerManager->SetSpriteRenderer(effekseerRenderer->CreateSpriteRenderer());
    effekseerManager->SetRibbonRenderer(effekseerRenderer->CreateRibbonRenderer());
    effekseerManager->SetRingRenderer(effekseerRenderer->CreateRingRenderer());
    effekseerManager->SetTrackRenderer(effekseerRenderer->CreateTrackRenderer());
    effekseerManager->SetModelRenderer(effekseerRenderer->CreateModelRenderer());
    //Effekseer内でのローダーの設定
    effekseerManager->SetTextureLoader(effekseerRenderer->CreateTextureLoader());
    effekseerManager->SetModelLoader(effekseerRenderer->CreateModelLoader());
    effekseerManager->SetMaterialLoader(effekseerRenderer->CreateMaterialLoader());
    //Effekseerを左手座標で計算する
    effekseerManager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);//RHで右手座標
}
void EffectManager::Finalize()
{
    if (effekseerManager != nullptr)
    {
        effekseerManager->Destroy();
        effekseerManager = nullptr;
    }
    if (effekseerRenderer != nullptr)
    {
        effekseerRenderer->Destroy();
        effekseerRenderer = nullptr;
    }
}
void EffectManager::Update(float elapsedTime)
{
    effekseerManager->Update(elapsedTime * 60.0f);
}
void EffectManager::Render(const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection)
{
    //ビュー＆プロジェクション行列をEffekseerRendererに設定
    effekseerRenderer->SetCameraMatrix(*reinterpret_cast<const Effekseer::Matrix44*>(&view));
    effekseerRenderer->SetProjectionMatrix(*reinterpret_cast<const Effekseer::Matrix44*>(&projection));
    //Effekseer描画開始
    effekseerRenderer->BeginRendering();
    //Effekseer描画実行
    effekseerManager->Draw();
    //Effekseer描画終了
    effekseerRenderer->EndRendering();
}