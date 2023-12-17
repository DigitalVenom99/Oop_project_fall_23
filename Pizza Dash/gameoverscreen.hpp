#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class GameOverScreen {
public:
    GameOverScreen(SDL_Renderer* renderer);
    ~GameOverScreen();

    void render(SDL_Renderer* renderer);
    bool handleRetryButtonEvent(SDL_Event& e);
    bool handleCloseButtonEvent(SDL_Event& e);

private:
    SDL_Renderer* renderer;
    SDL_Texture* gameOverTexture;
    SDL_Rect retryButtonRect;
    SDL_Rect closeButtonRect;
    TTF_Font* font;
    bool showRetryButton;
    bool showCloseButton;
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
    bool isPointInsideRect(int x, int y, const SDL_Rect& rect);
    void renderText(const std::string& text, SDL_Color textColor, SDL_Renderer* renderer, const SDL_Rect& buttonRect);
    bool handleButtonClickEvent(SDL_Event& e, const SDL_Rect& buttonRect);

    // Screen dimensions
    const int SCREEN_WIDTH = 880;
    const int SCREEN_HEIGHT = 800;

    // Button dimensions
    const int BUTTON_WIDTH = 200;
    const int BUTTON_HEIGHT = 50;
};

#endif // GAMEOVERSCREEN_HPP
