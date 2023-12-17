#include "cheese.hpp"

Cheese::Cheese(SDL_Renderer* renderer, int xPos) : Ingredient(renderer, xPos) {
    ingTexture = loadTexture("Cheese.png", renderer);
    if (ingTexture == nullptr) {
        cerr << "Failed to load cheese texture!" << endl;
    }
}

Cheese::~Cheese() {
    // Destructor implementation, automatically calls the base class destructor
}

void Cheese::move() {
    y += ING_SPEED;
}

std::string Cheese::get_name() {
    cout << "Get name called for Cheese" << endl;
    return name;
}
