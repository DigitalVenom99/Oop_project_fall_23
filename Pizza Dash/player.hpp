#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "lives.hpp"  // Include the Lives class header
#include "capacity.hpp"  // Include the Capacity class header
#include "capacity_visual.hpp"  // Include the CapacityVisual class header

class Player {
public:
    // Constructor
    Player(SDL_Renderer* renderer);

    // Destructor
    ~Player();

    Lives* getLivesObject() const;

    void increase_capacity(int x);
    void increase_Cap_flag_false();
    void increase_Cap_flag_true();

    void render(SDL_Renderer* renderer);

    void handleEvent(SDL_Event& e);

    int getX() const;
    int getY() const;

    void move();

    void decrementLives();

    void decrementCapacity();

    int getCurrentCapacity() const;

    int getTotalCapacity() const;

    int getLives() const;

    void reset();

    SDL_Rect getCollisionBox() const;

private:
    SDL_Texture* playerTexture = nullptr;
    int capacity_num = 10;
    int x, y;
    int lives;
    int velX = 0;
    static const int PLAYER_SPEED = 10;
    Lives* livesObject;
    Capacity* capacityObject;
    CapacityVisual* capacityVisual;
    bool increase_Cap_flag;
    SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer) ;

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
};

#endif // PLAYER_HPP
