#include "state.h"
#include "ball.h"
#include "player.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

// Sets the main window's properties like title, minimum and maximum size, etc. 
static void set_window_props() {
    SDL_SetWindowTitle(pc_state.window, "PongC * Game");
    SDL_SetWindowMinimumSize(pc_state.window, 192, 108);
}

static void terminate_game() {
    // Deletes all players.
    for (int i = 0; i < PC_PLAYER_LIMIT; i++) {
        pc_player* p = pc_state.game.players[i];
        if (!p) continue;
        free(p);
    }

    if (pc_state.game.ball) free(pc_state.game.ball);

    pc_state.game.players_idx = -1;
    pc_state.game.started     = 0;
}

static void init_game() {
    pc_player* player1 = pc_init_com_player(PC_COMLEVEL_IMP);
    pc_player* player2 = pc_init_com_player(PC_COMLEVEL_EASY);

    pc_spawn_player(player1);
    pc_spawn_player(player2);

    pc_spawn_ball(10);
}

void pc_reset_game() {
    terminate_game();
    init_game();
    pc_update_window_size();
}

// Allocates and initializes PongC's resources.
int pc_init() {
    assertm(!(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_SENSOR) != 0), "SDL failed to initialize.");
    assertm(TTF_Init() == 0, "TTF failed to initialize.");

    assertm(SDL_CreateWindowAndRenderer(
        800, 500,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
        &pc_state.window, &pc_state.renderer
    ) == 0, "Failed to initialize PongC's window and/or renderer.");

    pc_state.running = 0;

    // Enables VSync.
    SDL_RenderSetVSync(pc_state.renderer, 1);
    
    pc_reset_game();

    return 0;
}

void pc_quit() {
    SDL_Quit();
    TTF_Quit();

    SDL_DestroyWindow(pc_state.window);
    SDL_DestroyRenderer(pc_state.renderer);
}

pc_ball* pc_spawn_ball(float radius) {
    pc_state.game.ball = pc_init_ball(radius);
    
    return pc_state.game.ball;
}

void adjust_player_position(pc_player* player) {
    int ww, wh;
    SDL_GetWindowSize(pc_state.window, &ww, &wh);

    player->bbox.x = player->team == PC_TEAM_LEFT ? 50 : ww - 50.f;
    player->bbox.y = wh / 2.f;
    // We subtract the y position of the player with half of the height.
    // This centers the rectangle.
    player->bbox.y -= player->bbox.h / 2.f;
}

pc_player* pc_spawn_player(pc_player* _player) {
    if (pc_state.game.players_idx + 1 >= PC_PLAYER_LIMIT) {
        printf("Cannot spawn player. (Limit reached: %i)", PC_PLAYER_LIMIT);
        return NULL;
    }

    _player->index = pc_state.game.players_idx;

    // Checks if the player index is a modulus of 2. Is true, the side is right, else is left.
    // This allows easy implementation of multiple players. (Not implemented yet)
    _player->team = (_player->index + 1) % 2 != 0 ? PC_TEAM_RIGHT : PC_TEAM_LEFT;

    adjust_player_position(_player);

    pc_state.game.players_idx++;
    pc_state.game.players[pc_state.game.players_idx] = _player;

    return _player;
}

void resize_screen_bb() {
    int ww, wh;
    SDL_GetWindowSize(pc_state.window, &ww, &wh);

    /*
     *  [0] top-left    -> bottom-left
     *  [1] top-left    -> top-right
     *  [2] top-right   -> bottom-right 
     *  [3] bottom-left -> bottom-right
     */

    pc_state.screen_b[0].x = -10;
    pc_state.screen_b[0].y = 0;
    pc_state.screen_b[0].w = 10;
    pc_state.screen_b[0].h = wh;

    pc_state.screen_b[1].x = 0;
    pc_state.screen_b[1].y = -10;
    pc_state.screen_b[1].w = ww;
    pc_state.screen_b[1].h = 10;

    pc_state.screen_b[2].x = ww;
    pc_state.screen_b[2].y = 0;
    pc_state.screen_b[2].w = 10;
    pc_state.screen_b[2].h = wh;

    pc_state.screen_b[3].x = 0;
    pc_state.screen_b[3].y = wh;
    pc_state.screen_b[3].w = ww;
    pc_state.screen_b[3].h = 10;
}

static void update_game_elements() {
    int ww, wh;
    SDL_GetWindowSize(pc_state.window, &ww, &wh);

    /* Players */
    {
        for (int i = 0; i <= pc_state.game.players_idx; i++) {
            pc_player* player = pc_state.game.players[i];
            if (!player) continue;

            adjust_player_position(player);
        }
    }

    /* Ball */
    {
        pc_state.game.ball->bbox.x = ww / 2.f - pc_state.game.ball->bbox.w / 2;
        pc_state.game.ball->bbox.y = wh / 2.f - pc_state.game.ball->bbox.h / 2;
    }
}

void pc_update_window_size() {
    if (!pc_state.game.started) {
        update_game_elements();
    }
    
    /* Screen Boundaries Box */
    resize_screen_bb();
}