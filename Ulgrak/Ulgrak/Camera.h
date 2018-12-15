#ifndef Camera_h
#define Camera_h

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
    float GetX() const { return x; }
    void SetX(float x) { this->x = x; }
    void Follow(float dstX, float speed);

private:
    Camera() {}
    static Camera* pInstance;
    float x = 0;
};

#endif