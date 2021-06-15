#ifndef CBT_SUZUHA_GAME_H
#define CBT_SUZUHA_GAME_H

#include <chrono>
#include <iostream>

#include "Head.h"
#include "Food.h"
#include "Menu.h"

class Game{
private:
    float deltaTime{};
    sf::Texture head_t, body_t, food_t, wall_t;
    Entity* wall_top{};
    Entity* wall_right{};
    Entity* wall_bottom{};
    Entity* wall_left{};
    sf::RenderWindow* window{};
    Menu* menu{};
    std::vector<Food*> food_vec;
    Head* head{};
    std::vector<Body*> body_vec;
    std::chrono::milliseconds current_time = getMilliseconds();
    std::chrono::milliseconds endOfFrameTime = getMilliseconds();
    int a = 0;
    int b = 2;
    int score{};
    Difficulty difficulty;
    bool isGameRunning{};

public:
    Game();
    ~Game();
    void DebugView() const;
    void Init();
    void Update();
    void Draw();
    bool isWindowOpen();
    std::chrono::milliseconds getMilliseconds();
    void StartGame();
    void Stop();
};

#endif