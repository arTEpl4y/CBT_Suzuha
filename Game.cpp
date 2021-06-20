#include "Game.h"

Game::Game(){
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
    srand(time(nullptr));

    HWND hwnd = GetConsoleWindow(); //testing
    ShowWindow(hwnd, SW_HIDE);

    icon.loadFromFile("../Files/super_ikonka_super_gierki.png");
    music.openFromFile("../Files/suzuha_ost.ogg");
    wall_t.loadFromFile("../Files/wall.png");
    player_t.loadFromFile("../Files/player.png");
    hitbox_t.loadFromFile("../Files/hitbox.png");
    bullet_t.loadFromFile("../Files/bullet.png");
    boss_t.loadFromFile("../Files/boss.png");
    boss_hp_bar_t.loadFromFile("../Files/hp_bar.png");
    spiritfire_t.loadFromFile("../Files/spiritfire2.png");
    redfire_t.loadFromFile("../Files/redfire.png");

    window = new sf::RenderWindow(sf::VideoMode(800, 600), "CBT Suzuha", sf::Style::Close);
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window->setFramerateLimit(60);

    wall_top = new Entity(300, 5, &wall_t, window);
    wall_right = new Entity(595, 300, &wall_t, window);
    wall_right->sprite.setRotation(90);
    wall_bottom = new Entity(300, 595, &wall_t, window);
    wall_left = new Entity(5, 300, &wall_t, window);
    wall_left->sprite.setRotation(90);

    menu = new Menu(window);

    music.setLoop(true);
    music.setVolume(10);
    music.play();

    isGameRunning = false;

    current_time = getMilliseconds();
    endOfFrameTime = getMilliseconds();
}

