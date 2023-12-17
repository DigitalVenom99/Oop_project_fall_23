#ifndef CAR_HPP
#define CAR_HPP

#include "obstacle.hpp"
#include "player.hpp"

class Car : public Obstacle {
public:
    Car(SDL_Renderer* renderer, int xPos, Player* playerPtr);

    void move() override;
    

private:
    static const int OBSTACLE_SPEED = 2;
    SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer);
    Player* player;
    bool followPlayer = true;
};

#endif // CAR_HPP
