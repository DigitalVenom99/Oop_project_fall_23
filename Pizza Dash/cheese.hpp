#ifndef CHEESE_HPP
#define CHEESE_HPP

#include "ingredient.hpp"  // Include the base class header file

class Cheese : public Ingredient {
public:
    Cheese(SDL_Renderer* renderer, int xPos);
    virtual ~Cheese();  // Virtual destructor

    void move() override;
    std::string get_name() override;

private:
    static const int ING_SPEED = 4;
    std::string name = "Cheese";
};

#endif // CHEESE_HPP
