#ifndef LIVES_HPP
#define LIVES_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Lives {
public:
    Lives(SDL_Renderer* renderer, int totalLives);
    ~Lives();

    void render(SDL_Renderer* renderer);
    void decrement();
    int getCurrentLives() const;
    void reset();

private:
    SDL_Texture* lifeTexture = nullptr;
    int x, y;
    int totalLives;
    int currentLives;
    static const int LIFE_WIDTH = 30;
    static const int LIFE_HEIGHT = 30;
    static const int LIFE_SPACING = 5;
    const int SCREEN_WIDTH = 880;
    const int SCREEN_HEIGHT = 800;

    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
};

#endif
