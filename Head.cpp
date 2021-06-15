#include <iostream>

#include "Head.h"

Head::Head(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window, Difficulty diff)
        :Body(X_pos, Y_pos, texture, window, diff, nullptr){
    i_direction = 1;
    p_direction = 0;
}

void Head::Update(float deltaTime){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        i_direction = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        i_direction = 2;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
        i_direction = 3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        i_direction = 4;
    }

    if((p_direction == 1 && i_direction == 2) || (p_direction == 2 && i_direction == 1) ||
       (p_direction == 3 && i_direction == 4) || (p_direction == 4 && i_direction == 3)){//based
    }else{
        if(i_direction != p_direction){
            switch(i_direction){
                case 1:
                    sprite.setRotation(0);
                    break;
                case 2:
                    sprite.setRotation(180);
                    break;
                case 3:
                    sprite.setRotation(270);
                    break;
                case 4:
                    sprite.setRotation(90);
                    break;
            }
        }
        p_direction = i_direction;
    }
    switch(p_direction){
        case 1:
            sprite.move(0, -speed*deltaTime);
            break;
        case 2:
            sprite.move(0, speed*deltaTime);
            break;
        case 3:
            sprite.move(-speed*deltaTime, 0);
            break;
        case 4:
            sprite.move(speed*deltaTime, 0);
            break;
    }
    point.X = sprite.getPosition().x;
    point.Y = sprite.getPosition().y;
    history.emplace_back(point.X, point.Y);
    if(history.size() > max_history){
        history.pop_front();
    }
}

bool Head::checkCollision(Entity *entity){
    float deltaX = point.X - entity->point.X;
    float deltaY = point.Y - entity->point.Y;
    float intersectX = abs(deltaX)-(GetEntity_width()*0.5f + entity->GetEntity_width()*0.5f);
    float intersectY = abs(deltaY)-(GetEntity_height()*0.5f + entity->GetEntity_height()*0.5f);

    return (intersectX<0 && intersectY<0);
}