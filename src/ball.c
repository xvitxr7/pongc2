#include "ball.h"
#include "common.h"
#include "player.h"
#include "primitives.h"
#include "state.h"
#include <SDL2/SDL_render.h>
#include <stdint.h>

#include <math.h>
#include <stdlib.h>

pc_ball* pc_init_ball(float radius) {
    pc_ball* ball = (pc_ball*) malloc(sizeof(pc_ball));
    
    int direction = (rand() % 14) - 7;
    ball->ax = direction;
    ball->ay = direction;

    int ww, wh;
    SDL_GetWindowSize(pc_state.window, &ww, &wh);

    ball->radius = radius;
    
    ball->bbox.w = radius * 2;
    ball->bbox.h = radius * 2;
    
    return ball;
}

void pc_update_ball(pc_ball* ball) {
    ball->bbox.x += ball->ax;
    ball->bbox.y += ball->ay;

    // Player on the direction the ball is moving to.
    pc_player* pd = NULL;

    for (int i = 0; i < PC_PLAYER_LIMIT; i++) {
        pc_player* p = pc_state.game.players[i];
        if (!p) continue;
        
        if ((p->side > 0 && ball->ax > 0) || (p->side < 0 && ball->ax < 0)) {
            pd = p;
        }
    }

    if (!pd) return;

    float player_x1 = pd->side == PC_PLAYERSIDE_LEFT ? pd->bbox.x + pd->bbox.w : pd->bbox.x;
    float player_y1 = pd->bbox.y;
    float player_x2 = pd->bbox.x + pd->bbox.w;
    float player_y2 = pd->bbox.y + pd->bbox.h;

    // Using rectangle-line collisions avoids strange collision bugs when the ball hits the top of the player.
    if (pc_is_colliding_bbox_line(&ball->bbox, player_x1, player_y1, player_x2, player_y2)) {
        ball->ax *= -PC_BALL_HIT_MULTIPLIER;
        ball->ay *= PC_BALL_HIT_MULTIPLIER;
    }

    // Checks collisions with the screen's boundaries, causing the ball's y direction to flip.
    {
        const pc_bbox* up_w    = &pc_state.screen_b[1];
        const pc_bbox* down_w  = &pc_state.screen_b[3];
        const pc_bbox* left_w  = &pc_state.screen_b[0];
        const pc_bbox* right_w = &pc_state.screen_b[2];

        if (pc_is_colliding(up_w, &ball->bbox) || pc_is_colliding(down_w, &ball->bbox)) {
            ball->ay *= -1;
        }

        else if (pc_is_colliding(left_w, &ball->bbox) || pc_is_colliding(right_w, &ball->bbox)) {
            // TODO: Score system.
            pc_reset_game();
        }
    }
}

void pc_draw_ball() {
    SDL_SetRenderDrawColor(pc_state.renderer, 255, 255, 255, 255);
    pc_fill_circle(pc_state.game.ball->bbox.x + pc_state.game.ball->bbox.w / 2, pc_state.game.ball->bbox.y + pc_state.game.ball->bbox.h / 2, pc_state.game.ball->radius);
}