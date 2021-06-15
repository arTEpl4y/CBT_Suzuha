#ifndef CBT_SUZUHA_GAME_H
#define CBT_SUZUHA_GAME_H

#include <chrono>
#include <iostream>

#include "Head.h"
#include "Player.h"
#include "Food.h"
#include "Menu.h"

class Game{
private:
    float deltaTime{};
    sf::Texture player_t, wall_t;
    Entity* wall_top{};
    Entity* wall_right{};
    Entity* wall_bottom{};
    Entity* wall_left{};
    sf::RenderWindow* window{};
    Menu* menu{};
    Player* player{};
    std::chrono::milliseconds current_time = getMilliseconds();
    std::chrono::milliseconds endOfFrameTime = getMilliseconds();
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