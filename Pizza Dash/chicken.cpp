#include "chicken.hpp"

Chicken::Chicken(SDL_Renderer* renderer, int xPos) : Ingredient(renderer, xPos) {
    ingTexture = loadTexture("Chicken.png", renderer);
    if (ingTexture == nullptr) {
        cerr << "Failed to load chicken texture!" << endl;
    }
}

Chicken::~Chicken() {
    // Destructor implementation, automatically calls the base class destructor
}

void Chicken::move() {
    y += ING_SPEED;
}

std::string Chicken::get_name() {
    cout << "Get name called for Chicken" << endl;
    return name;
}
