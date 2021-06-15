#ifndef CBT_SUZUHA_MENU_H
#define CBT_SUZUHA_MENU_H

#include <iostream>
#include <fstream>

#include "Button.h"
#include "Difficulty.h"

class Menu{
private:
    Button* start_game;
    Button* high_scores;
    Button* difficulties;
    Button* difficulties_easy;
    Button* difficulties_normal;
    Button* difficulties_hard;
    Button* back;
    Button* quit;
    sf::RenderWindow* window;
    sf::Font* font;
    sf::Text* score_count;
    sf::Text* fps_counter;
    sf::Text* score_text;
    bool start_game_requested{}, quit_requested{};
    bool inScoreView{}, inDifficultyView = false;

public:
    Menu(sf::RenderWindow* window);
    ~Menu();
    void UpdateScoreText(int score);
    void UpdateFPS(float deltaTime);
    //void SaveHighscore();
    void ShowHighscores();
    void Draw();
    void CheckButtonPresses(sf::Event::MouseButtonEvent* mouse_event);
    bool RequestedQuit();
    bool RequestedStartGame();
    Difficulty selected_difficulty = NORMAL;
};

#endif