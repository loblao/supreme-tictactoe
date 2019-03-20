#include "gameOverObject.h"

#include "globals.h"
#include "controller.h"
#include "window.h"
#include "grid.h"

static SDL_Texture* s_text_winner_x = nullptr;
static SDL_Texture* s_text_winner_o = nullptr;
static SDL_Texture* s_text_draw = nullptr;
static SDL_Texture* s_text_cont = nullptr;

static SDL_Rect s_text_winner_x_rect;
static SDL_Rect s_text_winner_o_rect;
static SDL_Rect s_text_draw_rect;
static SDL_Rect s_text_cont_rect;

GameOverObject::~GameOverObject()
{
}

void GameOverObject::handle_key(SDL_Keycode key)
{
    static Controller* ctrl = Controller::get_global_ptr();
    if (!ctrl->get_winner())
        return;

    if (key != SDLK_RETURN)
        return;

    ctrl->set_winner(0);

    for (int i = 0; i < NUM_GRIDS; i++)
        for (int j = 0; j < NUM_GRIDS; j++)
            Grid::get(NUM_SQUARES * j + i)->reset();
}

void GameOverObject::draw(SDL_Renderer* renderer)
{
    static Controller* ctrl = Controller::get_global_ptr();
    static Window* window = Window::get_global_ptr();

    char w = ctrl->get_winner();
    if (!w)
        return;

    int screen_size = SQUARE_SIZE * NUM_SQUARES * NUM_GRIDS;

    SDL_Rect rect = {screen_size / 11, screen_size * 5 / 11, screen_size * 9 / 11, screen_size * 2 / 11};
	SDL_SetRenderDrawColor(renderer, GAME_OVER_BG_COLOR);
	SDL_RenderFillRect(renderer, &rect);

    if (s_text_draw == nullptr)
    {
        s_text_draw = window->render_text(GAME_OVER_TEXT_DRAW,
            &s_text_draw_rect.w, &s_text_draw_rect.h);
        s_text_winner_x = window->render_text(GAME_OVER_TEXT_X,
            &s_text_winner_x_rect.w, &s_text_winner_x_rect.h);
        s_text_winner_o = window->render_text(GAME_OVER_TEXT_O,
            &s_text_winner_o_rect.w, &s_text_winner_o_rect.h);
        s_text_cont = window->render_text(GAME_OVER_TEXT_CONT,
            &s_text_cont_rect.w, &s_text_cont_rect.h);

        s_text_draw_rect.x = screen_size / 2 - s_text_draw_rect.w / 2;
        s_text_draw_rect.y = screen_size * 5 / 11 + FONT_PTSIZE / 2;

        s_text_winner_x_rect.x = screen_size / 2 - s_text_winner_x_rect.w / 2;
        s_text_winner_x_rect.y = screen_size * 5 / 11 + FONT_PTSIZE / 2;

        s_text_winner_o_rect.x = screen_size / 2 - s_text_winner_o_rect.w / 2;
        s_text_winner_o_rect.y = screen_size * 5 / 11 + FONT_PTSIZE / 2;

        s_text_cont_rect.x = screen_size / 2 - s_text_cont_rect.w / 2;
        s_text_cont_rect.y = screen_size * 5 / 11 + FONT_PTSIZE / 2 * 5;
    }

    SDL_Texture* tex;
    SDL_Rect* tex_rect;

    if (w == 'X')
    {
        tex = s_text_winner_x;
        tex_rect = &s_text_winner_x_rect;
    }

    else if (w == 'O')
    {
        tex = s_text_winner_o;
        tex_rect = &s_text_winner_o_rect;
    }

    else
    {
        tex = s_text_draw;
        tex_rect = &s_text_draw_rect;
    }

    SDL_RenderCopy(renderer, tex, nullptr, tex_rect);
    SDL_RenderCopy(renderer, s_text_cont, nullptr, &s_text_cont_rect);
}
