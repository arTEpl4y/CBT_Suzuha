#ifndef CBT_SUZUHA_GAME_H
#define CBT_SUZUHA_GAME_H

#include <chrono>
#include <iostream>
#include <deque>

#include "Player.h"
#include "Bullet.h"
#include "Menu.h"

class Game{
private:
    float deltaTime{};
    int timer;
    sf::Texture player_t, bullet_t, wall_t;
    Entity* wall_top{};
    Entity* wall_right{};
    Entity* wall_bottom{};
    Entity* wall_left{};
    sf::RenderWindow* window{};
    Menu* menu{};
    Player* player{};
    std::deque<Bullet*> player_bullet_vec;
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