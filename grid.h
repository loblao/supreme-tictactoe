#pragma once

#include "object.h"
#include "controller.h"

class Grid : public Object
{
    public:
        Grid(int index, int x, int y);
        virtual ~Grid();

        virtual void draw(SDL_Renderer* renderer);
        virtual void handle_click(int x, int y);

        virtual bool in_bounds(int x, int y);

        static Grid* get(int index);

        void reset();
        bool is_full();
        char get_winner();

    private:
        int m_x;
        int m_y;

        char m_grid[9];
        victory_t m_victory;
};
