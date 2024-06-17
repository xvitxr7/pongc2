#pragma once

#include "common.h"

#include "player.h"
#include "ball.h"

#define PC_PLAYER_LIMIT 2

struct pc_state_t {
    SDL_Window*   window;
    SDL_Renderer* renderer;

    int running;
    struct {    
        int started;    

        int players_idx;
        pc_player* players[PC_PLAYER_LIMIT];

        pc_ball* ball;
    } game;

    // Contains the screen's boundaries. Its main purpose is to stop the ball from getting out of boundaries.
    pc_bbox screen_b[4];

    struct {
        // Determines if PongC will draw its object's bounding boxes.
        int draw_bb;
    } flags;
};

extern struct pc_state_t pc_state;

pc_player* pc_spawn_player(pc_player* player);
pc_ball*   pc_spawn_ball(float radius);

void pc_reset_game();

int  pc_init();
void pc_quit();

void pc_assign_point(int qnty);
// Updates the game's elements to the window size. This includes centering the ball, 
// recalculating the players coordinates, resizing the screen's boundaries, among other things.
void pc_update_window_size();