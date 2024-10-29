#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <functional>

class Button {

    private:
    SDL2pp::Rect rect;
    std::string label;
    bool mouse_encima;
    bool clickeo_boton(int x, int y) const;
    
    public:
    Button(int x, int y, int w, int h, const std::string& label);
    
    void render(SDL2pp::Renderer& renderer);
    void evento_click(const SDL_Event& event, std::function<void()> onClick);


};

#endif 
