#include "order.hpp"

Order::Order(SDL_Renderer* renderer, int screenWidth)
    : renderer(renderer), screenWidth(screenWidth),
      SCREEN_WIDTH(880), SCREEN_HEIGHT(800),
      PLAYER_WIDTH(100), PLAYER_HEIGHT(100),
      OBSTACLE_WIDTH(100), OBSTACLE_HEIGHT(100),
      ING_WIDTH(60), ING_HEIGHT(60),
      BUTTON_WIDTH(200), BUTTON_HEIGHT(50) {}

Order::~Order() {}

void Order::loadTexture(const string& filename, SDL_Texture*& texture) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface) {
        cerr << "Failed to load texture: " << filename << endl;
        exit(-1);
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        cerr << "Failed to create texture from surface: " << filename << endl;
        exit(-1);
    }
}

void Order::renderTexture(SDL_Texture* texture, int x, int y, int width, int height) const {
    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}
