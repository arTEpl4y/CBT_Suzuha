#include "Game.h"

int main(){
    Game* game = new Game();
    game->Init();

    while(game->isWindowOpen()){
        game->DebugView();
        game->Update();
        game->Draw();
    }

    delete game;
}