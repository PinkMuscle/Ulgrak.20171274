#ifndef TextureManager_h
#define TextureManager_h
#include <SDL.h>
#include <string>
#include <map>

class TextureManager
{
public:
    ~TextureManager() {}
    static TextureManager* Instance()
    {
        if (pInstance == nullptr)
        {
            pInstance = new TextureManager();
        }
        return pInstance;
    }

    bool Load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
    void Draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void ClearFromTextureMap(std::string id);

private:
    TextureManager() {}
    static TextureManager* pInstance;

    std::map<std::string, SDL_Texture*> textureMap;
};

#endif