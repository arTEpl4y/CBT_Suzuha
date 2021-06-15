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

void Game::Init(){
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Snake", sf::Style::Close);
    window->setFramerateLimit(30);

    head_t.loadFromFile("../Textures/head.png");
    body_t.loadFromFile("../Textures/body.png");
    food_t.loadFromFile("../Textures/food.png");
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

void Game::Update(){
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
        head->Update(deltaTime);

        if(head->checkCollision(wall_top) || head->checkCollision(wall_right) ||
           head->checkCollision(wall_bottom) || head->checkCollision(wall_left)){
            game_over = true;
        }

        for(auto i:body_vec){
            i->Update(deltaTime);
            if(i->kimi_no_na_wa != head && head->checkCollision(i)){
                game_over = true;
            }
        }

        if(game_over){
            Stop();
            return;
        }

        for(auto i:food_vec){
            if(head->checkCollision(i)){
                i->Spawn();
                if(body_vec.size() == 0){
                    body_vec.push_back(new Body(head->GetEntityX_pos(), head->GetEntityY_pos(), &body_t, window,
                                                difficulty, head));
                }else{
                    body_vec.push_back(new Body(body_vec[body_vec.size()-1]->GetEntityX_pos(),
                                                body_vec[body_vec.size()-1]->GetEntityY_pos(),
                                                &body_t, window, difficulty, body_vec[body_vec.size()-1]));
                }
                score += 100;
                menu->UpdateScoreText(score);
            }
        }

        a++;
        if(a >= 20 && b > 0){
            a = 0;
            b--;
            if(body_vec.size() == 0){
                body_vec.push_back(new Body(head->GetEntityX_pos(), head->GetEntityY_pos(), &body_t, window,
                                            difficulty, head));
            }else{
                body_vec.push_back(new Body(body_vec[body_vec.size()-1]->GetEntityX_pos(), body_vec[body_vec.size
                                                    ()-1]->GetEntityY_pos(), &body_t,
                                            window, difficulty, body_vec[body_vec.size()-1]));
            }
        }
    }
}

void Game::Draw(){
    window->clear(sf::Color(64, 64, 64));
    menu->Draw();
    wall_left->Draw();
    wall_right->Draw();
    wall_top->Draw();
    wall_bottom->Draw();
    if(isGameRunning){
        for(auto i : food_vec){
            i->Draw();
        }
        head->Draw();
        for(auto i : body_vec){
            i->Draw();
        }
    }
    window->display();
}

bool Game::isWindowOpen(){
    return window->isOpen();
}

std::chrono::milliseconds Game::getMilliseconds(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void Game::StartGame(){
    isGameRunning = true;

    b = 2;

    difficulty = menu->selected_difficulty;

    score = 0;
    menu->UpdateScoreText(score);

    food_vec = {};

    for(int i = 0; i < 5; i++){
        food_vec.push_back(new Food(0, 0, &food_t, window));
    }
    for(int i = 0; i < 5; i++){
        food_vec[i]->Spawn();
    }

    head = new Head(300, 300, &head_t, window, difficulty);

    body_vec = {};
}

void Game::Stop(){
    isGameRunning = false;
    delete head;
    head = nullptr;
    for(auto p:food_vec){
        delete p;
    }
    for(auto p:body_vec){
        delete p;
    }
    food_vec.clear();
    body_vec.clear();
}