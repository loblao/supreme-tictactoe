#include "superGrid.h"

#include "globals.h"

SuperGrid::SuperGrid()
{
	g = nullptr;
}

SuperGrid::~SuperGrid()
{
}

SuperGrid* SuperGrid::get_global_ptr()
{
    static SuperGrid* ptr = new SuperGrid;
    return ptr;
}

void SuperGrid::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, LINE_COLOR);

    int grid_size = SQUARE_SIZE * NUM_SQUARES;

    // Vertical lines
    for (int i = 1; i < NUM_GRIDS; i++)
    {
        SDL_RenderDrawLine(renderer, grid_size * i - 1, 0, grid_size * i - 1, grid_size * NUM_GRIDS);
        SDL_RenderDrawLine(renderer, grid_size * i, 0, grid_size * i, grid_size * NUM_GRIDS);
        SDL_RenderDrawLine(renderer, grid_size * i + 1, 0, grid_size * i + 1, grid_size * NUM_GRIDS);
    }

    // Horizontal lines
    for (int i = 1; i < NUM_GRIDS; i++)
    {
        SDL_RenderDrawLine(renderer, 0, grid_size * i - 1, grid_size * NUM_GRIDS, grid_size * i - 1);
        SDL_RenderDrawLine(renderer, 0, grid_size * i, grid_size * NUM_GRIDS, grid_size * i);
        SDL_RenderDrawLine(renderer, 0, grid_size * i + 1, grid_size * NUM_GRIDS, grid_size * i + 1);
    }
}

void SuperGrid::check()
{
    static Controller* ctrl = Controller::get_global_ptr();

    // Collect grid info
    char grid[NUM_GRIDS * NUM_GRIDS];
    for (int i = 0; i < NUM_GRIDS; i++)
    {
        for (int j = 0; j < NUM_GRIDS; j++)
        {
            int index = NUM_SQUARES * j + i;
            g = Grid::get(index);
            grid[index] = g->get_winner();
        }
    }

    victory_t v;
    ctrl->check_victory(grid, &v);
    if (v.mode != VictoryMode::V_none)
        ctrl->set_winner(v.mode == VictoryMode::V_draw ? '-' : v.winner);
}
