#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed) : SDLGameObject(pParams), animSpeed(animSpeed)
{
}

void AnimatedGraphic::Update()
{
    currentFrame = int((SDL_GetTicks() / (1000 / animSpeed)) % numFrames);
}