#include "Menu.h"

Menu::Menu(sf::RenderWindow* window){
    font = new sf::Font;
    font->loadFromFile("../Files/arial.ttf");

    start_game = new Button(700, 400, 130, 50, sf::Color(128, 128, 128), "NEW GAME", font, window);
    difficulties = new Button(700, 475, 130, 50, sf::Color(128, 128, 128), "SPEED", font, window);
    difficulties_easy = new Button(700, 325, 130, 50, sf::Color(128, 128, 128), "SLOW", font, window);
    difficulties_normal = new Button(700, 400, 130, 50, sf::Color(128, 128, 128), "MEDIUM", font, window);
    difficulties_hard= new Button(700, 475, 130, 50, sf::Color(128, 128, 128), "FAST", font, window);
    back = new Button(700, 550, 130, 50, sf::Color(128, 128, 128), "BACK", font, window);
    quit = new Button(700, 550, 130, 50, sf::Color(128, 128, 128), "QUIT", font, window);
    fps_counter = new sf::Text("FPS: ", *font, 12);
    fps_counter->setPosition(750, 583);

    this->window = window;
}

Menu::~Menu(){
    delete start_game;
    delete difficulties;
    delete difficulties_easy;
    delete difficulties_normal;
    delete difficulties_hard;
    delete back;
    delete quit;
    delete fps_counter;
    delete font;
}

void Menu::UpdateFPS(float deltaTime){
    fps_counter->setString("FPS: "+std::to_string((int)((1/deltaTime))));
}

void Menu::Draw(){
    if(inDifficultyView){
        difficulties_easy->Draw();
        difficulties_normal->Draw();
        difficulties_hard->Draw();
    }
    if(!inDifficultyView){
        start_game->Draw();
        difficulties->Draw();
        quit->Draw();
    }else{
        back->Draw();
    }
    window->draw(*fps_counter);
}

void Menu::CheckButtonPresses(sf::Event::MouseButtonEvent *mouse_event){
    if(inDifficultyView){
        if(difficulties_easy->isButtonPressed(mouse_event)){
            selected_difficulty = EASY;
            inDifficultyView = false;
            return;
        }
        if(difficulties_normal->isButtonPressed(mouse_event)){
            selected_difficulty = NORMAL;
            inDifficultyView = false;
            return;
        }
        if(difficulties_hard->isButtonPressed(mouse_event)){
            selected_difficulty = HARD;
            inDifficultyView = false;
            return;
        }
    }
    if(!inDifficultyView){
        if(start_game->isButtonPressed(mouse_event)){
            start_game_requested = true;
            return;
        }
        if(difficulties->isButtonPressed(mouse_event)){
            inDifficultyView = true;
            return;
        }
        if(quit->isButtonPressed(mouse_event)){
            quit_requested = true;
            return;
        }
    }
    if(inDifficultyView){
        if(back->isButtonPressed(mouse_event)){
            inDifficultyView = false;
            return;
        }
    }
}

bool Menu::RequestedQuit() const{
    return quit_requested;
}

bool Menu::RequestedStartGame() {
    if(start_game_requested){
        start_game_requested = false;
        return true;
    }
    return false;
}