#include "gameoverscreen.hpp"
#include <string>
using namespace std;

GameOverScreen::GameOverScreen(SDL_Renderer* renderer) : renderer(renderer) {
    // Load start screen texture and initialize any other necessary resources
    gameOverTexture = loadTexture("Gameover.jpeg", renderer);

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not be initialized! SDL_ttf Error: " << TTF_GetError() << std::endl;
        // Handle the initialization error as needed
    }

    // Load font for the buttons
    font = TTF_OpenFont("font.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }

    int centerX = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;

    // Set button positions
    retryButtonRect = {centerX, 600, BUTTON_WIDTH, BUTTON_HEIGHT};
    closeButtonRect = {centerX, 700, BUTTON_WIDTH, BUTTON_HEIGHT};

    showRetryButton = true;
    showCloseButton = true;
}

GameOverScreen::~GameOverScreen() {
    // Free resources
    SDL_DestroyTexture(gameOverTexture);
    TTF_CloseFont(font);
    TTF_Quit();
}

// SDL_Texture* GameOverScreen::(const string& path, SDL_Renderer* renderer) {
//     SDL_Texture* texture = nullptr;

//     // Load image at specified path
//     SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//     if (loadedSurface == nullptr) {
//         cerr << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
//         return nullptr;
//     }

//     // Create texture from surface pixels
//     texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
//     if (texture == nullptr) {
//         cerr << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << endl;
//     }

//     // Get rid of the loaded surface
//     SDL_FreeSurface(loadedSurface);

//     return texture;
// }

void GameOverScreen::render(SDL_Renderer* renderer) {
    // Render the start screen texture and any other elements
    SDL_RenderCopy(renderer, gameOverTexture, nullptr, nullptr);

    // Render the Retry button
    if (showRetryButton) {
        SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); // Grey color
        SDL_RenderFillRect(renderer, &retryButtonRect);

        // Render Retry button text
        renderText("Restart", textColor, renderer, retryButtonRect);
    }

    // Render the Close button
    if (showCloseButton) {
        SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); // Grey color
        SDL_RenderFillRect(renderer, &closeButtonRect);

        // Render Close button text
        renderText("Close", textColor, renderer, closeButtonRect);
    }
}

bool GameOverScreen::handleRetryButtonEvent(SDL_Event& e) {
    return handleButtonClickEvent(e, retryButtonRect);
}

bool GameOverScreen::handleCloseButtonEvent(SDL_Event& e) {
    return handleButtonClickEvent(e, closeButtonRect);
}

void GameOverScreen::renderText(const std::string& text, SDL_Color textColor, SDL_Renderer* renderer, const SDL_Rect& buttonRect) {
    // Create a surface with the rendered text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Failed to render text! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Create a texture from the surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    // Get the dimensions of the text
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Clean up the surface, as it's no longer needed
    SDL_FreeSurface(textSurface);

    // Set the rendering position for the text to center it in the button
    int buttonCenterX = buttonRect.x + buttonRect.w / 2 - textWidth / 2;
    int buttonCenterY = buttonRect.y + buttonRect.h / 2 - textHeight / 2;

    // Render the text to the screen
    SDL_Rect renderRect = {buttonCenterX, buttonCenterY, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderRect);

    // Clean up the texture
    SDL_DestroyTexture(textTexture);
}

bool GameOverScreen::handleButtonClickEvent(SDL_Event& e, const SDL_Rect& buttonRect) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Check if the mouse click is within the button
        if (isPointInsideRect(mouseX, mouseY, buttonRect)) {
            return true; // Button clicked
        }
    }
    return false;
}

bool GameOverScreen::isPointInsideRect(int x, int y, const SDL_Rect& rect) {
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

SDL_Texture* GameOverScreen::loadTexture(const std::string& path, SDL_Renderer* renderer) {
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
