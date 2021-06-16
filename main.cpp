#include "Game.h"

int main(){
    Game* game = new Game();
    game->Init();
    int loop_timer = 0;

    while(game->isWindowOpen()){
        if(loop_timer > 10){
            loop_timer = 0;
        }
        loop_timer += loop_timer+1;
        game->DebugView();
        game->Update(loop_timer);
        game->Draw();
    }

    delete game;
}