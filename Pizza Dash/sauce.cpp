// sauce.cpp

#include "sauce.hpp"

Sauce::Sauce(SDL_Renderer* renderer, int xPos) : Ingredient(renderer, xPos) {
    ingTexture = loadTexture("Sauce.png", renderer);
    if (ingTexture == nullptr) {
        std::cerr << "Failed to load sauce texture!" << std::endl;
    }
}

void Sauce::move() {
    y += ING_SPEED;
}

std::string Sauce::get_name() {
    std::cout << "Get name called for Sauce" << std::endl;
    return name;
}
