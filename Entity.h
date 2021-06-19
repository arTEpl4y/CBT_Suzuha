#ifndef CBT_SUZUHA_ENTITY_H
#define CBT_SUZUHA_ENTITY_H

#include <SFML/Graphics.hpp>
#include <ctime>
#include "Point.h"

class Entity{
private:
    sf::RenderWindow *window;

public:
    Entity(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window);
    virtual ~Entity();
    int GetEntityX_pos() const;
    int GetEntityY_pos() const;
    float GetEntity_width() const;
    float GetEntity_height() const;
    virtual void Update(float deltaTime);
    bool checkCollision(Entity *entity);
    void Draw();
    Point point;
    sf::Sprite sprite;
};

#endif