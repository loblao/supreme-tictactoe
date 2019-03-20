#pragma once

#include "object.h"
#include "controller.h"

class GameOverObject : public Object
{
    public:
        virtual ~GameOverObject();

        virtual void handle_key(SDL_Keycode key);

        virtual void draw(SDL_Renderer* renderer);
};
