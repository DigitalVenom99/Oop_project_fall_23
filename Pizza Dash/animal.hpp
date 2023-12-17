#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "obstacle.hpp"
#include <string>  // Include this line for the string type
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Animal : public Obstacle {
public:
    Animal(SDL_Renderer* renderer, int xPos);
    void move() override;

private:
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);

    static const int OBSTACLE_SPEED = 2;
    static const Uint32 BOOST_INTERVAL = 1000;
    static const Uint32 BOOST_DURATION = 750;
    Uint32 lastBoostTime = 0;
    Uint32 boostTimer = 0;
    bool boostActivated = false;
};

#endif
