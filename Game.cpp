#include "Game.h"

Game::Game(){
    srand(time(nullptr));
}

Game::~Game(){
    Stop();
    delete menu;
    delete wall_top;
    delete wall_right;
    delete wall_bottom;
    delete wall_left;
    delete window;
}

void Game::DebugView() const{
    menu->UpdateFPS(deltaTime);
}

void Game::Init(){//start okna
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "CBT Suzuha", sf::Style::Close);
    window->setFramerateLimit(60);

    player_t.loadFromFile("../Textures/player.png");
    bullet_t.loadFromFile("../Textures/bullet.png");
    boss_t.loadFromFile("../Textures/boss.png");
    boss_hp_bar_t.loadFromFile("../Textures/hp_bar.png");
    wall_t.loadFromFile("../Textures/wall.png");

    wall_top = new Entity(300, 5, &wall_t, window);
    wall_right = new Entity(595, 300, &wall_t, window);
    wall_right->sprite.setRotation(90);
    wall_bottom = new Entity(300, 595, &wall_t, window);
    wall_left = new Entity(5, 300, &wall_t, window);
    wall_left->sprite.setRotation(90);

    menu = new Menu(window);

    isGameRunning = false;

    current_time = getMilliseconds();
    endOfFrameTime = getMilliseconds();
}

void Game::Update(){//logika gry
    endOfFrameTime = getMilliseconds();
    deltaTime = (endOfFrameTime-current_time).count()*0.001;
    current_time = getMilliseconds();
    Bullet_spawn_cooldown += 1;

    bool game_over = false;

    sf::Event event{};
    while(window->pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button==sf::Mouse::Left){
                    menu->CheckButtonPresses(&event.mouseButton);
                }
                break;
            default:
                break;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || menu->RequestedQuit()){
        window->close();
    }
    if(menu->RequestedStartGame()){
        Stop();
        StartGame();
    }

    if(isGameRunning){
        player->Update(deltaTime);
        if(player->checkCollision(wall_top)){
            player->sprite.move(0, player->speed*deltaTime);
        }
        if(player->checkCollision(wall_bottom)){
            player->sprite.move(0, -player->speed*deltaTime);
        }
        if(player->checkCollision(wall_left)){
            player->sprite.move(player->speed*deltaTime, 0);
        }
        if(player->checkCollision(wall_right)){
            player->sprite.move(-player->speed*deltaTime, 0);
        }
        if(player->checkCollision(boss)){
            game_over = true;
        }

        if(Bullet_spawn_cooldown > 10){
            player_bullet_vec.push_back(
                    new Bullet(player->sprite.getPosition().x, player->sprite.getPosition().y, &bullet_t, window));
            Bullet_spawn_cooldown = 0;
        }
        for(size_t i = 0; i < player_bullet_vec.size(); i++){
            player_bullet_vec[i]->Update(deltaTime);
            if(boss->checkCollision(player_bullet_vec[i])){
                player_bullet_vec.erase(player_bullet_vec.begin()+i);
                boss->hitpoints -= 1;
                boss_hp_bar->sprite.setScale(boss->hitpoints/boss->max_hitpoints*1.0f, 1);
            }
            if(wall_top->checkCollision(player_bullet_vec[i])){
                player_bullet_vec.erase(player_bullet_vec.begin()+i);
            }
        }

        if(game_over){
            Stop();
            return;
        }
    }
}

void Game::Draw(){//self-explanatory
    window->clear(sf::Color(32, 32, 32));
    menu->Draw();
    wall_left->Draw();
    wall_right->Draw();
    wall_top->Draw();
    wall_bottom->Draw();
    if(isGameRunning){
        for(auto i : player_bullet_vec){
            i->Draw();
        }
        player->Draw();
        boss->Draw();
        boss_hp_bar->Draw();
    }
    window->display();
}

bool Game::isWindowOpen(){//self-explanatory
    return window->isOpen();
}

std::chrono::milliseconds Game::getMilliseconds(){//full profeska
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void Game::StartGame(){//tworzenie stuffu
    isGameRunning = true;

    difficulty = menu->selected_difficulty;

    player = new Player(300, 500, &player_t, window, difficulty);

    boss = new Boss(300, 100, &boss_t, window);

    boss_hp_bar = new Entity(300, 9, &boss_hp_bar_t, window);
}

void Game::Stop(){//self-explanatory
    isGameRunning = false;
    delete player;
    player = nullptr;
    delete boss;
    boss = nullptr;
    for(auto i : player_bullet_vec){
        delete i;
    }
    player_bullet_vec.clear();
}