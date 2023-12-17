#include <vector>
#include "SDL.h"
#include "vector"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iterator>
#include <string>
#include <ctime>
#include <SDL2/SDL_mixer.h>

using namespace std;
#include <algorithm>

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
// #include "Game.hpp"


using namespace std;




//Player Order Completion Check Vector
vector <string> Player_Order_Completion_Check_Vector;
// Chicken Tikka Order Ing 
vector <string> CTPING = {"Sauce", "Cheese", "Flour","Chicken","Capsicum"};

string currentPizza;


// Function to load a texture from an image file
SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer) {
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


bool areVectorsEqual(const vector<std::string>& vec1, const vector<string>& vec2) {
    // Make copies of the vectors to avoid modifying the original vectors
    vector<string> sortedVec1 = vec1;
    vector<string> sortedVec2 = vec2;

    // Sort both vectors
    sort(sortedVec1.begin(), sortedVec1.end());
    sort(sortedVec2.begin(), sortedVec2.end());

    // Compare the sorted vectors element-wise
    return sortedVec1 == sortedVec2;
}




// Function to initialize SDL and create a window
bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
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

// Function to close SDL and deallocate resources
void closeSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
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





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








class CheesePizzaOrder : public Order {


public:

    CheesePizzaOrder(SDL_Renderer* renderer, int screenWidth)
        : Order(renderer, screenWidth) {
        // Load ingredient textures
        loadTexture("orderbox.png",orderboxTexture);
        loadTexture("Cheese.png", cheeseTexture);
        loadTexture("Flour.png", flourTexture);
        loadTexture("Sauce.png", sauceTexture);
            }

    ~CheesePizzaOrder() {
        // Free loaded textures
        SDL_DestroyTexture(orderboxTexture);
        SDL_DestroyTexture(cheeseTexture);
        SDL_DestroyTexture(flourTexture);
        SDL_DestroyTexture(sauceTexture);




    }   

    
    // Overload the += operator to increment the count of collected ingredients
    CheesePizzaOrder& operator+=(int increment) {
        ingredientsCollected += increment;
        return *this;
    }

    // Method to check if the order is completed
    bool isOrderCompleted() const {
        return ingredientsCollected == totalIngredients;
    }


    void deleteSauceTexture() {
        SauceO = false;
    }

    void deleteFlourTexture() {
        FlourO = false;
    }


    void deleteCheeseTexture() {
        CheeseO = false;
    }

    void reset()
    {
        SauceO = true;
        CheeseO = true;
        FlourO = true;
    }
    
    void render() const override {
        int ORDER_BOX_WIDTH = 500;
        int ORDER_BOX_HEIGHT= 300;


        const int ING_WIDTH = 30;
        const int ING_HEIGHT = 30;  

        // Render the larger order box at the top-middle of the screen
        int orderBoxX = screenWidth / 2 - ORDER_BOX_WIDTH / 2;
        renderTexture(orderboxTexture, orderBoxX, -85, ORDER_BOX_WIDTH, ORDER_BOX_HEIGHT);
        
        if (FlourO == true)
        {
            renderTexture(flourTexture, orderBoxX +  200, ORDER_BOX_HEIGHT / 4 - ING_HEIGHT / 2, ING_WIDTH, ING_HEIGHT);
        }

        if (SauceO == true)
        {
            renderTexture(sauceTexture, orderBoxX + 250, ORDER_BOX_HEIGHT / 4 - ING_HEIGHT / 2, ING_WIDTH, ING_HEIGHT);
        }

        if (CheeseO == true)
        {
            renderTexture(cheeseTexture, orderBoxX + 150, ORDER_BOX_HEIGHT / 4 - ING_HEIGHT / 2, ING_WIDTH, ING_HEIGHT);
        }

        // Render ingredients inside the order box
        
        
        
    
        
    }
    

private:
    SDL_Texture* cheeseTexture;
    SDL_Texture* flourTexture;
    SDL_Texture* sauceTexture;
    SDL_Texture* orderboxTexture;

    int ingredientsCollected;
    const int totalIngredients = 5;
    bool SauceO = true;
    bool CheeseO =true;
    bool FlourO =true;

};                                                                                                                                      








////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////


// void playSoundEffect(Mix_Chunk* soundEffect) {
//     Mix_PlayChannel(-1, soundEffect, 0);
// }
 Mix_Music* backgroundMusic = nullptr;
 Mix_Music* IngMusic = nullptr;
 Mix_Music* obstacleMusic = nullptr;
    
/// @brief 
/// @param argc 
/// @param args 
/// @return 
int main(int argc, char* args[]) {
    // Initialize SDL
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
   


    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }

    // Load background music
    backgroundMusic = Mix_LoadMUS("background.wav");
    if (backgroundMusic == nullptr) {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }
    obstacleMusic = Mix_LoadMUS("obstacle_crash_sound.wav");
    if (backgroundMusic == nullptr) {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }
    IngMusic = Mix_LoadMUS("Ing_sound.wav");
    if (backgroundMusic == nullptr) {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }

    // Play background music
    Mix_PlayMusic(backgroundMusic, -1);
    // // Play the background music
    // Mix_PlayMusic(backgroundMusic, -1);



    // // Initialize SDL_mixer
    // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    //     cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
    //     return -1;
    // }

    // // Load the WAV file
    // Mix_Chunk* collisionSound = Mix_LoadWAV("obstacle_crash_sound.wav");
    // if (collisionSound == nullptr) {
    //     cout << "Failed to load collision sound! SDL_mixer Error: " << Mix_GetError() << endl;
    //     return -1;
    // }

    
   



    if (!initSDL(window, renderer)) {
        cerr << "Failed to initialize SDL!" << endl;
        return -1;
    }

    // Load background image
    SDL_Texture* backgroundTexture = loadTexture("BackGround.png", renderer);
    if (backgroundTexture == nullptr) {
        cerr << "Failed to load background texture!" << endl;
        closeSDL(window, renderer);
        return -1;
    }

    // Create a player object
    Player player(renderer);




        


    // Vector to store obstacles that will be spawning in the game.......
    vector <Obstacle*> obstacles;



    // Vector to store ing that will be spawning....
    vector <Ingredient*> ingredients;


    // 
    vector <Order*> pizza_orders;

    

    

    bool quit = false;
    SDL_Event e;

    // Time variables for obstacle spawning.....time controlling (Have to check in the end according to the game difficulty).....imp*******
    Uint32 lastSpawnTime = SDL_GetTicks();
    const Uint32 obstacleSpawnInterval = 2000; // in milliseconds


    Uint32 lastINGSpawnTime = SDL_GetTicks();
    const Uint32 INGSpawnInterval = 1000; // in milliseconds



                    // Main loop

                    bool startGame = false;
                    bool playAgain = false;

                    StartScreen startScreen(renderer);
                    

                    // When you want to transition from the start screen to the game loop:
                    startScreen.render(renderer);
                    SDL_RenderPresent(renderer);

                    SDL_Event startEvent;
                    while (!startGame) {
                        while (SDL_PollEvent(&startEvent) != 0) {
                            if (startScreen.handleStartButtonEvent(startEvent)) {
                                cout<<"Start Button Clicked"<<endl;
                                startGame = true;
                            }
                            else if  (startScreen.handleCloseButtonEvent(startEvent)) {
                                // startGame = false;
                                cout<<"Close Button Clicked"<<endl;
                                // closeSDL(window, renderer);
                                // SDL_Quit();
                                startGame = true;
                                quit = true;
                            }
                            else if (startScreen.handleRulesButtonEvent(startEvent)){
                                cout<<"Rules Button Clicked"<<endl;

                                SDL_SetRenderDrawColor(renderer, 0,0,0,0); // White
                                SDL_RenderClear(renderer);


                                bool ruleEvent = false;
                                Rule ruleScreen(renderer);
                    

                                // When you want to transition from the start screen to the rules screen:
                                ruleScreen.render(renderer);
                                SDL_RenderPresent(renderer);
                                

                                SDL_Event startEvent;
                                while (!ruleEvent) {
                                    while (SDL_PollEvent(&startEvent) != 0) {
                                        if (ruleScreen.handleBackButtonEvent(startEvent)) {
                                            
                                            cout<<"Back Button Clicked"<<endl;
                                            


                                        
                                        }
                                        
                                    }
                                }













                            ///////    
                            }
                        }
                    }

                

                    // Create random orders on the screen.....
                    // Create a ChickenTikka order
                    ChickenTikkaOrder chickenTikkaOrder(renderer, SCREEN_WIDTH);
                    currentPizza = "ChickenTikka";
                    


                    //////////////////////////////////////

                    //////////////////////////////////////////////










                        while (!quit) {
                                // Handle events on the queue
                                while (SDL_PollEvent(&e) != 0) {
                                    // User requests quit
                                    if (e.type == SDL_QUIT) {
                                        quit = true;
                                    }

                                    // Handle player events
                                    player.handleEvent(e);
                                }

                                // Move the player
                                player.move();


                               ////////////////////////////////

                                // int randomNum = rand() % 2;

                                //     if (randomNum == 0) {
                                //         currentPizza = "ChickenTikka";
                                //         pizza_order.push_back(new ChickenTikkaOrder(renderer, SCREEN_WIDTH));
                                //     } else {
                                //         currentPizza = "CheesePizza";
                                //         pizza_order.push_back(new CheesePizzaOrder(renderer, SCREEN_WIDTH));
                                //     }



                               ///////////////////////////// 
                                

                                // Spawn obstacles
                                Uint32 currentTime = SDL_GetTicks();
                                if (currentTime - lastSpawnTime >= obstacleSpawnInterval) {
                                    // Randomly choose between spawning a car or an Animal......
                                    if (rand() % 2 == 0) {
                                        obstacles.push_back(new Car(renderer, rand() % (SCREEN_WIDTH - OBSTACLE_WIDTH),&player));
                                    } else {
                                        obstacles.push_back(new Animal(renderer, rand() % (SCREEN_WIDTH - OBSTACLE_WIDTH)));
                                    }

                                    lastSpawnTime = currentTime;
                                }

                                // Move and render obstacles
                                for (auto it = obstacles.begin(); it != obstacles.end();) {
                                    (*it)->move();

                                    // collision check start
                                    SDL_Rect playerCollisionBox = player.getCollisionBox();
                                    SDL_Rect obstacleCollisionBox = (*it)->getCollisionBox();

                                    if (SDL_HasIntersection(&playerCollisionBox, &obstacleCollisionBox)) {
                                        cout << "Collision with obstacle!" << endl;

                                        // collision check end.....

                                        Mix_PlayMusic(obstacleMusic, -1);

                                        // decreasing life after collisions......
                                        player.decrementLives();

                                        // remove obstacle after collision....
                                        delete *it;
                                        it = obstacles.erase(it);
                                        continue;
                                    }

                                    ++it;
                                }

                                // Spawn ING
                                Uint32 currentingTime = SDL_GetTicks();
                                if (currentingTime - lastINGSpawnTime >= INGSpawnInterval) {
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

                                    lastINGSpawnTime = currentTime;
                                }
                        
                                // Move and render ingredients
                                for (auto it = ingredients.begin(); it != ingredients.end();) {
                                    (*it)->move();

                                    // Collision check start
                                    SDL_Rect playerCollisionBox = player.getCollisionBox();
                                    SDL_Rect ingCollisionBox = (*it)->getCollisionBox();

                                    if (SDL_HasIntersection(&playerCollisionBox, &ingCollisionBox)) {
                                        // Print the name of the ingredient
                                        string current_collected_ing;
                                        current_collected_ing =  (*it)->get_name();
                                        cout << "Ingredient collected: " << (*it)->get_name() << endl;

                                        Mix_PlayMusic(IngMusic, -1);

                                        // HANDLE ALL COLLISION WITH ING AND WITH A SPECIFIC ORDER.....

                                    
                                        if (current_collected_ing == "Sauce" && currentPizza == "ChickenTikka") {
                                            cout<<"Delete Sauce----"<<endl;
                                            if (find(Player_Order_Completion_Check_Vector.begin(), Player_Order_Completion_Check_Vector.end(), current_collected_ing) == Player_Order_Completion_Check_Vector.end()) 
                                            {
                                                Player_Order_Completion_Check_Vector.push_back(current_collected_ing);
                                                cout << "Pushed Back" << endl;
                                            }
                                             chickenTikkaOrder.deleteSauceTexture();
                                        }
                                        else if (current_collected_ing == "Flour" && currentPizza == "ChickenTikka") {
                                            cout<<"Delete Flour----"<<endl;
                                            if (find(Player_Order_Completion_Check_Vector.begin(), Player_Order_Completion_Check_Vector.end(), current_collected_ing) == Player_Order_Completion_Check_Vector.end()) 
                                            {
                                                Player_Order_Completion_Check_Vector.push_back(current_collected_ing);
                                                cout << "Pushed Back" << endl;
                                            }
                                             chickenTikkaOrder.deleteFlourTexture();
                                        }
                                        else if (current_collected_ing == "Chicken" && currentPizza == "ChickenTikka") {
                                            cout<<"Delete Chicken----"<<endl;
                                            if (find(Player_Order_Completion_Check_Vector.begin(), Player_Order_Completion_Check_Vector.end(), current_collected_ing) == Player_Order_Completion_Check_Vector.end()) 
                                            {
                                                Player_Order_Completion_Check_Vector.push_back(current_collected_ing);
                                                cout << "Pushed Back" << endl;
                                            }
                                             chickenTikkaOrder.deleteChickenTexture();
                                        }
                                        else if (current_collected_ing == "Capsicum" && currentPizza == "ChickenTikka") {
                                            cout<<"Delete Capsicum----"<<endl;
                                            if (find(Player_Order_Completion_Check_Vector.begin(), Player_Order_Completion_Check_Vector.end(), current_collected_ing) == Player_Order_Completion_Check_Vector.end()) 
                                            {
                                                Player_Order_Completion_Check_Vector.push_back(current_collected_ing);
                                                cout << "Pushed Back" << endl;
                                            }
                                             chickenTikkaOrder.deleteCapsicumTexture();
                                        }
                                        else if (current_collected_ing == "Cheese" && currentPizza == "ChickenTikka") {
                                            cout<<"Delete Cheese----"<<endl;
                                            if (find(Player_Order_Completion_Check_Vector.begin(), Player_Order_Completion_Check_Vector.end(), current_collected_ing) == Player_Order_Completion_Check_Vector.end()) 
                                            {
                                                Player_Order_Completion_Check_Vector.push_back(current_collected_ing);
                                                cout << "Pushed Back" << endl;
                                            }
                                            chickenTikkaOrder.deleteCheeseTexture();
                                        }


                                        //////////////////////////////////////


                                        // if (current_collected_ing == "Sauce" && currentPizza == "CheesePizza") {
                                        //     cout<<"Delete Sauce----"<<endl;
                                        //     if (find(Player_Order_Completion_Check_Vector.begin(), Player_Order_Completion_Check_Vector.end(), current_collected_ing) == Player_Order_Completion_Check_Vector.end()) 
                                        //     {
                                        //         Player_Order_Completion_Check_Vector.push_back(current_collected_ing);
                                        //         cout << "Pushed Back" << endl;
                                        //     }
                                        //      cheesePizzaOrder.deleteSauceTexture();
                                        // }
                                        // else if (current_collected_ing == "Flour" && currentPizza == "CheesePizza") {
                                        //     cout<<"Delete Flour----"<<endl;
                                        //     if (find(Player_Order_Completion_Check_Vector.begin(), Player_Order_Completion_Check_Vector.end(), current_collected_ing) == Player_Order_Completion_Check_Vector.end()) 
                                        //     {
                                        //         Player_Order_Completion_Check_Vector.push_back(current_collected_ing);
                                        //         cout << "Pushed Back" << endl;
                                        //     }
                                        //      cheesePizzaOrder.deleteFlourTexture();
                                        // }
                                        // else if (current_collected_ing == "Cheese" && currentPizza == "CheesePizza") {
                                        //     cout<<"Delete Cheese----"<<endl;
                                        //     if (find(Player_Order_Completion_Check_Vector.begin(), Player_Order_Completion_Check_Vector.end(), current_collected_ing) == Player_Order_Completion_Check_Vector.end()) 
                                        //     {
                                        //         Player_Order_Completion_Check_Vector.push_back(current_collected_ing);
                                        //         cout << "Pushed Back" << endl;
                                        //     }
                                        //     cheesePizzaOrder.deleteCheeseTexture();
                                        // }



                                        //////////////////////////////////////
                                        

                                        for (const auto& element : Player_Order_Completion_Check_Vector) {
                                            cout << element << " "<<endl;
                                        }
                                        if  (areVectorsEqual(Player_Order_Completion_Check_Vector,CTPING)){
                                            player.increase_Cap_flag_true(),
                                            cout<< currentPizza <<" --->  Order Completed"<<endl;
                                            
                                            player.increase_capacity(chickenTikkaOrder.getCTing_num());
                                            player.increase_Cap_flag_false();
                                            
                                            
                                        }
                                        
                                        // collision check end...

                                        // Decrease capacity
                                        player.decrementCapacity();

                                        cout << "Current Capacity Remaining = " << player.getCurrentCapacity() << endl;

                                        // Use operator overloading to increment the count of collected ingredients
                                        chickenTikkaOrder += 1;

                                        // Check if the order is completed
                                        if (chickenTikkaOrder.isOrderCompleted()) {
                                            cout << "Order Completed!" << endl;
                                            // Handle completion logic here, such as awarding points or advancing to the next level.
                                        }

                                        // Debugging output
                                        cout << "Before Erase - Ingredients Size: " << ingredients.size() << endl;

                                        // Remove ingredient after collection
                                        delete *it;
                                        it = ingredients.erase(it);

                                        // Debugging output
                                        cout << "After Erase - Ingredients Size: " << ingredients.size() << endl;

                                        continue;
                                    }

                                    ++it;
                                    

                                }




                            //////////////////////////////
                                // Clear screen.....
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
                                SDL_RenderClear(renderer);

                                // Render the background.....
                                SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

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

                                // Render lives
                                if (player.getLives() > 0) {
                                    player.getLivesObject()->render(renderer);
                                }


                                chickenTikkaOrder.render();


                                // Update the screen.....
                                SDL_RenderPresent(renderer);

                                // Check for game over......
                                if (player.getLives() <= 0 or player.getCurrentCapacity() <= 0) {
                                    cout << "Game Over!" << endl;

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
                                                chickenTikkaOrder.reset();
                                                Player_Order_Completion_Check_Vector.clear();

                                                quit = false;
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

                            // Free resources and close SDL
                            SDL_DestroyTexture(backgroundTexture);

                            // Free obstacle objects
                            for (auto obstacle : obstacles) {
                                delete obstacle;
                            }
                            
                            // for (auto order : pizza_order) {
                            //     delete order;
                            // }


                            // Free ingredient objects
                            for (auto ingredient : ingredients) {
                                delete ingredient;
                            }

                            // Check for game over......
                            if (player.getLives() <= 0 or player.getCurrentCapacity() <= 0) {
                                cout << "Game Over!" << endl;
                            }

                            closeSDL(window, renderer);

                            return 0;
                        }





// int main(int argc, char* args[]) {
//     // Seed for random number generation
//     srand(static_cast<unsigned>(time(nullptr)));

//     // Create an instance of the Game class
//     Game game;

//     // Run the game loop
//     game.run();

//     return 0;
// }
