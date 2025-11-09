

#include "game/game.h"

int main() {

    Game game;

    if (game.init() != 0) {
        
        return 100;
    }
    if (game.run() != 0)
    {
    
        return 200;
    }
    

    return 0;
}