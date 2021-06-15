#include <iostream>

#include "Body.h"

Body::Body(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window, Difficulty diff, Body* prev)
        :Entity(X_pos, Y_pos, texture, window){
    speed = diff*10;
    max_history = (Difficulty::HARD/diff)*10;
    this->kimi_no_na_wa = prev;
}

void Body::Update(float deltaTime) {
    if (kimi_no_na_wa != nullptr && kimi_no_na_wa->history.size() >= max_history) {
        history.emplace_back(point);
        if (history.size() > max_history) {
            history.pop_front();
        }
        point.X = kimi_no_na_wa->history.front().X;
        point.Y = kimi_no_na_wa->history.front().Y;
        sprite.setPosition(point.X, point.Y);
    }
}