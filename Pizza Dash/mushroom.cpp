#include "mushroom.hpp"

Mushroom::Mushroom(SDL_Renderer* renderer, int xPos) : Ingredient(renderer, xPos) {
    ingTexture = loadTexture("Mushroom.png", renderer);
    if (ingTexture == nullptr) {
        cerr << "Failed to load Mushroom texture!" << endl;
    }
}

Mushroom::~Mushroom() {
    // Destructor implementation, automatically calls the base class destructor
}

void Mushroom::move() {
    y += ING_SPEED;
}

std::string Mushroom::get_name() {
    cout << "Get name called for Mushroom" << endl;
    return name;
}
