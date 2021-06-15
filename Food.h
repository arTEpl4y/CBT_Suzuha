#ifndef CBT_SUZUHA_FOOD_H
#define CBT_SUZUHA_FOOD_H

#include <ctime>

#include "Entity.h"

class Food : public Entity{
private:
    const int spawn_area = 570;
    const int border_of_spawn = 15;

public:
    Food(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window);
    void Spawn();
};

#endif