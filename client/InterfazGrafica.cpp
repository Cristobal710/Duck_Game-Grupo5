#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace SDL2pp;

int main() try {

	// Initialize SDL library
	SDL sdl(SDL_INIT_VIDEO);

	 // Initialize SDL_image
    IMG_Init(IMG_INIT_PNG);

	// Create main window
    SDL2pp::Window window("SDL2 Image Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
    
    // Create renderer
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL2pp::Surface loadedSurface(IMG_Load("../resources/Grey-Duck.png"));
    
    // Create texture from surface using SDL2pp::Texture
    SDL2pp::Texture texture(renderer, loadedSurface);

    // Clear screen
    renderer.Clear();

    // Copy texture to renderer
    renderer.Copy(texture);

    // Show rendered frame
    renderer.Present();

    // 5 second delay
    SDL_Delay(5000); 

    // Clean up SDL_image
    IMG_Quit();
    return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	
}
