#ifndef CBT_SUZUHA_BULLET_H
#define CBT_SUZUHA_BULLET_H

#include "Entity.h"

class Bullet : public Entity{
private:

public:
    Bullet(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window);
    void Update(float deltaTime) override;
};

#endif