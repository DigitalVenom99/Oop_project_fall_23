// startscreen.hpp
#ifndef STARTSCREEN_HPP
#define STARTSCREEN_HPP
#include "rule.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "rule.hpp"  // Include the header file for the Rule class

using namespace std;

class StartScreen {
public:
    StartScreen(SDL_Renderer* renderer);
    ~StartScreen();
    bool isPointInsideRect(int x, int y, const SDL_Rect& rect);
    SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer);
    void renderText(const std::string& text, SDL_Color textColor, SDL_Renderer* renderer, const SDL_Rect& buttonRect);
    bool handleButtonClickEvent(SDL_Event& e, const SDL_Rect& buttonRect);
    void render(SDL_Renderer* renderer);
    bool handleStartButtonEvent(SDL_Event& e);
    bool handleRulesButtonEvent(SDL_Event& e);
    bool handleCloseButtonEvent(SDL_Event& e);

private:
    SDL_Texture* startTexture = nullptr;
    TTF_Font* font = nullptr;
    SDL_Rect startButtonRect;
    SDL_Rect rulesButtonRect;
    SDL_Rect closeButtonRect;
    bool showStartButton;
    bool showRulesButton;
    bool showCloseButton;
    bool startGame = false;
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    Rule* ruleWindow = nullptr; // Rule window instance

    
    const int SCREEN_WIDTH = 880;
    const int SCREEN_HEIGHT = 800;

};

#endif