void Game::Update(){//logika gry
    endOfFrameTime = getMilliseconds();
    deltaTime = (endOfFrameTime-current_time).count()*0.001;
    current_time = getMilliseconds();

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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            player->sprite.move(0, -player->speed*deltaTime);
            player_hitbox->sprite.move(0, -player->speed*deltaTime);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            player->sprite.move(0, player->speed*deltaTime);
            player_hitbox->sprite.move(0, player->speed*deltaTime);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            player->sprite.move(-player->speed*deltaTime, 0);
            player_hitbox->sprite.move(-player->speed*deltaTime, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            player->sprite.move(player->speed*deltaTime, 0);
            player_hitbox->sprite.move(player->speed*deltaTime, 0);
        }
        if(player->checkCollision(wall_top)){
            player->sprite.move(0, player->speed*deltaTime);
            player_hitbox->sprite.move(0, player->speed*deltaTime);
        }
        if(player->checkCollision(wall_bottom)){
            player->sprite.move(0, -player->speed*deltaTime);
            player_hitbox->sprite.move(0, -player->speed*deltaTime);
        }
        if(player->checkCollision(wall_left)){
            player->sprite.move(player->speed*deltaTime, 0);
            player_hitbox->sprite.move(player->speed*deltaTime, 0);
        }
        if(player->checkCollision(wall_right)){
            player->sprite.move(-player->speed*deltaTime, 0);
            player_hitbox->sprite.move(-player->speed*deltaTime, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)){
            if (Bullet_spawn_cooldown > 10){
                player_bullet_vec.push_back(
                        new Entity(player->sprite.getPosition().x, player->sprite.getPosition().y, &bullet_t, window));
                Bullet_spawn_cooldown = 0;
            }
        }
        for(size_t i = 0; i < player_bullet_vec.size(); i++){
            player_bullet_vec[i]->sprite.move(0, -5);
            if(boss->checkCollision(player_bullet_vec[i])){
                player_bullet_vec.erase(player_bullet_vec.begin()+i);
                boss->hitpoints -= 1;
                boss_hp_bar->sprite.setScale(boss->hitpoints/boss->max_hitpoints*1.0f, 1);
            }
            if(wall_top->checkCollision(player_bullet_vec[i])){
                player_bullet_vec.erase(player_bullet_vec.begin()+i);
            }
        }

        boss->Update(deltaTime);
        if(boss->target_position_x == boss->sprite.getPosition().x){
            //do nothing
        }else{
            if(boss->target_position_x < boss->sprite.getPosition().x){
                boss->sprite.move(-1, 0);
            }else{
                boss->sprite.move(1, 0);
            }
        }
        if(boss->target_position_y == boss->sprite.getPosition().y){
            //do nothing
        }else{
            if(boss->target_position_y < boss->sprite.getPosition().y){
                boss->sprite.move(0, -1);
            }else{
                boss->sprite.move(0, 1);
            }
        }
        if(spiritfire_cd > 120){
            if(spiritfire_cd2 == 10 || spiritfire_cd2 == 20 || spiritfire_cd2 == 30){
                spiritfire_vec.push_back(
                    new Entity(boss->sprite.getPosition().x, boss->sprite.getPosition().y, &spiritfire_t, window));
            }
            spiritfire_cd2 += 1;
            redfire_cd -= 1;
            if(spiritfire_cd2 > 30){
                spiritfire_cd = 0;
                spiritfire_cd2 = 0;
            }
        }
        for(size_t i = 0; i < spiritfire_vec.size(); i++){
            spiritfire_vec[i]->sprite.move(0, 4);
            if(spiritfire_vec[i]->checkCollision(player_hitbox)){
                game_over = true;
            }
            if(wall_bottom->checkCollision(spiritfire_vec[i])){
                spiritfire_vec.erase(spiritfire_vec.begin()+i);
            }
        }

        if(redfire_cd > 80 && spiritfire_cd2 == 0){
            redfire_vec.push_front(
                new Entity(boss->sprite.getPosition().x, boss->sprite.getPosition().y, &redfire_t, window));
            redfire_vec.push_front(
                new Entity(boss->sprite.getPosition().x, boss->sprite.getPosition().y, &redfire_t, window));
            redfire_vec.push_front(
                new Entity(boss->sprite.getPosition().x, boss->sprite.getPosition().y, &redfire_t, window));
            redfire_vec[0]->sprite.setRotation(30);
            redfire_vec[2]->sprite.setRotation(330);
            redfire_cd = 0;
        }
        for(size_t i = 0; i < redfire_vec.size(); i++){
            if(redfire_vec[i]->sprite.getRotation() == 330){
                redfire_vec[i]->sprite.move(0.5f, 3);
            }
            if(redfire_vec[i]->sprite.getRotation() == 0){
                redfire_vec[i]->sprite.move(0, 3);
            }
            if(redfire_vec[i]->sprite.getRotation() == 30){
                redfire_vec[i]->sprite.move(-0.5f, 3);
            }
            if(redfire_vec[i]->checkCollision(player_hitbox)){
                game_over = true;
            }
            if(wall_left->checkCollision(redfire_vec[i]) || wall_bottom->checkCollision(redfire_vec[i])
                || wall_right->checkCollision(redfire_vec[i])){
                redfire_vec.erase(redfire_vec.begin()+i);
            }
        }

        if(player->checkCollision(boss) || boss->hitpoints == 0){
            game_over = true;
        }

        if(game_over){
            Stop();
            return;
        }

        Bullet_spawn_cooldown += 1;
        spiritfire_cd += 1;
        redfire_cd += 1;
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
        for(auto i : spiritfire_vec){
            i->Draw();
        }
        for(auto i : redfire_vec){
            i->Draw();
        }
        player->Draw();
        player_hitbox->Draw();
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

    Bullet_spawn_cooldown = 0;
    spiritfire_cd = 0;
    redfire_cd = 0;

    player = new Player(300, 500, &player_t, window, difficulty);
    player_hitbox = new Entity(300, 500, &hitbox_t, window);

    boss = new Boss(300, 100, &boss_t, window);
    //boss->sprite.setScale(0.5945945945945946f, 0.5588235294117647f);

    boss_hp_bar = new Entity(300, 2, &boss_hp_bar_t, window);
}

void Game::Stop(){//self-explanatory
    isGameRunning = false;
    delete player;
    player = nullptr;
    delete player_hitbox;
    player_hitbox = nullptr;
    delete boss;
    boss = nullptr;
    for(auto i : player_bullet_vec){
        delete i;
    }
    player_bullet_vec.clear();
    for(auto i : spiritfire_vec){
        delete i;
    }
    spiritfire_vec.clear();
    for(auto i : redfire_vec){
        delete i;
    }
    redfire_vec.clear();
}