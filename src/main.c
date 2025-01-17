#include "ball.h"
#include "event.h"
#include "font.h"
#include "player.h"
#include "state.h"
#include "ui.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

struct pc_state_t pc_state;

pc_rect    r = { 0, 0, 10, 30 };
pc_color   white = { 255, 255, 255, 255 };
pc_color   red = { 255, 0, 0, 255 };
pc_color   green = { 0, 255, 0, 255 };
pc_color   blue = { 0, 0, 255, 255 };
pc_button* button;

static void draw_middle_lines(int w, int h) {
  int ww, wh;
  SDL_GetWindowSize(pc_state.window, &ww, &wh);
  for (int y = 0; y < wh; y++) {
    if (y % 2 == 1) continue;
    SDL_Rect r;
    r.w = w;
    r.h = h;
    r.x = ww / 2 - w / 2;
    r.y = y * h;

    SDL_SetRenderDrawColor(pc_state.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(pc_state.renderer, &r);
  }
}

static void draw_bboxes() {
  for (int i = 0; i <= pc_state.game.players_idx; i++) {
    pc_player *player = pc_state.game.players[i];

    SDL_SetRenderDrawColor(pc_state.renderer, 255, 0, 0, 255);
    SDL_RenderDrawRectF(pc_state.renderer, &player->bbox);
  }

  SDL_RenderDrawRectF(pc_state.renderer, &pc_state.game.ball->bbox);
  
  for (int i = 0; i < 4; i++) {
    const pc_rect* bbox = &pc_state.window_b[i];
    SDL_SetRenderDrawColor(pc_state.renderer, 0, 0, 255, 255);
    SDL_RenderDrawRectF(pc_state.renderer, bbox);
  }
}

static void draw_players() {
  for (int i = 0; i <= pc_state.game.players_idx; i++) {
    pc_player *player = pc_state.game.players[i];
    if (!player) continue;
    pc_draw_player(player);
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

static const char* help_text = "ESC - Quits the game.\n"
                               "X   - Locks the ball to the mouse position.\n"
                               "R   - Resets the game state.";

static void render() {

  SDL_SetRenderDrawColor(pc_state.renderer, pc_state.bg_color.r, pc_state.bg_color.g, pc_state.bg_color.b, pc_state.bg_color.a);
  SDL_RenderClear(pc_state.renderer);
  
  draw_middle_lines(10, 20);

  SDL_SetRenderDrawColor(pc_state.renderer, pc_state.bg_color.r + 255, pc_state.bg_color.g + 255, pc_state.bg_color.b + 255, pc_state.bg_color.a);
  pc_draw_text("! PongC2 - made by @xvitxr7 !", 10, 10, 2);
  
  {
    int ww, wh;
    SDL_GetWindowSize(pc_state.window, &ww, &wh);
    SDL_SetRenderDrawColor(pc_state.renderer, pc_state.bg_color.r + 10, pc_state.bg_color.g + 10, pc_state.bg_color.b + 10, pc_state.bg_color.a);
    pc_draw_text(help_text, ww / 2 + 10, wh - 50, 2);
  }

  pc_draw_ball();
  // Draw the players.
  draw_players();

  if (pc_ui_button(pc_state.renderer, button)) {
      printf("PEIDEI\n");
  }

  if (pc_state.flags[PC_FLAG_DRAW_BBOXES])
    draw_bboxes();

  SDL_RenderPresent(pc_state.renderer);
}

static void update() {
  for (int i = 0; i < PC_PLAYER_LIMIT; i++) {
    update_player(pc_state.game.players[i]);
  }

  if (pc_state.game.started == 1)
    pc_update_ball(pc_state.game.ball);
}

static void run() {
  pc_state.running = 1;

  pc_ease_info* easing = (pc_ease_info*) malloc(sizeof(pc_ease_info));
  easing->multiplier = 10.f;
  easing->type = PC_EASING_IN;

  button = pc_create_button(r, "click this button", "extra stuff here", red, red, 3, 10, easing);

  while (pc_state.running) {
    pc_handle_events();

    update();
    render();
  }
}

#undef main
int main(int argc, char **argv) {
  pc_init(argc, argv);
  run();
  pc_quit();

  return 0;
}
