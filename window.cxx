#include "window.h"

#include "globals.h"

#include <SDL_ttf.h>

static TTF_Font* get_font()
{
    static TTF_Font* font = TTF_OpenFont(FONT_FILENAME, FONT_PTSIZE);
    return font;
}

Window::Window() : m_window(nullptr), m_renderer(nullptr)
{
}

Window* Window::get_global_ptr()
{
    static Window* ptr = new Window;
    return ptr;
}

bool Window::init(int w, int h, const char* title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    if (TTF_Init() == -1)
        return false;

    if (get_font() == nullptr)
	return false;

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w, h, SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
        return false;

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr)
        return false;

    return true;
}

void Window::close()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    TTF_Quit();
    SDL_Quit();

    m_window = nullptr;
    m_renderer = nullptr;
}

void Window::handle_event(SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            for (auto obj : m_objects)
                if (obj->in_bounds(x, y))
                    obj->handle_click(x, y);

            break;

        case SDL_KEYDOWN:
            for (auto obj : m_objects)
                obj->handle_key(event->key.keysym.sym);

            break;
    }
}

void Window::draw()
{
    // Clear screen
    SDL_SetRenderDrawColor(m_renderer, BACKGROUND_COLOR);
    SDL_RenderClear(m_renderer);

    // Draw objects
    for (auto obj : m_objects)
        obj->draw(m_renderer);

    SDL_RenderPresent(m_renderer);
}

void Window::add_object(Object* obj)
{
    m_objects.push_back(obj);
}

SDL_Texture* Window::render_text(const char* text, int* w, int* h)
{
    SDL_Color color = {TEXT_COLOR};
    SDL_Surface* surface = TTF_RenderText_Solid(get_font(), text, color);
    if (surface == nullptr)
        return nullptr;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (tex != nullptr)
    {
        if (w != nullptr) *w = surface->w;
        if (h != nullptr) *h = surface->h;
    }

    SDL_FreeSurface(surface);

    return tex;
}
