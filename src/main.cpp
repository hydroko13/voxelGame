#define STB_IMAGE_IMPLEMENTATION

#include "game/game.h"

int main() {

    Game game;

    if (game.init() != 0) {
        
        return -1;
    }
    if (game.run() != 0)
    {
    
        return -1;
    }
    

    return 0;
}