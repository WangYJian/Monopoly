#include <stdio.h>
#include<malloc.h>
#include "Game.h"

int main() {
    Game* game = malloc(sizeof(Game));
    GameInitialize(game);
    return 0;
}
