#include "button.h"

Button::Button(int x, int y, int w, int h, const std::string& label)
    : rect(x, y, w, h), label(label), mouse_encima(false) {}

void Button::render(SDL2pp::Renderer& renderer) {
    
    if (mouse_encima) {
        renderer.SetDrawColor(200, 200, 200, 255);
    } else {
        renderer.SetDrawColor(100, 100, 100, 255);
    }
    renderer.FillRect(rect);
}

void Button::evento_click(const SDL_Event& event, std::function<void()> onClick) {
    if (event.type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        mouse_encima = clickeo_boton(x, y);
    }
    
    if (event.type == SDL_MOUSEBUTTONDOWN && mouse_encima) {
        onClick(); 
    }
}

bool Button::clickeo_boton(int x, int y) const {
    return x >= rect.x && x <= (rect.x + rect.w) &&
           y >= rect.y && y <= (rect.y + rect.h);
}