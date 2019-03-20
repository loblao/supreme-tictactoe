#pragma once

#include <SDL.h>

class Object
{
    public:
        virtual ~Object();

        virtual void step();
        virtual void draw(SDL_Renderer* renderer);
        virtual void handle_click(int x, int y);
        virtual void handle_key(SDL_Keycode key);

        virtual bool in_bounds(int x, int y);
};
