#ifndef Camera_h
#define Camera_h
#include <vector>
#include <memory>
#include "GameObject.h"
class Camera
{
public:
    ~Camera() {}
    static Camera* Instance()
    {
        if (pInstance == nullptr)
        {
            pInstance = new Camera();
        }
        return pInstance;
    }
    void Update(const std::vector<std::unique_ptr<GameObject>>& players);
    void Init();
    int GetXOnCamera(const float& objX) const;
    int GetYOnCamera(const float& objY) const;
    float GetScale() const { return objScale; }

private:
    Camera() {}
    static Camera* pInstance;

    float leftX;
    float rightX;
    float upY;
    float downY;

    float oldLeftX;
    float oldRightX;
    float oldUpY;

    float objScale;
};

#endif