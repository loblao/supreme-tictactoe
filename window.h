#pragma once

#include "object.h"

#include <SDL.h>
#include <vector>

class Window
{
    public:
        Window();

        bool init(int w, int h, const char* title);
        void close();

        void handle_event(SDL_Event* event);
        void draw();

        void add_object(Object* obj);

        SDL_Texture* render_text(const char* text, int* w=nullptr, int* h=nullptr);

        static Window* get_global_ptr();

    private:
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

        std::vector<Object*> m_objects;

        int m_w;
        int m_h;
};
