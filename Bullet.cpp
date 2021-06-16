#include "Bullet.h"

Bullet::Bullet(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window)
        :Entity(X_pos, Y_pos, texture, window){

}

void Bullet::Update(float deltaTime) {
    sprite.move(0, -5);
}

bool Bullet::checkCollision(Entity *entity) {
    float deltaX = point.X - entity->point.X;
    float deltaY = point.Y - entity->point.Y;
    float intersectX = abs(deltaX)-(GetEntity_width()*0.5f + entity->GetEntity_width()*0.5f);
    float intersectY = abs(deltaY)-(GetEntity_height()*0.5f + entity->GetEntity_height()*0.5f);

    return (intersectX<0 && intersectY<0);
}