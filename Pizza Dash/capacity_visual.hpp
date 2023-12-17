#ifndef CAPACITY_VISUAL_HPP
#define CAPACITY_VISUAL_HPP

#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class CapacityVisual {
public:
    CapacityVisual(SDL_Renderer* renderer);

    ~CapacityVisual();

    void render(SDL_Renderer* renderer, int currentCapacity);

private:
    SDL_Texture* capacityTexture = nullptr;
    int x, y;
    static const int CAPACITY_WIDTH = 20;
    static const int CAPACITY_HEIGHT = 100;

    SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer);
};

#endif // CAPACITY_VISUAL_HPP
