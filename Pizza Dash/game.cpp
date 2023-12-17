#include <algorithm>
#include <string>

#include "Game.hpp"

Game::Game() : window(nullptr), renderer(nullptr), player(renderer), startGame(false), quit(false),
               lastSpawnTime(SDL_GetTicks()), obstacleSpawnInterval(2000),
               lastINGSpawnTime(SDL_GetTicks()), INGSpawnInterval(1000), currentPizza("") {
    if (!initSDL(window, renderer)) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        quit = true;
    }
}

Game::~Game() {
    // Free resources
    closeSDL(window, renderer);

    // Free obstacle objects
    for (auto obstacle : obstacles) {
        delete obstacle;
    }

    // Free ingredient objects
    for (auto ingredient : ingredients) {
        delete ingredient;
    }

    // Free order objects
    for (auto order : pizza_orders) {
        delete order;
    }
}

void Game::run() {
    while (!quit) {
        // Handle events
        handleEvents();

        // Move entities
        moveEntities();

        // Render
        render();

        // Check for game over
        checkGameOver();
    }
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }

        // Handle player events
        player.handleEvent(e);
    }
}

void Game::moveEntities() {
    // Move the player
    player.move();

    // Spawn obstacles
    spawnObstacles();

    // Move and render obstacles
    for (auto it = obstacles.begin(); it != obstacles.end();) {
        (*it)->move();
        ++it;
    }

    // Spawn ING
    spawnIngredients();

    // Move and render ingredients
    for (auto it = ingredients.begin(); it != ingredients.end();) {
        (*it)->move();
        ++it;
    }

    // Handle collisions
    checkCollisions();
}

void Game::spawnObstacles() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastSpawnTime >= obstacleSpawnInterval) {
        // Randomly choose between spawning a car or an Animal......
        if (rand() % 2 == 0) {
            obstacles.push_back(new Car(renderer, rand() % (SCREEN_WIDTH - OBSTACLE_WIDTH), &player));
        } else {
            obstacles.push_back(new Animal(renderer, rand() % (SCREEN_WIDTH - OBSTACLE_WIDTH)));
        }

        lastSpawnTime = currentTime;
    }
}

void Game::spawnIngredients() {
    Uint32 currentINGTime = SDL_GetTicks();
    if (currentINGTime - lastINGSpawnTime >= INGSpawnInterval) {
        // Randomly choose between Ingredients......
        // Adjust probabilities as needed
        int randomIngredient = rand() % 7;
        if (randomIngredient == 0) {
            ingredients.push_back(new Sauce(renderer, rand() % (SCREEN_WIDTH - ING_WIDTH)));
        } else if (randomIngredient == 1) {
            ingredients.push_back(new Olive(renderer, rand() % (SCREEN_WIDTH - ING_WIDTH)));
        } else if (randomIngredient == 2) {
            ingredients.push_back(new Cheese(renderer, rand() % (SCREEN_WIDTH - ING_WIDTH)));
        } else if (randomIngredient == 3) {
            ingredients.push_back(new Capsicum(renderer, rand() % (SCREEN_WIDTH - ING_WIDTH)));
        } else if (randomIngredient == 4) {
            ingredients.push_back(new Mushroom(renderer, rand() % (SCREEN_WIDTH - ING_WIDTH)));
        } else if (randomIngredient == 5) {
            ingredients.push_back(new Flour(renderer, rand() % (SCREEN_WIDTH - ING_WIDTH)));
        } else if (randomIngredient == 6) {
            ingredients.push_back(new Chicken(renderer, rand() % (SCREEN_WIDTH - ING_WIDTH)));
        }

        lastINGSpawnTime = currentINGTime;
    }
}

void Game::render() {
    // Clear screen.....
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    SDL_RenderClear(renderer);

    // Render the player.....
    player.render(renderer);

    // Render obstacles.....
    for (const auto& obstacle : obstacles) {
        obstacle->render(renderer);
    }

    // render ingredients
    for (const auto& ingredient : ingredients) {
        ingredient->render(renderer);
    }

    // Update the screen.....
    SDL_RenderPresent(renderer);
}

void Game::checkCollisions() {
    // TODO: Implement collision handling logic
}

void Game::checkGameOver() {
    if (player.getLives() <= 0 || player.getCurrentCapacity() <= 0) {
        std::cout << "Game Over!" << std::endl;

        // Show the game over screen only once
        GameOverScreen gameOverScreen(renderer);

        // Render the game over screen
        gameOverScreen.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Event gameOverEvent;
        bool gameOverHandled = false;
        while (!gameOverHandled) {
            while (SDL_PollEvent(&gameOverEvent) != 0) {
                if (gameOverScreen.handleRetryButtonEvent(gameOverEvent)) {
                    // Retry button clicked, restart the game
                    player.reset();  // Implement a reset method in your Player class
                    obstacles.clear();
                    ingredients.clear();
                    pizza_orders.clear();

                    startGame = true;
                    gameOverHandled = true;
                } else if (gameOverScreen.handleCloseButtonEvent(gameOverEvent)) {
                    // Close button clicked, end the game
                    startGame = false;
                    gameOverHandled = true;
                    quit = true;
                }
            }
        }
    }
}

bool Game::initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    // Create a window
    window = SDL_CreateWindow("SDL Starting Screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        return false;
    }

    return true;
}


void Game::closeSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    // Quit SDL_image
    IMG_Quit();

    // Destroy the renderer
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    // Destroy the window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL
    SDL_Quit();
}

bool Game::areVectorsEqual(const vector<std::string>& vec1, const vector<string>& vec2) {
    // Make copies of the vectors to avoid modifying the original vectors
    vector<string> sortedVec1 = vec1;
    vector<string> sortedVec2 = vec2;

    // Sort both vectors
    sort(sortedVec1.begin(), sortedVec1.end());
    sort(sortedVec2.begin(), sortedVec2.end());

    // Compare the sorted vectors element-wise
    return sortedVec1 == sortedVec2;
}
