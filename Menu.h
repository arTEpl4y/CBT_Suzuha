#ifndef CBT_SUZUHA_MENU_H
#define CBT_SUZUHA_MENU_H

#include <iostream>
#include <fstream>

#include "Button.h"
#include "Difficulty.h"

class Menu{
private:
    Button* start_game;
    Button* difficulties;
    Button* difficulties_easy;
    Button* difficulties_normal;
    Button* difficulties_hard;
    Button* back;
    Button* quit;
    sf::RenderWindow* window;
    sf::Font* font;
    sf::Text* fps_counter;
    bool start_game_requested{}, quit_requested{};
    bool inDifficultyView = false;

public:
    Menu(sf::RenderWindow* window);
    ~Menu();
    void UpdateFPS(float deltaTime);
    //void SaveHighscore();
    void Draw();
    void CheckButtonPresses(sf::Event::MouseButtonEvent* mouse_event);
    bool RequestedQuit() const;
    bool RequestedStartGame();
    Difficulty selected_difficulty = NORMAL;
};

#endif