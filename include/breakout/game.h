#pragma once

#include <stdbool.h>

typedef enum {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
} GameState;

typedef struct {
    GameState state;
    bool keys[1024];
    unsigned int width, height;
} Game;

// (constructor)
// (destructor)

void game_init(Game *game);
void game_process_input(Game *game, float dt);
void game_update(Game *game, float dt);
void game_render(Game *game);
