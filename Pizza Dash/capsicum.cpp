#include "capsicum.hpp"

Capsicum::Capsicum(SDL_Renderer* renderer, int xPos) : Ingredient(renderer, xPos) {
    ingTexture = loadTexture("Capsicum.png", renderer);
    if (ingTexture == nullptr) {
        cerr << "Failed to load capsicum texture!" << endl;
    }
}

Capsicum::~Capsicum() {
    // Destructor implementation, automatically calls the base class destructor
}

void Capsicum::move() {
    y += ING_SPEED;
}

std::string Capsicum::get_name() {
    cout << "Get name called for Capsicum" << endl;
    return name;
}
