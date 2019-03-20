#include "controller.h"

#include "globals.h"
#include "grid.h"

Controller::Controller() : m_turn('X'), m_next_grid(nullptr),
                           m_winner(0)
{
}

Controller* Controller::get_global_ptr()
{
    static Controller* ptr = new Controller;
    return ptr;
}

void Controller::next_turn()
{
    if (m_turn == 'X')
        m_turn = 'O';

    else
        m_turn = 'X';
}

char Controller::get_turn()
{
    return m_turn;
}

char Controller::get_turn_and_advance()
{
    char ret = get_turn();
    next_turn();
    return ret;
}

void Controller::set_next_grid(Grid* grid)
{
    if (!grid->is_full())
        m_next_grid = grid;

    else
        m_next_grid = nullptr;
}

Grid* Controller::get_next_grid()
{
    return m_next_grid;
}

void Controller::set_winner(char winner)
{
    m_winner = winner;
}

char Controller::get_winner()
{
    return m_winner;
}

void Controller::check_victory(const char* grid, victory_t* v)
{
    v->winner = 0;

    // Check cols
    v->mode = VictoryMode::V_col;
    for (int i = 0; i < NUM_GRIDS; i++)
    {
        switch (grid[NUM_SQUARES * i] + grid[NUM_SQUARES * i + 1] + grid[NUM_SQUARES * i + 2])
        {
            case 'X' * 3:
                v->winner = 'X';
                break;

            case 'O' * 3:
                v->winner = 'O';
                break;
        }

        v->arg = i;
        if (v->winner)
            return;
    }

    // Check lines
    v->mode = VictoryMode::V_line;
    for (int i = 0; i < NUM_GRIDS; i++)
    {
        switch (grid[i] + grid[i + NUM_SQUARES] + grid[i + 2 * NUM_SQUARES])
        {
            case 'X' * 3:
                v->winner = 'X';
                break;

            case 'O' * 3:
                v->winner = 'O';
                break;
        }

        v->arg = i;
        if (v->winner)
            return;
    }

    // Check first diagonal
    v->mode = VictoryMode::V_diag;
    v->arg = 0;

    switch (grid[0] + grid[4] + grid[8])
    {
        case 'X' * 3:
            v->winner = 'X';
            break;

        case 'O' * 3:
            v->winner = 'O';
            break;
    }

    if (v->winner)
        return;

    // Check second diagonal
    v->arg = 1;

    switch (grid[2] + grid[4] + grid[6])
    {
        case 'X' * 3:
            v->winner = 'X';
            break;

        case 'O' * 3:
            v->winner = 'O';
            break;
    }

    if (v->winner)
        return;

    // Maybe it's a draw?
    v->mode = VictoryMode::V_draw;
    for (int i = 0; i < NUM_SQUARES * NUM_SQUARES; i++)
    {
        if (grid[i] == 0)
        {
            // Nope...
            v->mode = VictoryMode::V_none;
        }
    }
}
