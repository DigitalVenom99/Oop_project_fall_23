#include "animal.hpp"
#include <iostream>

Animal::Animal(SDL_Renderer* renderer, int xPos) : Obstacle(renderer, xPos) {
    obstacleTexture = loadTexture("Cow.png", renderer);
    if (obstacleTexture == nullptr) {
        std::cerr << "Failed to load Animal texture!" << std::endl;
    }
}

void Animal::move() {
    if (boostTimer > 0) {
        y += 3 * OBSTACLE_SPEED;
        boostTimer -= OBSTACLE_SPEED;
    } else {
        y += OBSTACLE_SPEED;
        if (!boostActivated && x >= SCREEN_WIDTH / 2) {
            boostTimer = BOOST_DURATION;
            boostActivated = true;
            lastBoostTime = SDL_GetTicks();
        }
    }
}

SDL_Texture* Animal::loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* texture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(loadedSurface);

    return texture;
}
