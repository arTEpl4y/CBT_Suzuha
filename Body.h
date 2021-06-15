#ifndef CBT_SUZUHA_BODY_H
#define CBT_SUZUHA_BODY_H

#include "Difficulty.h"
#include "Entity.h"

#include <deque>

class Body : public Entity{
private:

public:
    Body(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window, Difficulty diff, Body* prev);
    Body* kimi_no_na_wa;
    std::deque<Point> history;
    int speed, max_history;
    void Update(float deltaTime) override;
};

#endif