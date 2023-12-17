#include "obstacle.hpp"

Obstacle::Obstacle(SDL_Renderer* renderer, int xPos) : x(xPos), y(0) {}

Obstacle::~Obstacle() {
    SDL_DestroyTexture(obstacleTexture);
}


void Obstacle::render(SDL_Renderer* renderer) {
    SDL_Rect obstacleRect = { x, y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT };
    SDL_RenderCopy(renderer, obstacleTexture, nullptr, &obstacleRect);
}

SDL_Rect Obstacle::getCollisionBox() const {
    return { x, y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT };
}

