#include "ingredient.hpp"

Ingredient::Ingredient(SDL_Renderer* renderer, int xPos) : x(xPos), y(0) {}

Ingredient::~Ingredient() {
    SDL_DestroyTexture(ingTexture);
}

void Ingredient::render(SDL_Renderer* renderer) {
    SDL_Rect ingRect = {x, y, ING_WIDTH, ING_HEIGHT};
    SDL_RenderCopy(renderer, ingTexture, nullptr, &ingRect);
}

SDL_Rect Ingredient::getCollisionBox() const {
    return {x, y, ING_WIDTH, ING_HEIGHT};
}

SDL_Texture* Ingredient::loadTexture(const string& path, SDL_Renderer* renderer) {
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
