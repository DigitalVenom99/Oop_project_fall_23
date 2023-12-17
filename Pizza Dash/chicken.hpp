#ifndef CHICKEN_HPP
#define CHICKEN_HPP

#include "ingredient.hpp"  // Include the base class header file

class Chicken : public Ingredient {
public:
    Chicken(SDL_Renderer* renderer, int xPos);
    virtual ~Chicken();  // Virtual destructor

    void move() override;
    std::string get_name() override;

private:
    static const int ING_SPEED = 4;
    std::string name = "Chicken";
};

#endif // CHICKEN_HPP
