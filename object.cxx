#include "object.h"

Object::~Object()
{
}

void Object::step()
{
}

void Object::draw(SDL_Renderer*)
{
}

void Object::handle_click(int x, int y)
{
}

void Object::handle_key(SDL_Keycode key)
{
}

bool Object::in_bounds(int x, int y)
{
    return false;
}
