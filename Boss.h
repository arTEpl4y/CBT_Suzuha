#ifndef CBT_SUZUHA_BOSS_H
#define CBT_SUZUHA_BOSS_H

#include "Entity.h"

class Boss : public Entity{
private:
    int position_switch_timer = 50;
    int target_position_x = 300;
    int target_position_y = 100;

public:
    Boss(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window);
    void Update(float deltaTime) override;
    float max_hitpoints, hitpoints;
};

#endif