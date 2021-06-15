#ifndef CBT_SUZUHA_HEAD_H
#define CBT_SUZUHA_HEAD_H

#include "Body.h"

class Head : public Body{
private:
    int i_direction;
    int p_direction;

public:
    Head(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window, Difficulty diff);
    void Update(float deltaTime) override;
    bool checkCollision(Entity *entity);
};

#endif