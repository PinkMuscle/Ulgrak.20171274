#include "Camera.h"

Camera* Camera::pInstance = nullptr;

constexpr int screenWidth = 864;
constexpr int screenHeight = 540;
constexpr float sideBlank = 200;
constexpr float upBlank = 125; //sidBlank * 5 / 8
constexpr float followSpeed = 0.02f;

void Camera::Update(const std::vector<std::unique_ptr<Player>>& players)
{
    float minX, maxX, minY, maxY;
    int playerCount = 0;

    minX = maxX = 240;
    minY = maxY = -32;

    for (std::vector<std::unique_ptr<Player>>::size_type i = 0; i < players.size(); i++)
    {
        if (players[i]->GetLife() == 0)
        {
            continue;
        }
        playerCount++;

        Vector2D tempPos = players[i]->GetPosition();

        if (tempPos.x < minX)
        {
            minX = tempPos.x;
        }

        if (tempPos.x > maxX)
        {
            maxX = tempPos.x;
        }

        if (tempPos.y < minY)
        {
            minY = tempPos.y;
        }

        if (tempPos.y > maxY)
        {
            maxY = tempPos.y;
        }
    }

    if (playerCount == 1)
    {
        for (auto& p : players)
        {
            if (p->GetLife() != 0)
            {
                minX = maxX = p->GetPosition().x;
                minY = maxY = p->GetPosition().y;
            }
        }
    }

    if (maxY > 400)
    {
        maxY = 400;
    }

    if ((maxX - minX) / (maxY - minY) > (screenWidth - sideBlank * 2) / (screenHeight - upBlank * 2))
    {
        leftX = minX - sideBlank;
        rightX = maxX + sideBlank;
        upY = (maxY + minY) / 2 - ((rightX - leftX) * 5 / 8 / 2);
        downY = (maxY + minY) / 2 + ((rightX - leftX) * 5 / 8 / 2);

        //objScale = screenWidth / (rightX - leftX);
    }
    else
    {
        upY = minY - upBlank;
        downY = maxY + upBlank;
        leftX = (maxX + minX) / 2 - ((downY - upY) * 8 / 5 / 2);
        rightX = (maxX + minX) / 2 + ((downY - upY) * 8 / 5 / 2);

        //objScale = screenHeight / (downY - upY);
    }

    oldLeftX += (leftX - oldLeftX) * followSpeed;
    oldRightX += (rightX - oldRightX) * followSpeed;
    oldUpY += (upY - oldUpY) * followSpeed;

    objScale = screenWidth / (oldRightX - oldLeftX);
}

void Camera::Init()
{
    oldLeftX = -600;
    oldRightX = 1100;
    oldUpY = -500;
}

int Camera::GetXOnCamera(const float& objX) const
{
    return int((objX - oldLeftX) * objScale);
}
int Camera::GetYOnCamera(const float& objY) const
{
    return int((objY - oldUpY) * objScale);
}