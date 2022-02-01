#include "game.h"

int main(void)
{
    struct Game game;

    game_init(&game);
    game_run(&game);
    game_shutdown(&game);

    return 0;
}