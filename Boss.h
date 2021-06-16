#ifndef CBT_SUZUHA_BOSS_H
#define CBT_SUZUHA_BOSS_H

#include "Entity.h"

class Boss : public Entity{
private:

public:
    Boss(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window);
    void Update(float deltaTime) override;
    int hitpoints;
};

#endif