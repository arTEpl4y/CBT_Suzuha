#include "Button.h"

Button::Button(int x_pos, int y_pos, int width, int height, sf::Color color, std::string string,
               sf::Font* font, sf::RenderWindow* window){
    button_shape = new sf::RectangleShape(sf::Vector2f(width, height));
    button_shape->setFillColor(color);
    button_shape->setPosition(x_pos, y_pos);
    button_shape->setOrigin(width/2, height/2);
    text = new sf::Text(string, *font, 20);
    text->setPosition(x_pos, y_pos);
    text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2+5);
    this->window = window;
}

Button::~Button(){
    delete button_shape;
    delete text;
}

bool Button::isButtonPressed(sf::Event::MouseButtonEvent* mouse_event) const{
    float deltaX = button_shape->getPosition().x - mouse_event->x;
    float deltaY = button_shape->getPosition().y - mouse_event->y;
    float overlapX = abs(deltaX) - button_shape->getGlobalBounds().width*0.5f;
    float overlapY = abs(deltaY) - button_shape->getGlobalBounds().height*0.5f;

    return (overlapX<0 && overlapY<0);
}

void Button::Draw(){
    window->draw(*button_shape);
    window->draw(*text);
}