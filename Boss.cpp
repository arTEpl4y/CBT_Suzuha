#include "Boss.h"

Boss::Boss(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window)
        :Entity(X_pos, Y_pos, texture, window){
    max_hitpoints = 500;
    hitpoints = max_hitpoints;
}

void Boss::Update(float deltaTime) {

}