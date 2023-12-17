#ifndef OLIVE_HPP
#define OLIVE_HPP

#include "ingredient.hpp"  // Include the base class header file

class Olive : public Ingredient {
public:
    Olive(SDL_Renderer* renderer, int xPos);
    virtual ~Olive();  // Virtual destructor

    void move() override;
    std::string get_name() override;

private:
    static const int ING_SPEED = 4;
    std::string name = "Olive";
};

#endif // OLIVE_HPP
