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
    Stage1 = new Sprite("Data/Sprite/StageIcon1.png");
    Stage2 = new Sprite("Data/Sprite/StageIcon2.png");
    Stage3 = new Sprite("Data/Sprite/StageIcon3.png");
    Stage4 = new Sprite("Data/Sprite/StageIcon4.png");
    Stage5 = new Sprite("Data/Sprite/StageIcon5.png");
    cursorWidth = static_cast<float>(CursorSprite->GetTextureWidth());
    cursorHeight = static_cast<float>(CursorSprite->GetTextureHeight());
    ballWidth = static_cast<float>(BallSprite->GetTextureWidth());
    ballHeight = static_cast<float>(BallSprite->GetTextureHeight());
    StagesWidth= static_cast<float>(Stage1->GetTextureWidth());
    StagesHeight= static_cast<float>(Stage1->GetTextureHeight());
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
    //if (gamePad.GetButtonDown() & GamePad::BTN_X)Launch();

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
    for (int i = 0; i < 4; i++)
    {
        distance[i] = sqrtf(
            (position.x - StageNumPos[i].x) * (position.x - StageNumPos[i].x) +
            (position.y - StageNumPos[i].y) * (position.y - StageNumPos[i].y));
        if (distance[i] < 140 /*&& !flag*/)
        {
            onCursorNo = i;
            keep = i;
            //flag = true;
        }

        if (distance[0] > 140 && distance[1] > 140 && distance[2] > 140 && distance[3] > 140)
        {
            onCursorNo = 10;
        }

 
        /*if (onCursorNo > 4) {
            if (distance[i] > 140)
        }*/
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
    switch (onCursorNo)
    {
    case 0:
        Stage1->Render(dc,
            1100, 250, 1500, 650,
            0, 0, StagesWidth, StagesHeight,
            0,
            1, 1, 1, 1);
        break;
    case 1:
        Stage2->Render(dc,
            1100, 250, 1500, 650,
            0, 0, StagesWidth, StagesHeight,
            0,
            1, 1, 1, 1);
        break;
    case 2:
        Stage3->Render(dc,
            1100, 250, 1500, 650,
            0, 0, StagesWidth, StagesHeight,
            0,
            1, 1, 1, 1);
        break;
    case 3:
        Stage4->Render(dc,
            1100, 250, 1500, 650,
            0, 0, StagesWidth, StagesHeight,
            0,
            1, 1, 1, 1);
        break;
    case 4:
        Stage5->Render(dc,
            1100, 250, 1500, 650,
            0, 0, StagesWidth, StagesHeight,
            0,
            1, 1, 1, 1);
        break;
    case 5:
        break;
    }
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

            ImGui::InputInt("onCursorNo", &onCursorNo);
        }
    }
    ImGui::End();
}