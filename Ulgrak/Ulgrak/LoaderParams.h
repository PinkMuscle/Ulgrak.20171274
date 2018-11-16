#ifndef LoaderParams_h
#define LoaderParams_h
#include <string>

class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID) : x(x), y(y), width(width), height(height), textureID(textureID) {}
    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    std::string GetTextureID() const { return textureID; }

private:
    int x;
    int y;
    int width;
    int height;
    std::string textureID;
};

#endif
