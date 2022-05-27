#include "Cursor.h"
#include "Input/Input.h"
#include "Graphics/Shader.h"
#include "CameraController.h"
#include <iostream>
#include <cmath>

Cursor::Cursor()
{
    CursorSprite = new Sprite("Data/Sprite/CrossHair.png");
    BallSprite = new Sprite("Data/Sprite/SelectBullet.png");
    cursorWidth = static_cast<float>(CursorSprite->GetTextureWidth());
    cursorHeight = static_cast<float>(CursorSprite->GetTextureHeight());
    ballWidth = static_cast<float>(BallSprite->GetTextureWidth());
    ballHeight = static_cast<float>(BallSprite->GetTextureHeight());
    screenWidth = static_cast<float>(graphics.GetScreenWidth());
    screenHeight = static_cast<float>(graphics.GetScreenHeight());
}
Cursor::~Cursor()
{
    if (CursorSprite != nullptr)
    {
        delete CursorSprite;
        CursorSprite = nullptr;
    }
    if (BallSprite != nullptr)
    {
        delete BallSprite;
        BallSprite = nullptr;
    }
}
void Cursor::Update()
{
    // 画面端（カーソル）
    if (position.x + 50 > screenWidth)position.x = screenWidth - 50;
    if (position.x - 50 < 0)position.x = 50;
    if (position.y + 50 > screenHeight)position.y = screenHeight - 50;
    if (position.y - 50 < 0)position.y = 50;

    GamePad& gamePad = Input::Instance().GetGamePad();
    axisX = gamePad.GetAxisLX();
    axisY = gamePad.GetAxisLY();

    // 入力（カーソル）
    position.x += axisX * speed;
    position.y -= axisY * speed;
    if (gamePad.GetButtonDown() & GamePad::BTN_X)Launch();

    // 移動（ボール）
    if (moveble == true)
    {
        ballPosition.x = lerp(ballCurrentPosition.x, position.x, i);
        ballPosition.y = lerp(ballCurrentPosition.y, position.y, i);

        ballSize.x = lerp(ballWidth * 3, 100, i);
        ballSize.y = lerp(ballHeight * 3, 100, i);
        i += 0.02f;
        if (i > 1.0)
        {
            moveble = false;
        }
    }
}
void Cursor::Render(ID3D11DeviceContext* dc)
{
    CursorSprite->Render(dc,
        position.x-50,position.y-50,100,100,
        0,0,cursorWidth,cursorHeight,
        0,
        1,1,1,1);
    BallSprite->Render(dc,
        ballPosition.x-ballSize.x/2, ballPosition.y-ballSize.y/2, ballSize.x, ballSize.y,
        0, 0, ballWidth, ballHeight,
        0,
        1, 1, 1, 1);
    DrawDebugGUI();
}
void Cursor::Launch()
{
    //ballPosition = { screenWidth / 2,screenHeight / 2 };
    //ballSize = { ballWidth*3,ballHeight*3 };
    ballCurrentPosition = { screenWidth / 2,screenHeight / 2 };
    moveble = true;
}

void Cursor::DrawDebugGUI()
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Cursor", nullptr, ImGuiWindowFlags_None))
    {
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
            //position
            ImGui::InputFloat2("Position", &position.x);
            ImGui::InputFloat2("ballPosition", &ballPosition.x);            
            ImGui::InputFloat2("ballSize", &ballSize.x);

            ImGui::InputFloat("i", &i);
        }
    }
    ImGui::End();
}