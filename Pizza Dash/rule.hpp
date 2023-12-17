#ifndef RULE_HPP
#define RULE_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

// Screen dimensions
const int SCREEN_WIDTH = 880;
const int SCREEN_HEIGHT = 800;

// Player dimensions
const int PLAYER_WIDTH = 100;
const int PLAYER_HEIGHT = 100;

// Obstacle dimensions
const int OBSTACLE_WIDTH = 100;
const int OBSTACLE_HEIGHT = 100;


// Ingredients dimensions
const int ING_WIDTH = 60;
const int ING_HEIGHT = 60;

// Button dimensions
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 50;

using namespace std;

class Rule {
public:
    Rule(SDL_Renderer* renderer);
    ~Rule();

    void render(SDL_Renderer* renderer);
    bool handleBackButtonEvent(SDL_Event& e);

private:
    SDL_Texture* ruleTexture = nullptr;
    TTF_Font* font = nullptr;
    SDL_Rect backButtonRect;
    bool showBackButton = true;
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
    bool isPointInsideRect(int x, int y, const SDL_Rect& rect);
    bool handleButtonClickEvent(SDL_Event& e, const SDL_Rect& buttonRect);
    void renderText(const string& text, SDL_Color textColor, SDL_Renderer* renderer, const SDL_Rect& buttonRect);
};

#endif 
