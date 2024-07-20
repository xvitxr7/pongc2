#include "player.h"
#include "font.h"
#include "state.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

pc_player* init_player(pc_player_type _player_type, pc_player_input_type _input_type, pc_com_level _com_l)  {
    pc_player* player = (pc_player*) malloc(sizeof(pc_player));
    player->type       = _player_type;
    player->input_type = _input_type;

    player->com_l = _com_l;

    player->index = 0;
    int ww, wh;
    SDL_GetWindowSize(pc_state.window, &ww, &wh);

    player->bbox.x = 0;
    player->bbox.y = 0;

    // The player's width is 15 pixels.
    player->bbox.w = 15;
    // The player height is a third of the window height.
    player->bbox.h = 30 * wh / 100.f;

    return player;
}

pc_player* pc_init_human_player(pc_player_input_type _player_input_t) {
    return init_player(PC_PLAYERTYPE_HUMAN, _player_input_t, 0);
}

pc_player* pc_init_com_player(pc_com_level _com_l) {
    return init_player(PC_PLAYERTYPE_COM, 0, _com_l);
}

void pc_draw_player(const pc_player *player) {
    SDL_SetRenderDrawColor(pc_state.renderer, 255, 255, 255, 255);
    SDL_RenderFillRectF(pc_state.renderer, &player->bbox);

    {
        char scoreText[10];
        sprintf(scoreText, "%i", pc_state.game.teams[player->team]);

        SDL_SetRenderDrawColor(pc_state.renderer, 0, 0, 0, 255);
        pc_draw_text(scoreText, player->bbox.x, player->bbox.y + player->bbox.h / 2, 5 / strlen(scoreText));
    }
}

void pc_player_control(pc_player* player) {
    // You cannot control a computer, unless you're a nerd (a.k.a programmer).
    if (player->type == PC_PLAYERTYPE_COM) return;

    int up_coll, down_coll;
    {
        const pc_bbox* up_w    = &pc_state.window_b[1];
        const pc_bbox* down_w  = &pc_state.window_b[3];

        up_coll   = pc_is_colliding(up_w, &player->bbox);
        down_coll = pc_is_colliding(down_w, &player->bbox);
    }

    const uint8_t* keys = SDL_GetKeyboardState(NULL);
    switch (player->input_type) {
        case PC_PLAYERINPUT_ARROWS:
        {
            if (keys[SDL_SCANCODE_UP] && !up_coll) {
                player->bbox.y -= 7;
            }

            if (keys[SDL_SCANCODE_DOWN] && !down_coll) {
                player->bbox.y += 7;
            }
            break;
        }
        case PC_PLAYERINPUT_MODERN:
        {
            if (keys[SDL_SCANCODE_W] && !up_coll) {
                player->bbox.y -= 7;
            }

            if (keys[SDL_SCANCODE_S] && !down_coll) {
                player->bbox.y += 7;
            }
            break;
        }

        case PC_PLAYERINPUT_MOUSE:
        {
            int my;
            SDL_GetMouseState(NULL, &my);

            player->bbox.y = my - player->bbox.h / 2.f;
            break;
        }
    }
}

void pc_player_com(pc_player* player) {
    pc_ball* ball = pc_state.game.ball;

    if (player->com_l < 0) {
        player->com_l = PC_COMLEVEL_MEDIUM;
        return;
    }
    // At this point, it's easier to just set the player y to be exacly the ball's y.
    else if (player->com_l > 100) {
        player->bbox.y = ball->bbox.y - player->bbox.h / 2.f;
    }

    int up_coll, down_coll;
    {
        const pc_bbox* up_w    = &pc_state.window_b[1];
        const pc_bbox* down_w  = &pc_state.window_b[3];

        up_coll   = pc_is_colliding(up_w, &player->bbox);
        down_coll = pc_is_colliding(down_w, &player->bbox);
    }

    float top_most    = player->bbox.y;
    float bottom_most = player->bbox.y + player->bbox.h;

    if (ball->bbox.y < top_most && !up_coll) {
        player->bbox.y -= player->com_l;
    }

    else if (ball->bbox.y > bottom_most && !down_coll) {
        player->bbox.y += player->com_l;
    }
}
