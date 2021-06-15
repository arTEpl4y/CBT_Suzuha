#include "Menu.h"

Menu::Menu(sf::RenderWindow* window){
    font = new sf::Font;
    font->loadFromFile("../arial.ttf");

    start_game = new Button(700, 325, 130, 50, sf::Color(128, 128, 128), "NEW GAME", font, window);
    high_scores = new Button(700, 400, 130, 50, sf::Color(128, 128, 128), "SCORES", font, window);
    difficulties = new Button(700, 475, 130, 50, sf::Color(128, 128, 128), "LEVEL", font, window);
    difficulties_easy = new Button(700, 325, 130, 50, sf::Color(128, 128, 128), "EASY", font, window);
    difficulties_normal = new Button(700, 400, 130, 50, sf::Color(128, 128, 128), "NORMAL", font, window);
    difficulties_hard= new Button(700, 475, 130, 50, sf::Color(128, 128, 128), "HARD", font, window);
    back = new Button(700, 550, 130, 50, sf::Color(128, 128, 128), "BACK", font, window);
    quit = new Button(700, 550, 130, 50, sf::Color(128, 128, 128), "QUIT", font, window);
    score_count = new sf::Text("SCORE: ", *font, 20);
    score_count->setOrigin(0, score_count->getGlobalBounds().height/2+5);
    score_count->setPosition(605, 270);
    fps_counter = new sf::Text("FPS: ", *font, 12);
    fps_counter->setPosition(750, 583);

    score_text = new sf::Text("HIGHSCORES", *font, 20);

    this->window = window;
}

Menu::~Menu(){
    delete start_game;
    delete high_scores;
    delete difficulties;
    delete difficulties_easy;
    delete difficulties_normal;
    delete difficulties_hard;
    delete back;
    delete quit;
    delete score_count;
    delete fps_counter;
    delete score_text;
    delete font;
}

void Menu::UpdateScoreText(int score) {
    score_count->setString("SCORE: "+std::to_string(score));
}

void Menu::UpdateFPS(float deltaTime){
    fps_counter->setString("FPS: "+std::to_string((int)((1/deltaTime))));
}

/*void Menu::SaveHighscore(){

}*/

void Menu::ShowHighscores(){
    std::string text;
    int i = 0;
    std::ifstream ReadFileHighscores("../highscores.txt");
    while(std::getline(ReadFileHighscores, text)){
        score_text->setString(text);
        score_text->setOrigin(score_text->getGlobalBounds().width/2, score_text->getGlobalBounds().height/2+5);
        score_text->setPosition(700, 50+i);
        window->draw(*score_text);
        i += 30;
    }
    ReadFileHighscores.close();
}

void Menu::Draw(){
    if(inScoreView){
        ShowHighscores();
    }
    if(inDifficultyView){
        difficulties_easy->Draw();
        difficulties_normal->Draw();
        difficulties_hard->Draw();
    }
    if(!inScoreView && !inDifficultyView){
        window->draw(*score_count);
        start_game->Draw();
        high_scores->Draw();
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
    if(!inScoreView && !inDifficultyView){
        if(start_game->isButtonPressed(mouse_event)){
            start_game_requested = true;
            return;
        }
        if(high_scores->isButtonPressed(mouse_event)){
            inScoreView = true;
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
    if(inScoreView || inDifficultyView){
        if(back->isButtonPressed(mouse_event)){
            inScoreView = false;
            inDifficultyView = false;
            return;
        }
    }
}

bool Menu::RequestedQuit() {
    return quit_requested;
}

bool Menu::RequestedStartGame() {
    if(start_game_requested){
        start_game_requested = false;
        return true;
    }
    return false;
}