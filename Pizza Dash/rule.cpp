#include "rule.hpp"
// #include <iostream>
// #include <vector>

// Rule.cpp

#include "rule.hpp"
#include <SDL_image.h>

// Include necessary headers and define SCREEN_WIDTH, BUTTON_WIDTH, and BUTTON_HEIGHT if not already defined

Rule::Rule(SDL_Renderer* renderer) {
    // Load rule window texture and initialize any other necessary resources
    ruleTexture = loadTexture("rule.png", renderer);

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        cerr << "SDL_ttf could not be initialized! SDL_ttf Error: " << TTF_GetError() << endl;
        // Handle the initialization error as needed
    }

    // Load font for the buttons
    font = TTF_OpenFont("font.ttf", 24);
    if (!font) {
        cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
    }

    // Calculate the centered X-coordinate for the back button
    int centerX = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;

    // Set the position for the back button
    backButtonRect = {centerX, 675, BUTTON_WIDTH, BUTTON_HEIGHT}; // Adjust the Y-coordinate as needed
}

Rule::~Rule() {
    SDL_DestroyTexture(ruleTexture);
    // Clean up any other resources
}

void Rule::render(SDL_Renderer* renderer) {
    // Render the rule window texture and any other elements
    SDL_RenderCopy(renderer, ruleTexture, nullptr, nullptr);

    // Render the Back button
    SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); // Grey color
    SDL_RenderFillRect(renderer, &backButtonRect);

    // Render Back button text
    renderText("Back", textColor, renderer, backButtonRect);
}

bool Rule::handleBackButtonEvent(SDL_Event& e) {
    return handleButtonClickEvent(e, backButtonRect);
}

bool Rule::handleButtonClickEvent(SDL_Event& e, const SDL_Rect& buttonRect) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Check if the mouse click is within the button
        if (isPointInsideRect(mouseX, mouseY, buttonRect)) {
            return true; // Button clicked
        }
    }

    return false; // Button not clicked
}

SDL_Texture* Rule::loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* texture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cerr << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
        return nullptr;
    }

    // Create texture from surface pixels
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == nullptr) {
        cerr << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << endl;
    }

    // Get rid of the loaded surface
    SDL_FreeSurface(loadedSurface);

    return texture;
}

void Rule::renderText(const std::string& text, SDL_Color textColor, SDL_Renderer* renderer, const SDL_Rect& buttonRect) {
    // Render text implementation...
}

bool Rule::isPointInsideRect(int x, int y, const SDL_Rect& rect) {
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

















