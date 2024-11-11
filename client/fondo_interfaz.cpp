#include "fondo_interfaz.h"
#include <SDL2/SDL_image.h>

FondoInterfaz::FondoInterfaz(SDL2pp::Renderer& renderer, const std::string& fondo_path):
        fondo_texture(renderer, SDL2pp::Surface(IMG_Load(fondo_path.c_str()))) {}

/*void FondoInterfaz::dibujar(SDL2pp::Renderer& renderer, float zoom_factor) {
    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer.Get(), &window_width, &window_height);

    // Scale the background size based on the zoom factor
    SDL2pp::Rect destination_rect(
        0, 0,
        static_cast<int>(window_width * zoom_factor),
        static_cast<int>(window_height * zoom_factor)
    );

    // Center the background if it's zoomed in
    destination_rect.x = (window_width - destination_rect.w) / 2;
    destination_rect.y = (window_height - destination_rect.h) / 2;

    renderer.Copy(fondo_texture, SDL2pp::Optional<SDL2pp::Rect>(), destination_rect);
}*/

/*void FondoInterfaz::dibujar(SDL2pp::Renderer& renderer, float zoom_factor, int duck_x, int duck_y) {
    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer.Get(), &window_width, &window_height);

    // Scale the background size based on the zoom factor
    //int scaled_width = static_cast<int>(fondo_texture.GetWidth() * zoom_factor);
    //int scaled_height = static_cast<int>(fondo_texture.GetHeight() * zoom_factor);

    // Calculate the offset so the duck stays in the center
    int offset_x = static_cast<int>(duck_x * zoom_factor) - (window_width / 2);
    int offset_y = static_cast<int>(duck_y * zoom_factor) - (window_height / 2);

    // Define the destination rectangle with adjusted position and scale
    SDL2pp::Rect destination_rect(
        -offset_x, // Move background to keep duck centered
        -offset_y, // Move background to keep duck centered
        static_cast<int>(window_width * zoom_factor),
        static_cast<int>(window_height * zoom_factor)
    );

    // Render the background with the calculated offset and scaling
    renderer.Copy(fondo_texture, SDL2pp::Optional<SDL2pp::Rect>(), destination_rect);
}*/

void FondoInterfaz::dibujar(SDL2pp::Renderer& renderer, float min_zoom, float max_zoom, 
                            int duck1_x, int duck1_y, int duck2_x, int duck2_y) {
    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer.Get(), &window_width, &window_height);

    // Calculate the distance between the two ducks
    float distance = std::sqrt(std::pow(duck2_x - duck1_x, 2) + std::pow(duck2_y - duck1_y, 2));

    // Adjust the zoom factor based on the distance between ducks
    // Here we normalize the distance within a range to map it to zoom levels
    float zoom_factor = std::max(min_zoom, std::min(max_zoom, max_zoom - (distance / 300.0f))); // Adjust 300.0f as needed

    // Calculate the midpoint between the two ducks
    int center_x = (duck1_x + duck2_x) / 2;
    int center_y = (duck1_y + duck2_y) / 2;

    // Get the original size of the background
    int background_width = fondo_texture.GetWidth();
    int background_height = fondo_texture.GetHeight();

    // Scale the background size based on the zoom factor
    int scaled_width = static_cast<int>(background_width * zoom_factor);
    int scaled_height = static_cast<int>(background_height * zoom_factor);

    // Calculate offset to keep the midpoint centered
    int offset_x = static_cast<int>(center_x * zoom_factor) - (window_width / 2);
    int offset_y = static_cast<int>(center_y * zoom_factor) - (window_height / 2);

    // Clamp the offset to ensure the background doesn’t move beyond its boundaries
    offset_x = std::max(0, std::min(offset_x, scaled_width - window_width));
    offset_y = std::max(0, std::min(offset_y, scaled_height - window_height));

    // Define the destination rectangle for the background with the adjusted position and scale
    SDL2pp::Rect destination_rect(
        -offset_x, -offset_y, scaled_width, scaled_height
    );

    // Render the background with the calculated offset and scaling
    renderer.Copy(fondo_texture, SDL2pp::Optional<SDL2pp::Rect>(), destination_rect);
}



