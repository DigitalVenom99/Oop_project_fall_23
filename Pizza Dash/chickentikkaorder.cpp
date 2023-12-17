#include "chickentikkaorder.hpp"

ChickenTikkaOrder::ChickenTikkaOrder(SDL_Renderer* renderer, int screenWidth)
    : Order(renderer, screenWidth), ingredientsCollected(0), SauceO(true), CheeseO(true), FlourO(true), ChickenO(true), CapsicumO(true) {
    // Load ingredient textures
    loadTexture("orderbox.png", orderboxTexture);
    loadTexture("Cheese.png", cheeseTexture);
    loadTexture("Flour.png", flourTexture);
    loadTexture("Sauce.png", sauceTexture);
    loadTexture("Chicken.png", chickenTexture);
    loadTexture("Capsicum.png", capsicumTexture);
}

ChickenTikkaOrder::~ChickenTikkaOrder() {
    // Free loaded textures
    SDL_DestroyTexture(orderboxTexture);
    SDL_DestroyTexture(cheeseTexture);
    SDL_DestroyTexture(flourTexture);
    SDL_DestroyTexture(sauceTexture);
    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyTexture(capsicumTexture);
}

ChickenTikkaOrder& ChickenTikkaOrder::operator+=(int increment) {
    ingredientsCollected += increment;
    return *this;
}

bool ChickenTikkaOrder::isOrderCompleted() const {
    return ingredientsCollected == totalIngredients;
}

void ChickenTikkaOrder::deleteSauceTexture() {
    SauceO = false;
}

void ChickenTikkaOrder::deleteFlourTexture() {
    FlourO = false;
}

void ChickenTikkaOrder::deleteChickenTexture() {
    ChickenO = false;
}

void ChickenTikkaOrder::deleteCapsicumTexture() {
    CapsicumO = false;
}

void ChickenTikkaOrder::deleteCheeseTexture() {
    CheeseO = false;
}

int ChickenTikkaOrder::getCTing_num() {
    return totalIngredients;
}

void ChickenTikkaOrder::reset() {
    SauceO = true;
    CheeseO = true;
    FlourO = true;
    ChickenO = true;
    CapsicumO = true;
}

void ChickenTikkaOrder::render() const {
    int ORDER_BOX_WIDTH = 500;
    int ORDER_BOX_HEIGHT = 300;

    const int ING_WIDTH = 30;
    const int ING_HEIGHT = 30;

    // Render the larger order box at the top-middle of the screen
    int orderBoxX = screenWidth / 2 - ORDER_BOX_WIDTH / 2;
    renderTexture(orderboxTexture, orderBoxX, -85, ORDER_BOX_WIDTH, ORDER_BOX_HEIGHT);

    if (FlourO == true) {
        renderTexture(flourTexture, orderBoxX + 200, ORDER_BOX_HEIGHT / 4 - ING_HEIGHT / 2, ING_WIDTH, ING_HEIGHT);
    }

    if (SauceO == true) {
        renderTexture(sauceTexture, orderBoxX + 250, ORDER_BOX_HEIGHT / 4 - ING_HEIGHT / 2, ING_WIDTH, ING_HEIGHT);
    }

    if (ChickenO == true) {
        renderTexture(chickenTexture, orderBoxX + 300, ORDER_BOX_HEIGHT / 4 - ING_HEIGHT / 2, ING_WIDTH, ING_HEIGHT);
    }

    if (CapsicumO == true) {
        renderTexture(capsicumTexture, orderBoxX + 350, ORDER_BOX_HEIGHT / 4 - ING_HEIGHT / 2, ING_WIDTH, ING_HEIGHT);
    }

    if (CheeseO == true) {
        renderTexture(cheeseTexture, orderBoxX + 150, ORDER_BOX_HEIGHT / 4 - ING_HEIGHT / 2, ING_WIDTH, ING_HEIGHT);
    }
}
