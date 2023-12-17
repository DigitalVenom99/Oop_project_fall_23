#include "olive.hpp"

Olive::Olive(SDL_Renderer* renderer, int xPos) : Ingredient(renderer, xPos) {
    ingTexture = loadTexture("Olives.png", renderer);
    if (ingTexture == nullptr) {
        cerr << "Failed to load olives texture!" << endl;
    }
}

Olive::~Olive() {
    // Destructor implementation, automatically calls the base class destructor
}

void Olive::move() {
    y += ING_SPEED;
}

std::string Olive::get_name() {
    cout << "Get name called for Olive" << endl;
    return name;
}
