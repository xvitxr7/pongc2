#include "ball.h"
#include "player.h"
#include "state.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string.h>

#define PC_HAS_OPT(str, opt) strcmp(str, opt) > 0

struct pc_state_t pc_state;

static void draw_bboxes() {
  for (int i = 0; i <= pc_state.game.players_idx; i++) {
    pc_player *player = pc_state.game.players[i];

    if (pc_state.flags.draw_bb) {
      SDL_SetRenderDrawColor(pc_state.renderer, 255, 0, 0, 255);
      SDL_RenderDrawRectF(pc_state.renderer, &player->bbox);
    }
  }

  SDL_RenderDrawRectF(pc_state.renderer, &pc_state.game.ball->bbox);

  for (int i = 0; i < 4; i++) {
    const pc_bbox *bbox = &pc_state.screen_b[i];
    SDL_SetRenderDrawColor(pc_state.renderer, 0, 0, 255, 255);
    SDL_RenderDrawRectF(pc_state.renderer, bbox);
  }
}

static void draw_players() {
  for (int i = 0; i <= pc_state.game.players_idx; i++) {
    pc_player *player = pc_state.game.players[i];
    if (!player)
      continue;
    pc_draw_player(player);
  }
}

static void handle_window_events(SDL_WindowEvent *wevent) {
  switch (wevent->event) {
  case SDL_WINDOWEVENT_RESIZED: {
    pc_update_window_size();
    break;
  }
  }
}

static void handle_key_down(SDL_KeyboardEvent *kevent) {
  switch (kevent->keysym.sym) {
  case SDLK_ESCAPE:
    pc_state.running = 0;
    break;

  case SDLK_EQUALS:
  case SDLK_PLUS:
  case SDLK_KP_PLUS: {
    pc_state.game.ball->ax *= PC_BALL_HIT_MULTIPLIER;
    pc_state.game.ball->ay *= PC_BALL_HIT_MULTIPLIER;
  } break;

  case SDLK_MINUS:
  case SDLK_KP_MINUS: {
    pc_state.game.ball->ax /= PC_BALL_HIT_MULTIPLIER;
    pc_state.game.ball->ay /= PC_BALL_HIT_MULTIPLIER;
  } break;

  case SDLK_SPACE: {
    pc_state.game.started = 1;
  } break;

  case SDLK_r: {
    pc_reset_game();
  } break;

  case SDLK_g: {
    pc_state.game.players[1]->com_l++;
  } break;

  }
}

static void handle_key_up(SDL_KeyboardEvent *kevent) {}

static void handle_events() {
  static SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
    case SDL_WINDOWEVENT: handle_window_events(&ev.window); break;
    case SDL_KEYDOWN:     handle_key_down(&ev.key); break;
    case SDL_KEYUP:       handle_key_up(&ev.key); break;
    // Stops the game loop.
    case SDL_QUIT:        pc_state.running = 0; break;
    }
  }
}

static void update_player(pc_player *player) {
  switch (player->type) {
  case PC_PLAYERTYPE_HUMAN:
    pc_player_control(player);
    break;
  case PC_PLAYERTYPE_COM:
    pc_player_com(player);
    break;
  }
}

static void run() {
  pc_state.running = 1;

  while (pc_state.running) {
    handle_events();

    for (int i = 0; i < PC_PLAYER_LIMIT; i++) {
      update_player(pc_state.game.players[i]);
    }

    if (pc_state.game.started == 1)
      pc_update_ball(pc_state.game.ball);

    SDL_SetRenderDrawColor(pc_state.renderer, 25, 0, 100, 255);
    SDL_RenderClear(pc_state.renderer);

    pc_draw_ball();
    // Draw the players.
    draw_players();

    if (pc_state.flags.draw_bb)
      draw_bboxes();

    SDL_RenderPresent(pc_state.renderer);
  }
}

static void process_opts(int argc, char **argv) {
  for (int i = 0; i < argc; i++) {
    if (PC_HAS_OPT(argv[i], "--draw-bboxes")) {
      pc_state.flags.draw_bb = 1;
    }
  }
}

int main(int argc, char **argv) {
  process_opts(argc, argv);

  pc_init();
  run();
  pc_quit();

  return 0;
}