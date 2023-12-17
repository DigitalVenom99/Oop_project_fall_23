// sauce.hpp

#ifndef SAUCE_HPP
#define SAUCE_HPP

#include "ingredient.hpp"

class Sauce : public Ingredient {
public:
    Sauce(SDL_Renderer* renderer, int xPos);
    void move() override;
    std::string get_name() override;

private:
    static const int ING_SPEED = 4;
    std::string name = "Sauce";
};

#endif
