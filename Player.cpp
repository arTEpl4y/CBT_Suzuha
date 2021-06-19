#include <iostream>

#include "Player.h"

Player::Player(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window, Difficulty diff)
        :Entity(X_pos, Y_pos, texture, window){
    speed = diff;
}

void Player::Update(float deltaTime){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)){
        deltaTime = deltaTime/2;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        sprite.move(0, -speed*deltaTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        sprite.move(0, speed*deltaTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
        sprite.move(-speed*deltaTime, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        sprite.move(speed*deltaTime, 0);
    }


}