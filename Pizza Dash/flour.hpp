#ifndef FLOUR_HPP
#define FLOUR_HPP

#include "ingredient.hpp"  // Include the base class header file

class Flour : public Ingredient {
public:
    Flour(SDL_Renderer* renderer, int xPos);
    virtual ~Flour();  // Virtual destructor

    void move() override;
    std::string get_name() override;

private:
    static const int ING_SPEED = 4;
    std::string name = "Flour";
};

#endif // FLOUR_HPP
