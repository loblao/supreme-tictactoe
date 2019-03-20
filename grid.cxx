#include "grid.h"

#include "globals.h"
#include "window.h"
#include "controller.h"
#include "superGrid.h"

static SDL_Texture* s_tex_x = nullptr;
static SDL_Texture* s_tex_o = nullptr;

static Grid* s_map[9];
Grid* Grid::get(int index)
{
    return s_map[index];
}

static struct {
    Grid* grid = nullptr;
    int index;
} s_last;

Grid::Grid(int index, int x, int y) : m_x(x), m_y(y)
{
    if (s_tex_x == nullptr)
    {
        Window* w = Window::get_global_ptr();
        s_tex_x = w->render_text("X");
        s_tex_o = w->render_text("O");
    }

    s_map[index] = this;

    reset();
}

Grid::~Grid()
{
}

void Grid::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, LINE_COLOR);

    // Vertical lines
    for (int i = 1; i < NUM_SQUARES; i++)
        SDL_RenderDrawLine(renderer,
                           m_x + SQUARE_SIZE * i,
                           m_y,
                           m_x + SQUARE_SIZE * i,
                           m_y + SQUARE_SIZE * NUM_SQUARES);

    // Horizontal lines
    for (int i = 1; i < NUM_GRIDS; i++)
        SDL_RenderDrawLine(renderer,
                           m_x,
                           m_y + SQUARE_SIZE * i,
                           m_x + SQUARE_SIZE * NUM_SQUARES,
                           m_y + SQUARE_SIZE * i);

    // Xs and Os
    for (int i = 0; i < NUM_SQUARES; i++)
    {
        for (int j = 0; j < NUM_SQUARES; j++)
        {
            int index = NUM_SQUARES * i + j;
            SDL_Rect render_quad = {m_x + SQUARE_SIZE * (i + 0.5) - FONT_PTSIZE / 2,
                                    m_y + SQUARE_SIZE * (j + 0.5) - FONT_PTSIZE / 2,
                                    FONT_PTSIZE, FONT_PTSIZE};

            if (s_last.grid == this && s_last.index == index)
            {
                SDL_Rect fill_rect = {m_x + SQUARE_SIZE * i + 1,
                                      m_y + SQUARE_SIZE * j + 1,
                                      SQUARE_SIZE - 1,
                                      SQUARE_SIZE - 1};
				SDL_SetRenderDrawColor(renderer, LAST_HIGHLIGHT_COLOR);
				SDL_RenderFillRect(renderer, &fill_rect);
                SDL_SetRenderDrawColor(renderer, LINE_COLOR);
            }

            char c = m_grid[index];
            if (c == 'X')
                SDL_RenderCopy(renderer, s_tex_x, nullptr, &render_quad);

            else if (c == 'O')
                SDL_RenderCopy(renderer, s_tex_o, nullptr, &render_quad);
        }
    }

    // Crossing lines
    int padding = XLINE_PADDING;
    int x, y, x1, x2;

    switch (m_victory.mode)
    {
        case VictoryMode::V_line:
            y = m_y + SQUARE_SIZE * (m_victory.arg + 0.5);
            SDL_RenderDrawLine(renderer,
                               m_x + padding,
                               y,
                               m_x + SQUARE_SIZE * NUM_SQUARES - padding,
                               y);
            break;

        case VictoryMode::V_col:
            x = m_x + SQUARE_SIZE * (m_victory.arg + 0.5);
            SDL_RenderDrawLine(renderer,
                               x,
                               m_y + padding,
                               x,
                               m_y + SQUARE_SIZE * NUM_SQUARES - padding);
            break;

        case VictoryMode::V_diag:
            if (m_victory.arg == 0)
            {
                x1 = m_x + padding;
                x2 = m_x + SQUARE_SIZE * NUM_SQUARES - padding;
            }

            else
            {
                x1 = m_x + SQUARE_SIZE * NUM_SQUARES - padding;
                x2 = m_x + padding;
            }

            SDL_RenderDrawLine(renderer,
                               x1,
                               m_y + padding,
                               x2,
                               m_y + SQUARE_SIZE * NUM_SQUARES - padding);

            break;
    }
}

void Grid::handle_click(int x, int y)
{
    static Controller* ctrl = Controller::get_global_ptr();
    static SuperGrid* sg = SuperGrid::get_global_ptr();

    if (ctrl->get_winner())
        return; // Game is over

    x -= m_x;
    y -= m_y;

    int i = x / SQUARE_SIZE;
    int j = y / SQUARE_SIZE;

    Grid* next = ctrl->get_next_grid();
    if (next != nullptr && next != this || is_full())
        return;

    if (m_grid[NUM_SQUARES * i + j] != '\0')
        return;

    m_grid[NUM_SQUARES * i + j] = ctrl->get_turn_and_advance();
    ctrl->check_victory(m_grid, &m_victory);

    ctrl->set_next_grid(Grid::get(NUM_SQUARES * j + i));
    sg->check();

    s_last.grid = this;
    s_last.index = NUM_SQUARES * i + j;
}

bool Grid::in_bounds(int x, int y)
{
    if (x <= m_x || x >= m_x + SQUARE_SIZE * NUM_SQUARES)
        return false;

    if (y <= m_y || y >= m_y + SQUARE_SIZE * NUM_SQUARES)
        return false;

    return true;
}

void Grid::reset()
{
    memset(m_grid, 0, sizeof(m_grid));
    m_victory.mode = VictoryMode::V_none;

    s_last.grid = nullptr;
}

bool Grid::is_full()
{
    return m_victory.mode != VictoryMode::V_none;
}

char Grid::get_winner()
{
    if (m_victory.mode == VictoryMode::V_none)
        return 0;

    if (m_victory.mode == VictoryMode::V_draw)
        return '-';

    return m_victory.winner;
}
