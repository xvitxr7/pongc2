#include "event.h"
#include "common.h"
#include "state.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <string.h>

static void handle_window_events(SDL_WindowEvent *wevent) {
  switch (wevent->event) {
    case SDL_WINDOWEVENT_RESIZED: {
      pc_update_window_size();
      break;
    }
  }
}

static void handle_key_down(SDL_KeyboardEvent* kevent) {
	if (pc_state.current == PC_GAMESTATE_MAINMENU)
		return;

  	switch (kevent->keysym.sym) {
		case SDLK_ESCAPE: {
			pc_state.current = PC_GAMESTATE_MAINMENU;
		} break;

		/* Increases the ball's velocity */
		case SDLK_EQUALS:
		case SDLK_PLUS:
		case SDLK_KP_PLUS: {
			pc_state.game.ball->ax *= PC_BALL_HIT_MULTIPLIER;
			pc_state.game.ball->ay *= PC_BALL_HIT_MULTIPLIER;
		} break;

		/* Decreases the ball's velocity */
		case SDLK_MINUS:
		case SDLK_KP_MINUS: {
			pc_state.game.ball->ax /= PC_BALL_HIT_MULTIPLIER;
			pc_state.game.ball->ay /= PC_BALL_HIT_MULTIPLIER;
		} break;

		/* Starts the game */
		case SDLK_SPACE: {
			pc_state.game.started = 1;
		} break;

		/* Resets the game to its intitial state */
		case SDLK_r: {
			pc_reset_game();
		} break;

		/* Increases the second player's comlevel (difficulty) (Only if the second player is a PC_PLAYERTYPE_COM) */
		case SDLK_g: {
			pc_state.game.players[1]->com_l++;
		} break;
		
		case SDLK_1: {
			pc_state.bg_color.r += 10;
		} break;
		case SDLK_2: {
			pc_state.bg_color.g += 10;
		} break;
		case SDLK_3: {
			pc_state.bg_color.b += 10;
		} break;
	}
}

static void handle_mouse_click(SDL_MouseButtonEvent* bevent) {

}

static void handle_key_up(SDL_KeyboardEvent* kevent) {
    // Nothing for now.
}

void pc_handle_events() {
  static SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
    case SDL_WINDOWEVENT:     handle_window_events(&ev.window); break;
    case SDL_KEYDOWN:         handle_key_down(&ev.key);         break;
    case SDL_KEYUP:           handle_key_up(&ev.key);           break;
    case SDL_MOUSEBUTTONDOWN: handle_mouse_click(&ev.button);   break;
    // Stops the game loop.
    case SDL_QUIT:        pc_state.running = 0; break;
    }
  }
}