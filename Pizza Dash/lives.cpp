#include "lives.hpp"

Lives::Lives(SDL_Renderer* renderer, int totalLives) : totalLives(totalLives), currentLives(totalLives) {
    lifeTexture = loadTexture("Life.png", renderer);
    if (lifeTexture == nullptr) {
        std::cerr << "Failed to load life texture!" << std::endl;
    }
    x = SCREEN_WIDTH - 50;
    y = 10;
}

Lives::~Lives() {
    SDL_DestroyTexture(lifeTexture);
}

void Lives::render(SDL_Renderer* renderer) {
    for (int i = 0; i < currentLives; ++i) {
        SDL_Rect lifeRect = {x - i * (LIFE_WIDTH + LIFE_SPACING), y, LIFE_WIDTH, LIFE_HEIGHT};
        SDL_RenderCopy(renderer, lifeTexture, nullptr, &lifeRect);
    }
}

SDL_Texture* Lives::loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* texture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // Create texture from surface pixels
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    // Get rid of the loaded surface
    SDL_FreeSurface(loadedSurface);

    return texture;
}

void Lives::decrement() {
    if (currentLives > 0) {
        --currentLives;
    }
}

int Lives::getCurrentLives() const {
    return currentLives;
}

void Lives::reset() {
    currentLives = totalLives;
}
