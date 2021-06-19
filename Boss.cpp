#include "Boss.h"

Boss::Boss(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window)
        :Entity(X_pos, Y_pos, texture, window){
    max_hitpoints = 500;
    hitpoints = max_hitpoints;
}

void Boss::Update(float deltaTime) {
    if(position_switch_timer >= 100){
        target_position_x = rand()%564+36;
        target_position_y = rand()%60+70;
        position_switch_timer = 0;
    }
    if(target_position_x == sprite.getPosition().x){
        //do nothing
    }else{
        if(target_position_x < sprite.getPosition().x){
            sprite.move(-1, 0);
        }else{
            sprite.move(1, 0);
        }
    }
    if(target_position_y == sprite.getPosition().y){
        //do nothing
    }else{
        if(target_position_y < sprite.getPosition().y){
            sprite.move(0, -1);
        }else{
            sprite.move(0, 1);
        }
    }

    position_switch_timer++;
}