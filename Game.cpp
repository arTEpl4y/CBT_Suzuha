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
    window->setFramerateLimit(30);

    player_t.loadFromFile("../Textures/player.png");
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

        if(game_over){
            Stop();
            return;
        }
    }
}

void Game::Draw(){//self-explanatory
    window->clear(sf::Color(128, 32, 32));
    menu->Draw();
    wall_left->Draw();
    wall_right->Draw();
    wall_top->Draw();
    wall_bottom->Draw();
    if(isGameRunning){
        player->Draw();
    }
    window->display();
}

bool Game::isWindowOpen(){//self-explanatory
    return window->isOpen();
}

std::chrono::milliseconds Game::getMilliseconds(){//nie wiem
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void Game::StartGame(){//tworzenie stuffu
    isGameRunning = true;

    difficulty = menu->selected_difficulty;

    player = new Player(300, 300, &player_t, window, difficulty);
}

void Game::Stop(){//self-explanatory
    isGameRunning = false;
    delete player;
    player = nullptr;
}