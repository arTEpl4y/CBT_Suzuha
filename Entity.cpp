#include "Entity.h"

Entity::Entity(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window){
    this->point = Point(X_pos, Y_pos);
    sprite.setPosition(X_pos, Y_pos);
    sprite.setTexture(*texture);
    this->window = window;
    sprite.setOrigin(GetEntity_width()/2, GetEntity_height()/2);
}

Entity::~Entity(){

}

int Entity::GetEntityX_pos() const{
    return point.X;
}

int Entity::GetEntityY_pos() const{
    return point.Y;
}

float Entity::GetEntity_width() const{
    return sprite.getGlobalBounds().width;
}

float Entity::GetEntity_height() const{
    return sprite.getGlobalBounds().height;
}

void Entity::Update(float deltaTime){

}

bool Entity::checkCollision(Entity *entity) {
    float deltaX = sprite.getPosition().x - entity->sprite.getPosition().x;
    float deltaY = sprite.getPosition().y - entity->sprite.getPosition().y;
    float intersectX = abs(deltaX)-(GetEntity_width()*0.5f + entity->GetEntity_width()*0.5f);
    float intersectY = abs(deltaY)-(GetEntity_height()*0.5f + entity->GetEntity_height()*0.5f);

    return (intersectX<0 && intersectY<0);
}

void Entity::Draw(){
    window->draw(sprite);
}