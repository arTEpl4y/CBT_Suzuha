#include "Food.h"

Food::Food(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window)
        :Entity(X_pos, Y_pos, texture, window){

}

void Food::Spawn(){
    point = Point(rand() % spawn_area + border_of_spawn, rand() % spawn_area + border_of_spawn);
    sprite.setPosition(point.X, point.Y);
}