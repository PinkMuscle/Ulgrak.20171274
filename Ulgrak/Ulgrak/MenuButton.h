#ifndef MenuButton_h
#define MenuButton_h
#include "SDLGameObject.h"

enum button_state
{
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
};

class MenuButton : public SDLGameObject
{
public:
    MenuButton(const LoaderParams* pParams, void (*callback)());
    virtual void Draw();
    virtual void Update();
    virtual void Clean();

private:
    bool released;

    void(*callback)();
};

#endif