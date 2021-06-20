#include <iostream>

#include "Player.h"

Player::Player(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window, Difficulty diff)
        :Entity(X_pos, Y_pos, texture, window){
    speed = diff;
}

void Player::Update(float deltaTime){

}