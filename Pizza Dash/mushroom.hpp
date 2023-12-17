#ifndef MUSHROOM_HPP
#define MUSHROOM_HPP

#include "ingredient.hpp"  // Include the base class header file

class Mushroom : public Ingredient {
public:
    Mushroom(SDL_Renderer* renderer, int xPos);
    virtual ~Mushroom();  // Virtual destructor

    void move() override;
    std::string get_name() override;

private:
    static const int ING_SPEED = 4;
    std::string name = "Mushroom";
};

#endif // MUSHROOM_HPP
