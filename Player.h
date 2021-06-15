#ifndef CBT_SUZUHA_PLAYER_H
#define CBT_SUZUHA_PLAYER_H

#include "Difficulty.h"
#include "Entity.h"

class Player : public Entity{
private:

public:
    Player(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window, Difficulty diff);
    void Update(float deltaTime) override;
    bool checkCollision(Entity *entity);
    int speed;
};

#endif