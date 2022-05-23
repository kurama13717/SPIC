#include <thread>//�}���`�X���b�h
#include "Graphics/Graphics.h"
#include "Input/Input.h"
#include "SceneLoading.h"
#include "SceneManager.h"

void SceneLoading::Initialize()
{
    sprite = new Sprite("Data/Sprite/yazirusigauge.png");
    //�X���b�h�J�n
    //�R���X�g���N�^�Ɋ֐��̃|�C���^��n��
    //�����̃N���X�̊֐����}���`�X���b�h�ɂ���ꍇ�Athis�|�C���^��n��
    //(�����o�֐��|�C���^�A�I�u�W�F�N�g�|�C���^�A����)
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
    
    //���������Ȃ�V�[���J��
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

    //��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);
    //2D�X�v���C�g�`��
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        float positionX = screenWidth - textureWidth;
        float positionY = screenHeight - textureHeight;

        //�^�C�g���`��
        sprite->Render(dc,
            positionX, positionY, textureWidth, textureHeight,
            0, 0, textureWidth, textureHeight,
            angle,
            1, 1, 1, 1);
    }
}

//���[�f�B���O�X���b�h
void SceneLoading::LoadingThred(SceneLoading* scene)
{
    // COM�֘A�̏������ŃX���b�h���ɌĂԕK�v������//�K�v���킩���
    CoInitialize(nullptr);
    // ���̃V�[���̏��������s��
    scene->nextScene->Initialize();
    // �X���b�h���I���O��COM�֘A�̏I����
    CoUninitialize();
    // ���̃V�[���̏��������ݒ�
    scene->nextScene->SetReady();
}
