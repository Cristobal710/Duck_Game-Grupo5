#include "button.h"

Button::Button(int x, int y, int w, int h, const std::string& label, TTF_Font* fuente)
    : rect(x, y, w, h), label(label), mouse_encima(false), font(fuente),
    textColor(255, 255, 255)  {}

    void Button::render(SDL2pp::Renderer& renderer) {

        if (mouse_encima) {
            renderer.SetDrawColor(200, 200, 200, 255);
        } else {
            renderer.SetDrawColor(100, 100, 100, 255);
        }
        renderer.FillRect(rect);
        // Render the label text inside the button using SDL2pp::Renderer
    if (font != nullptr) {
        // Create surface from TTF text
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, label.c_str(), textColor);  // Render text with white color
        if (textSurface) {
            // Create texture from surface (SDL2pp::Texture)
            SDL2pp::Surface surface(textSurface);  // Wrap surface in SDL2pp::Surface for automatic cleanup
            SDL2pp::Texture textTexture(renderer, surface);  // Create texture from surface
            
            // Calculate text size and position
            int textWidth = textSurface->w;
            int textHeight = textSurface->h;
            SDL2pp::Rect textRect = { rect.x + (rect.w - textWidth) / 2, rect.y + (rect.h - textHeight) / 2, textWidth, textHeight };

            // Copy the texture to the renderer (draw the text)
            renderer.Copy(textTexture, SDL2pp::Optional<SDL2pp::Rect>(), textRect);
        }
    }
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