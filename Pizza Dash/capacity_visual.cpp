#include "capacity_visual.hpp"

CapacityVisual::CapacityVisual(SDL_Renderer* renderer) {
    capacityTexture = loadTexture("capacity.png", renderer);
    if (capacityTexture == nullptr) {
        cerr << "Failed to load capacity texture!" << endl;
    }

    x = 10;
    y = 0;
}

CapacityVisual::~CapacityVisual() {
    SDL_DestroyTexture(capacityTexture);
}

void CapacityVisual::render(SDL_Renderer* renderer, int currentCapacity) {
    SDL_Rect capacityRect = { x, y, CAPACITY_WIDTH * currentCapacity, CAPACITY_HEIGHT };
    SDL_RenderCopy(renderer, capacityTexture, nullptr, &capacityRect);
}

SDL_Texture* CapacityVisual::loadTexture(const string& path, SDL_Renderer* renderer) {
    SDL_Texture* texture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cerr << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
        return nullptr;
    }

    // Create texture from surface pixels
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == nullptr) {
        cerr << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << endl;
    }

    // Get rid of the loaded surface
    SDL_FreeSurface(loadedSurface);

    return texture;
}
