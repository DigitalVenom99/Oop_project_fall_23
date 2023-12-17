#include "car.hpp"

Car::Car(SDL_Renderer* renderer, int xPos, Player* playerPtr)
    : Obstacle(renderer, xPos), player(playerPtr) {
    obstacleTexture = loadTexture("Car_2.png", renderer);
    if (obstacleTexture == nullptr) {
        cerr << "Failed to load car texture!" << endl;
    }
}
SDL_Texture* Car::loadTexture(const string& path, SDL_Renderer* renderer) {
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

void Car::move() {
    if (player) {
        int playerX = player->getX();
        int playerY = player->getY();
        int directionX = playerX - x;
        int directionY = playerY - y;

        // Check if the car is already at the player's position
        bool atPlayerPosition = (directionX == 0 && directionY == 0);

        // Avoid updating position if already at the player's position
        if (!atPlayerPosition) {
            int absDirectionX = abs(directionX);
            int absDirectionY = abs(directionY);

            // Check if absDirectionX is not zero to avoid division by zero
            if (absDirectionX != 0) {
                x += static_cast<int>(OBSTACLE_SPEED * directionX / absDirectionX);
            }

            // Check if absDirectionY is not zero to avoid division by zero
            if (absDirectionY != 0) {
                y += static_cast<int>(OBSTACLE_SPEED * directionY / absDirectionY);
            }
        }
    } else {
        cout << "Player pointer is null!" << endl;
    }
}
