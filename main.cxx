#include <SDL.h>
#include <iostream>

#include "window.h"
#include "superGrid.h"
#include "grid.h"
#include "gameOverObject.h"
#include "globals.h"

int main(int argc, char** argv)
{
	Window* w = Window::get_global_ptr();

    // Open window
    int size = SQUARE_SIZE * NUM_SQUARES * NUM_GRIDS;
    if (!w->init(size, size, WINDOW_TITLE))
    {
        std::cerr << "SDL init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Spawn objects
    SuperGrid* sg = SuperGrid::get_global_ptr();
    w->add_object(sg);

    for (int i = 0; i < NUM_GRIDS; i++)
    {
        for (int j = 0; j < NUM_GRIDS; j++)
        {
            int grid_size = SQUARE_SIZE * NUM_SQUARES;
            w->add_object(new Grid(NUM_SQUARES * j + i, i * grid_size, j * grid_size));
        }
    }

    GameOverObject goo;
    w->add_object(&goo);

    // Main loop
    bool running = true;
    while (running)
    {
        // Handle events
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
                running = false;
				break;
			}

            w->handle_event(&e);
		}

        if (!running)
            break;

        w->draw();

        SDL_Delay(1.0 / FRAMES_PER_SECOND);
    }

    w->close();
    return 0;
}
