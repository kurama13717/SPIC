#include "Graphics/Graphics.h"
#include "Effect.h"
#include "EffectManager.h"

Effect::Effect(const char* filename)
{
    //�����ɃA�N�Z�X���Ȃ��悤�ɔr�����䂷��
    std::lock_guard<std::mutex>lock(Graphics::Instance().getMutex());
    //���\�[�X�ǂݍ���
    char16_t utf16Filename[256];
    Effekseer::ConvertUtf8ToUtf16(utf16Filename, 256, filename);//filename��UTF8->UTF16�ɕϊ�
    Effekseer::Manager* effekseerManager = EffectManager::Instance().GetEffekseerManager();
    effekseerEffect = Effekseer::Effect::Create(effekseerManager, (EFK_CHAR*)utf16Filename);
}
Effect::~Effect()
{
    //�j������
    if (effekseerEffect != nullptr)
    {
        effekseerEffect->Release();
        effekseerEffect = nullptr;
    }
}

//�Đ�
Effekseer::Handle Effect::Play(const DirectX::XMFLOAT3& positon, float scale)
{
    Effekseer::Manager* effekseerManager = EffectManager::Instance().GetEffekseerManager();
    Effekseer::Handle handle = effekseerManager->Play(effekseerEffect, positon.x, positon.y, positon.z);
    effekseerManager->SetScale(handle, scale, scale, scale);
    return handle;
}

//��~
void Effect::Stop(Effekseer::Handle handle)
{
    Effekseer::Manager* effekseerManager = EffectManager::Instance().GetEffekseerManager();
    effekseerManager->StopEffect(handle);
}
//���W�ݒ�
void Effect::SetPosition(Effekseer::Handle handle, const DirectX::XMFLOAT3& position)
{
    Effekseer::Manager* effekseerManager = EffectManager::Instance().GetEffekseerManager();
    effekseerManager->SetLocation(handle, position.x, position.y, position.z);
}

//�X�P�[���ݒ�
void Effect::SetScale(Effekseer::Handle handle, const DirectX::XMFLOAT3& scale)
{
    Effekseer::Manager* effekseerManager = EffectManager::Instance().GetEffekseerManager();
    effekseerManager->SetScale(handle, scale.x, scale.y, scale.z);
}