
#ifndef INGREDIENT_HPP
#define INGREDIENT_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

class Ingredient {
public:
    Ingredient(SDL_Renderer* renderer, int xPos);
    virtual ~Ingredient();

    virtual void move() = 0;
    virtual std::string get_name() = 0;
    void render(SDL_Renderer* renderer);
    SDL_Rect getCollisionBox() const;

protected:
    SDL_Texture* ingTexture = nullptr;
    int x, y;

    // Screen dimensions
    const int SCREEN_WIDTH = 880;
    const int SCREEN_HEIGHT = 800;

    // Ingredient dimensions
    const int ING_WIDTH = 60;
    const int ING_HEIGHT = 60;

    // Button dimensions
    const int BUTTON_WIDTH = 200;
    const int BUTTON_HEIGHT = 50;

    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
};

#endif
