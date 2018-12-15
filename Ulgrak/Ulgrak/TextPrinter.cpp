#include "TextPrinter.h"
#include "Game.h"
#include <SDL_image.h>

TextPrinter* TextPrinter::pInstance = nullptr;

constexpr int numWidth = 6;
constexpr int numHeight = 8;

bool TextPrinter::Init()
{
    SDL_Surface* pTempSurface = IMG_Load("../assets/numbers.png");
    if (pTempSurface == 0)
    {
        return false;
    }
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), pTempSurface);
    SDL_FreeSurface(pTempSurface);

    if (pTexture != 0)
    {
        numTexture = pTexture;
        return true;
    }

    return false;
}

void TextPrinter::Draw(char ch, int x, int y, int scale)
{
    int column;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    switch (ch)
    {
    case '0':
        column = 0;
        break;
    case '1':
        column = 1;
        break;
    case '2':
        column = 2;
        break;
    case '3':
        column = 3;
        break;
    case '4':
        column = 4;
        break;
    case '5':
        column = 5;
        break;
    case '6':
        column = 6;
        break;
    case '7':
        column = 7;
        break;
    case '8':
        column = 8;
        break;
    case '9':
        column = 9;
        break;
    case ':':
        column = 10;
        break;
    case 'x':
        column = 11;
        break;
    case 'X':
        column = 11;
        break;
    case ' ':
        column = 12;
        break;
    default:
        column = 12;
        break;
    }

    srcRect.x = numWidth * column;
    srcRect.y = 0;
    dstRect.x = x;
    dstRect.y = y;

    srcRect.w = numWidth;
    srcRect.h = numHeight;
    dstRect.w = numWidth * scale;
    dstRect.h = numHeight * scale;

    SDL_RenderCopy(Game::Instance()->GetRenderer(), numTexture, &srcRect, &dstRect);
}

void TextPrinter::Draw(std::string str, int x, int y, int scale)
{
    for (std::string::size_type i = 0; i < str.size(); i++)
    {
        Draw(str[i], x + (i * numWidth * scale), y, scale);
    }
}