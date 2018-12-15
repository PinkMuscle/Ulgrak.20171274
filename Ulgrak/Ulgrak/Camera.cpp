#include "Camera.h"

Camera* Camera::pInstance = nullptr;

constexpr int screenWidth = 864;
constexpr int screenHeight = 540;
constexpr float sideBlank = 200;
constexpr float upBlank = 125; //sidBlank * 5 / 8

void Camera::Update(const std::vector<std::unique_ptr<GameObject>>& players)
{
    float minX, maxX, minY, maxY;

    minX = maxX = players[0]->GetPosition().x;
    minY = maxY = players[0]->GetPosition().y;

    for (std::vector<std::unique_ptr<GameObject>>::size_type i = 1; i < players.size(); i++)
    {
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

    if (maxY > 400)
    {
        maxY = 400;
    }

    if ((maxX - minX) / (maxY - minY) > (screenWidth - sideBlank * 2) / (screenHeight - upBlank * 2))
    {
        leftX = minX - sideBlank;
        rightX = maxX + sideBlank;
        upY = (maxY + minY) / 2 - ((rightX - leftX) * 5 / 8 / 2);

        objScale = screenWidth / (rightX - leftX);
    }
    else
    {
        upY = minY - upBlank;
        downY = maxY + upBlank;
        leftX = (maxX + minX) / 2 - ((downY - upY) * 8 / 5 / 2);

        objScale = screenHeight / (downY - upY);
    }
}

int Camera::GetXOnCamera(const float& objX) const
{
    return int((objX - leftX) * objScale);
}
int Camera::GetYOnCamera(const float& objY) const
{
    return int((objY - upY) * objScale);
}