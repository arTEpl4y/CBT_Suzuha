#include "Boss.h"

Boss::Boss(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window)
        :Entity(X_pos, Y_pos, texture, window){
    max_hitpoints = 500;
    hitpoints = max_hitpoints;
}

void Boss::Update(float deltaTime) {
    if(position_switch_timer >= 100){
        target_position_x = rand()%527+36;
        target_position_y = rand()%80+60;
        position_switch_timer = 0;
    }

    position_switch_timer++;
}