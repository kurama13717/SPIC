#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "Input/Input.h"

// �ύX�_
#include "SceneRule.h"

void SceneTitle::Initialize()
{
    sprite = new Sprite("Data/Sprite/Title().png");
    X = new Sprite("Data/Sprite/X.png");
    arrow = new Sprite("Data/Sprite/arrow.png");
    cameracontroller = new CameraController();
    //�J���������ݒ�
    camera.SetLookAt(DirectX::XMFLOAT3(0, 10, -10), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 1, 0));
    camera.SetPerspectiveFov(
        DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
        0.1f,
        1000.0f
    );
    cameracontroller->SetAngle(DirectX::XMFLOAT3(DirectX::XMConvertToRadians(15), 0.0f, 0.0f));
    cameracontroller->SetFov(35.0f);
    //�t�H���g������
    {
        font = std::make_unique<Font>(device, "Data/Font/MS Gothic.fnt", 1024);
    }
    StageManager::Instance().SetStageClear(false);

}
void SceneTitle::Finalize()
{
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
    if (arrow != nullptr)
    {
        delete arrow;
        arrow = nullptr;
    }
    if (cameracontroller != nullptr)
    {
        delete cameracontroller;
        cameracontroller = nullptr;
    }
}
void SceneTitle::Update(float elapsedTime)
{
    cameracontroller->Update(elapsedTime);
    UpdateTransform();
    TitleInput();
    // �ύX�_
    ArrowTimer++;
}
void SceneTitle::UpdateTransform()
{
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
    DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
    DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
    DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
    DirectX::XMMATRIX R = X * Y * Z;
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
    DirectX::XMMATRIX W = S * R * T;
    DirectX::XMStoreFloat4x4(&transform, W);

}
void SceneTitle::TitleInput()
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    const GamePadButton anyButton =
        GamePad::BTN_A | GamePad::BTN_B | GamePad::BTN_X | GamePad::BTN_Y;
    if (gamePad.GetButtonDown() & anyButton)
    {
        if (arrowPosX == 500)
        {
            //�X�e�[�W�I���Ŕԍ���������Mark�̈����ɓn���đJ�ڂ���
            StageManager::Instance().SetStageNum(2);
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
        }
        if (arrowPosX == 1250)
            // �ύX�_
            SceneManager::Instance().ChangeScene(new SceneRule);
    }
    if (gamePad.GetButtonDown() & GamePad::BTN_LEFT)
    {
        arrowPosX = 500;
    }
    if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT)
    {
        arrowPosX = 1250;
    }
}
void SceneTitle::DrawDebugGUI()
{

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("title", nullptr, ImGuiWindowFlags_None))
    {
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
        }
    }
    ImGui::End();
}
void SceneTitle::Render()
{
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();
    Shader* shader = graphics.GetShader(0);

    //��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    camera.SetPerspectiveFov(
        DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
        0.1f,
        1000.0f
    );
    //�J�����ݒ�
    {
        rc.view = camera.GetView();
        rc.projection = camera.GetProjection();
    }
   // rc.lightDirection = { light_angle.x, light_angle.y, light_angle.z, 0.0f };// ���C�g�����i�������j
  //3D���f���`��
    //{
    //    shader->Begin(dc, rc);
    //    shader->Draw(dc, title_model);
    //    //BottenManager::Instance().Render(deviceContext, shader);
    //    //bottenManager.Render(deviceContext,shader);
    //    shader->End(dc);
    //}
    
    //2D�X�v���C�g�`��
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        float XWidth = static_cast<float>(X->GetTextureWidth());
        float XHeight = static_cast<float>(X->GetTextureHeight());
        float arrowWidth = static_cast<float>(arrow->GetTextureWidth());
        float arrowHeight = static_cast<float>(arrow->GetTextureHeight());
 
        //�^�C�g���`��
        sprite->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0,
            1, 1, 1, 1);

        if (ArrowTimer % 60 >= 6)
        {
            arrow->Render(dc,
                arrowPosX, 480, 100, 100,
                0, 0, arrowWidth, arrowHeight,
                0,
                1, 1, 1, 1);
        }

        if (flagX == true)
        {
            X->Render(dc,
                1050, 430, 200, 200,
                0, 0, XWidth, XHeight,
                0,
                1, 1, 1, 1);
        }
    }
    // �t�H���g�̕`��
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        //font->Begin(dc);
        //font->Draw(screenWidth *0.25f, screenHeight * 0.25f  + 150, L"�߂�ǂ�����~\nX O X", 1.5f, 1.5f, 1.0f, 1.0f, 1.0f, 1.0f);
        //font->End(dc);
    }
#ifdef _DEBUG
    DrawDebugGUI();
#endif //_DEBUG
}