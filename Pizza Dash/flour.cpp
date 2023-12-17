#include "flour.hpp"

Flour::Flour(SDL_Renderer* renderer, int xPos) : Ingredient(renderer, xPos) {
    ingTexture = loadTexture("Flour.png", renderer);
    if (ingTexture == nullptr) {
        cerr << "Failed to load flour texture!" << endl;
    }
}

Flour::~Flour() {
    // Destructor implementation, automatically calls the base class destructor
}

void Flour::move() {
    y += ING_SPEED;
}

std::string Flour::get_name() {
    cout << "Get name called for Flour" << endl;
    return name;
}
