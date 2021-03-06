#ifndef MenuButton_h
#define MenuButton_h
#include "GameObject.h"

enum button_state
{
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
};

class MenuButton : public GameObject
{
public:
    MenuButton(const LoaderParams& pParams, void (*callback)());
    virtual void Draw();
    virtual void Update();

private:
    void(*callback)();

    bool released;
};

#endif