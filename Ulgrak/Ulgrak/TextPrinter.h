#ifndef TextPrinter_h
#define TextPrinter_h
#include <SDL.h>
#include <string>

class TextPrinter
{
public:
    ~TextPrinter()
    {
        if (numTexture != nullptr) SDL_DestroyTexture(numTexture);
    }
    static TextPrinter* Instance()
    {
        if (pInstance == nullptr)
        {
            pInstance = new TextPrinter();
            pInstance->Init();
        }
        return pInstance;
    }

    void Draw(char ch, int x, int y, int scale = 1);
    void Draw(std::string str, int x, int y, int scale = 1);

private:
    TextPrinter() {}
    static TextPrinter* pInstance;
    bool Init();

    SDL_Texture* numTexture = nullptr;
};

#endif