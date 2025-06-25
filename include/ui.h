#pragma once

#include "common.h"
#include "easing.h"

typedef struct
{
	pc_color background;
	pc_color foreground;
	pc_color accent;
	pc_color hover;
	pc_color click;
} pc_button_colors_t;

typedef struct {
	pc_rect bbox;
	
	float max_w;
	float min_w;
	int clicked;
	int hovered;

	const char* text;
	// Extra text displayed when the user hovers the mouse on top of the button.
	const char* extra;
	
	pc_button_colors_t colors;

	uint32_t font_scale;
	
	float sharpness;

	pc_easing_info_t easing;
} pc_button;

typedef struct
{
	float x, y;

	const char* text;
	// Extra text displayed when the user hovers the mouse on top of the button.
	// Can be null.
	const char* extra;
	
	pc_button_colors_t colors;

	uint32_t font_scale;
	
	float sharpness;

	pc_easing_info_t easing;
} pc_button_info;

typedef struct {
	pc_button* btn_start_game;
	pc_button* btn_extras;
	pc_button* btn_quit;
} pc_mainmenu_t;

pc_button* pc_create_button(pc_button_info* info);

// Draws a dynamic button, that grows when the user hovers up on it.
int pc_ui_button(SDL_Renderer* renderer, pc_button* button);

pc_mainmenu_t* pc_create_mainmenu(SDL_Window* window);

enum pc_mainmenu_return_codes
{
	PC_MAINMENU_NONE,
	PC_MAINMENU_START,
	PC_MAINMENU_EXTRAS,
	PC_MAINMENU_QUIT
};

int pc_ui_mainmenu(SDL_Renderer* renderer, pc_mainmenu_t* menu);