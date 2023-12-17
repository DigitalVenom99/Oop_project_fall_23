#ifndef ORDER_HPP
#define ORDER_HPP

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

using namespace std;

class Order {
public:
    Order(SDL_Renderer* renderer, int screenWidth);
    virtual ~Order();

    virtual void render() const = 0;

    void loadTexture(const string& filename, SDL_Texture*& texture);
    void renderTexture(SDL_Texture* texture, int x, int y, int width, int height) const;

protected:
    SDL_Renderer* renderer;
    int screenWidth;

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

#endif // ORDER_HPP
