#include "Boss.h"

Boss::Boss(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window)
        :Entity(X_pos, Y_pos, texture, window){
    hitpoints = 1000;
}

void Boss::Update(float deltaTime) {

}