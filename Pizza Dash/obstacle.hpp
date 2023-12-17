#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Obstacle {
public:
    Obstacle(SDL_Renderer* renderer, int xPos);
    virtual ~Obstacle();

    virtual void move() = 0;
    void render(SDL_Renderer* renderer);
    SDL_Rect getCollisionBox() const;

protected:
    SDL_Texture* obstacleTexture = nullptr;
    
    int x, y;
    // Screen dimensions
    const int SCREEN_WIDTH = 880;
    const int SCREEN_HEIGHT = 800;

    // Player dimensions
    const int PLAYER_WIDTH = 100;
    const int PLAYER_HEIGHT = 100;

    // Obstacle dimensions
    const int OBSTACLE_WIDTH = 100;
    const int OBSTACLE_HEIGHT = 100;

    // Ingredients dimensions
    const int ING_WIDTH = 60;
    const int ING_HEIGHT = 60;

    // Button dimensions
    const int BUTTON_WIDTH = 200;
    const int BUTTON_HEIGHT = 50;
};

#endif // OBSTACLE_HPP
