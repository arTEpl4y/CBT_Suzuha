#ifndef CBT_SUZUHA_GAME_H
#define CBT_SUZUHA_GAME_H

#include <SFML/Audio/Music.hpp>
#include <Windows.h>
#include <chrono>
#include <iostream>
#include <deque>

#include "Player.h"
#include "Boss.h"
#include "Menu.h"

class Game{
private:
    float deltaTime{};
    int timer;
    sf::Image icon;
    sf::Music music;
    sf::Texture player_t, hitbox_t, bullet_t, boss_t, wall_t, boss_hp_bar_t;
    sf::Texture spiritfire_t, redfire_t, seal1_t, seal2_t;
    Entity* wall_top{};
    Entity* wall_right{};
    Entity* wall_bottom{};
    Entity* wall_left{};
    sf::RenderWindow* window{};
    Menu* menu{};
    Player* player{};
    Entity* player_hitbox{};
    Boss* boss{};
    Entity* boss_hp_bar{};
    std::deque<Entity*> player_bullet_vec;
    std::deque<Entity*> spiritfire_vec, redfire_vec, seal_vec;
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
    int Bullet_spawn_cooldown = 0;
    int spiritfire_cd, spiritfire_cd2 = 0;
    int redfire_cd = 0;
    int seal_wall_cd = 0;
};

#endif