#include "Camera.h"

Camera* Camera::pInstance = nullptr;

void Camera::Follow(float dstX, float speed)
{
    x += (dstX - x) * speed;
}