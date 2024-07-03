#include "ball.h"
#include "common.h"
#include "player.h"
#include "state.h"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <stdint.h>

#include <math.h>
#include <stdlib.h>

pc_ball* pc_init_ball(float radius) {
    pc_ball* ball = (pc_ball*) malloc(sizeof(pc_ball));

    int direction = (rand() % 14) - 7;
    ball->ax = direction;
    ball->ay = (direction % 2 == 0 ? 1 : -1) * direction;

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

        if ((p->team == PC_TEAM_RIGHT && ball->ax > 0) || (p->team == PC_TEAM_LEFT && ball->ax < 0)) {
            pd = p;
        }
    }

    if (!pd) return;

    float player_x1 = pd->team == PC_TEAM_LEFT ? pd->bbox.x + pd->bbox.w : pd->bbox.x;
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

        int score = (pc_is_colliding(left_w, &ball->bbox) || pc_is_colliding(right_w, &ball->bbox)) ||
                    (ball->bbox.x > right_w->x || ball->bbox.x < 0);

        if (pc_is_colliding(up_w, &ball->bbox) || pc_is_colliding(down_w, &ball->bbox)) {
            ball->ay *= -1;
        }

        else if (score) {
            pc_teams team = pd->team == PC_TEAM_LEFT ? PC_TEAM_RIGHT : PC_TEAM_LEFT;
            pc_state.game.teams[team]++;
            pc_reset_game();
            printf("Player [%i] scored! [%ix%i]\n", pd->index, pc_state.game.teams[0], pc_state.game.teams[1]);
        }
    }

    {
        int mx, my;
        uint32_t button = SDL_GetMouseState(&mx, &my);

        pc_bbox mouse;
        mouse.w = 10;
        mouse.h = 10;
        mouse.x = mx;
        mouse.y = my;

        if (pc_is_colliding(&mouse, &pc_state.game.ball->bbox) && SDL_BUTTON(button) == SDL_BUTTON_LEFT) {
            pc_state.game.ball->bbox.x = mouse.x - pc_state.game.ball->bbox.w / 2.f;
            pc_state.game.ball->bbox.y = mouse.y - pc_state.game.ball->bbox.h / 2.f;
        }
    }
}

static void fill_circle(int32_t _cx, int32_t _cy, int32_t radius) {
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(pc_state.renderer, _cx + dx, _cy + dy);
            }
        }
    }
}

void pc_draw_ball() {
    SDL_SetRenderDrawColor(pc_state.renderer, 255, 255, 255, 255);
    fill_circle(pc_state.game.ball->bbox.x + pc_state.game.ball->bbox.w / 2, pc_state.game.ball->bbox.y + pc_state.game.ball->bbox.h / 2, pc_state.game.ball->radius);
}