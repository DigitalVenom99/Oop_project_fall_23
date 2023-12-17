#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "SDL.h"
#include "vector"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iterator>
#include <string>
#include <ctime>
using namespace std;

#include "rule.hpp"
#include "startscreen.hpp"
#include "capacity.hpp"
#include "capacity_visual.hpp"
#include "lives.hpp"
#include "ingredient.hpp"
#include "sauce.hpp"
#include "olive.hpp"
#include "cheese.hpp"
#include "mushroom.hpp"
#include "capsicum.hpp"
#include "flour.hpp"
#include "chicken.hpp"
#include "player.hpp"
#include "obstacle.hpp"
#include "car.hpp"
#include "animal.hpp"
#include "order.hpp"
#include "chickentikkaorder.hpp"
#include "gameoverscreen.hpp"

// #include "player.hpp"  // Include your Player class header file
// #include "obstacle.hpp"  // Include your Obstacle class header file
// #include "ingredient.hpp"  // Include your Ingredient class header file
// // #include "Order.hpp"  // Include your Order class header file
// #include "startscreen.hpp"  // Include your StartScreen class header file
// #include "rule.hpp"  // Include your Rule class header file
// #include "gameoverscreen.hpp"  // Include your GameOverScreen class header file

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Player player;

    vector<Obstacle*> obstacles;
    vector<Ingredient*> ingredients;
    vector<Order*> pizza_orders;

    bool startGame;
    bool quit;

    Uint32 lastSpawnTime;
    const Uint32 obstacleSpawnInterval;
    Uint32 lastINGSpawnTime;
    const Uint32 INGSpawnInterval;

    string currentPizza;
    bool areVectorsEqual(const vector<string>& vec1, const vector<string>& vec2);
    bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
    void closeSDL(SDL_Window*& window, SDL_Renderer*& renderer);
    void handleEvents();
    void moveEntities();
    void spawnObstacles();
    void spawnIngredients();
    void render();
    void checkCollisions();
    void checkGameOver();

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

#endif // GAME_HPP
