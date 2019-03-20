#pragma once

#include "object.h"

class SuperGrid : public Object
{
    public:
        virtual ~SuperGrid();

        virtual void draw(SDL_Renderer* renderer);

        void check();

        static SuperGrid* get_global_ptr();
};
