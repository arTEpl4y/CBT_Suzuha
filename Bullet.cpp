#include "Bullet.h"

Bullet::Bullet(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window)
        :Entity(X_pos, Y_pos, texture, window){

}

void Bullet::Update(float deltaTime) {
    sprite.move(0, -5);
}