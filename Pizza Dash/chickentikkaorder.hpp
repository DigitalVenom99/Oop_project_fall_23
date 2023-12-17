#ifndef CHICKENTIKKAORDER_HPP
#define CHICKENTIKKAORDER_HPP

#include "order.hpp"

class ChickenTikkaOrder : public Order {
public:
    ChickenTikkaOrder(SDL_Renderer* renderer, int screenWidth);
    ~ChickenTikkaOrder();

    ChickenTikkaOrder& operator+=(int increment);

    bool isOrderCompleted() const;

    void deleteSauceTexture();
    void deleteFlourTexture();
    void deleteChickenTexture();
    void deleteCapsicumTexture();
    void deleteCheeseTexture();

    int getCTing_num();
    void reset();

    void render() const override;

private:
    SDL_Texture* cheeseTexture;
    SDL_Texture* flourTexture;
    SDL_Texture* sauceTexture;
    SDL_Texture* chickenTexture;
    SDL_Texture* orderboxTexture;
    SDL_Texture* capsicumTexture;
    int ingredientsCollected;
    const int totalIngredients = 5;
    bool SauceO;
    bool CheeseO;
    bool FlourO;
    bool ChickenO;
    bool CapsicumO;
};

#endif // CHICKENTIKKAORDER_HPP
