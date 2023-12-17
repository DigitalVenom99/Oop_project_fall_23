#include "player.hpp"

// Constructor
Player::Player(SDL_Renderer* renderer) {
    playerTexture = loadTexture("Pizza_man.png", renderer);
    if (playerTexture == nullptr) {
        cerr << "Failed to load player texture!" << endl;
    }

    // Initialize the lives before using it
    lives = 5;
    livesObject = new Lives(renderer, lives);
    capacityObject = new Capacity(capacity_num);
    capacityVisual = new CapacityVisual(renderer);

    x = (SCREEN_WIDTH - PLAYER_WIDTH) / 2;
    y = SCREEN_HEIGHT - PLAYER_HEIGHT;
}

// Destructor
Player::~Player() {
    SDL_DestroyTexture(playerTexture);

    delete livesObject;
    delete capacityObject;
    delete capacityVisual;
}



Lives* Player::getLivesObject() const {
    return livesObject;
}


SDL_Texture* Player::loadTexture(const string& path, SDL_Renderer* renderer) {
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


void Player::increase_capacity(int x) {
    if (increase_Cap_flag == true) {
        capacityObject->increment(x);
    }
}

void Player::increase_Cap_flag_false() {
    increase_Cap_flag = false;
}

void Player::increase_Cap_flag_true() {
    increase_Cap_flag = true;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect playerRect = {x, y, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
    capacityVisual->render(renderer, getCurrentCapacity());

    SDL_Color textColor = {255, 0, 0, 255}; // Red color
    livesObject->render(renderer);
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                velX -= PLAYER_SPEED;
                break;
            case SDLK_RIGHT:
                velX += PLAYER_SPEED;
                break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                velX += PLAYER_SPEED;
                break;
            case SDLK_RIGHT:
                velX -= PLAYER_SPEED;
                break;
        }
    }
}

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

void Player::move() {
    x += velX;
    if (x < 0) {
        x = 0;
    } else if (x > SCREEN_WIDTH - PLAYER_WIDTH) {
        x = SCREEN_WIDTH - PLAYER_WIDTH;
    }
}

void Player::decrementLives() {
    livesObject->decrement();
    lives--;

    // We can add other logic here if needed, such as playing a sound or showing an animation.

    if (lives <= 0) {
        // Game over logic if lives reach 0.
        cout << "Game Over!" << endl;
        // You might want to add additional game over handling here.
    }
    // Additional logic after losing a life can be added here.
}

void Player::decrementCapacity() {
    capacityObject->decrement();
}

int Player::getCurrentCapacity() const {
    return capacityObject->getCurrentCapacity();
}

int Player::getTotalCapacity() const {
    return capacityObject->getTotalCapacity();
}

int Player::getLives() const {
    return lives;
}

void Player::reset() {
    // Set player position to the initial position
    x = (SCREEN_WIDTH - PLAYER_WIDTH) / 2;
    y = SCREEN_HEIGHT - PLAYER_HEIGHT;

    // Reset velocity
    velX = 0;

    // Reset lives
    lives = 5;
    livesObject->reset();  // Assuming you have a reset method in Lives class

    // Reset capacity
    capacityObject->reset();  // Assuming you have a reset method in Capacity class
}

SDL_Rect Player::getCollisionBox() const {
    return {x, y, PLAYER_WIDTH, PLAYER_HEIGHT};
}

