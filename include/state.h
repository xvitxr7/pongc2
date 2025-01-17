#pragma once

#include "common.h"

#include "player.h"
#include "ball.h"

#define PC_PLAYER_LIMIT 2
#define PC_FLAGS_COUNT 2 // Placeholder

#define PC_FLAG_DRAW_BBOXES 0
#define PC_FLAG_DEBUG_FONT 1

#define PC_HAS_OPT(str, opt) strcmp(str, opt) > 0

struct pc_state_t {
    SDL_Window*   window;
    SDL_Renderer* renderer;

    int running;
    struct {
        int started;

        int players_idx;
        pc_player* players[PC_PLAYER_LIMIT];

        pc_ball* ball;

        // Teams are defined as the sides the players are in themselves.
        // Left is index 0 and right is index 1.
        score teams[2];
    } game;

    // Contains the screen's boundaries. Its main purpose is to stop the ball from getting out of boundaries.
    pc_rect window_b[4];
    // Background color.
    pc_color bg_color;

    int flags[PC_FLAGS_COUNT];
};

extern struct pc_state_t pc_state;

pc_player* pc_spawn_player(pc_player* player);
pc_ball*   pc_spawn_ball(float radius);

void pc_reset_game();

int  pc_init(int argc, char** argv);
void pc_quit();

void pc_score(int amount, pc_teams team);
// Updates the game's elements to the window size. This includes centering the ball, 
// recalculating the players coordinates, resizing the screen's boundaries, among other things.
void pc_update_window_size();
