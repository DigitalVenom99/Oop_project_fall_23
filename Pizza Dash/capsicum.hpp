#ifndef CAPSICUM_HPP
#define CAPSICUM_HPP

#include "ingredient.hpp"  // Include the base class header file

class Capsicum : public Ingredient {
public:
    Capsicum(SDL_Renderer* renderer, int xPos);
    virtual ~Capsicum();  // Virtual destructor

    void move() override;
    std::string get_name() override;

private:
    static const int ING_SPEED = 4;
    std::string name = "Capsicum";
};

#endif // CAPSICUM_HPP
