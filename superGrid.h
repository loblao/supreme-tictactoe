#pragma once

#include "object.h"
#include "grid.h"

class SuperGrid : public Object
{
    public:
		SuperGrid()
	
        virtual ~SuperGrid();

        virtual void draw(SDL_Renderer* renderer);

        void check();

        static SuperGrid* get_global_ptr();
     
    private:
		Grid* g
};
