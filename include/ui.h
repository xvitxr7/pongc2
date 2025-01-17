#pragma once

#include "common.h"
#include "easing.h"

typedef struct {
	pc_rect bbox;
	
	float max_w;
	float min_w;
	int clicked;

	const char* text;
	// Extra text displayed when the user hovers the mouse on top of the button.
	const char* extra;
	
	pc_color color;
	pc_color accent;

	uint32_t font_scale;
	
	float sharpness;

	pc_ease_info easing;
} pc_button;

pc_button* pc_create_button(
	pc_rect       r,
	const char*   text,
	const char*   extra,
	pc_color      color,
	pc_color      accent,
	uint32_t      font_scale,
	float         sharpness,
	pc_ease_info* ease
);

// Draws a dynamic button, that grows when the user hovers up on it.
int pc_ui_button(SDL_Renderer* renderer, pc_button* button);