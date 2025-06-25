#include "ui.h"
#include "easing.h"
#include "font.h"
#include <SDL_render.h>
#include <SDL_video.h>
#include <string.h>

pc_button* pc_create_button(pc_button_info* info) {
	pc_button* button = (pc_button*) malloc(sizeof(pc_button));

	if (!button) return button;

	button->bbox.x = info->x;
	button->bbox.y = info->y;

	button->text  = info->text;
	button->extra = info->extra;

	button->font_scale = info->font_scale;

	const int len = pc_text_length(button->text, button->font_scale);

	button->min_w  = len * 2;
	button->bbox.w = button->min_w;
	button->max_w  = pc_text_length(button->extra, button->font_scale) + len * 3 + 100;
	button->bbox.h = info->font_scale * 10;

	memcpy(&button->colors, &info->colors, sizeof(pc_button_colors_t));

	button->sharpness = info->sharpness;

	button->easing = info->easing;
	return button;
}

static int update_button(pc_button* button) {
	int mx, my;
	static int last_mouse_state;
	int mstate = SDL_GetMouseState(&mx, &my);

	pc_rect mouse = { mx, my, 5, 5 };

	int is_mouse_click = (mstate & SDL_BUTTON_LMASK);

	if (SDL_HasIntersectionF(&mouse, &button->bbox)) {
		pc_ease_in(&button->bbox.w, button->max_w, &button->easing);
		button->hovered = 1;
	}
	else {
		pc_ease_out(&button->bbox.w, button->min_w, &button->easing);
		button->hovered = 0;
	}

	if (button->hovered && is_mouse_click)
		button->clicked = 1;
	else
		button->clicked = 0;
	
	return button->clicked;
}

int pc_ui_button(SDL_Renderer* renderer, pc_button* button) {
	SDL_Vertex vertices[4] = {
		{ { button->bbox.x, button->bbox.y }, button->colors.background, { 1, 1 } },
		{ { button->bbox.x + button->bbox.w, button->bbox.y }, button->colors.accent, { 1, 1 } },
		{ { button->bbox.x + button->bbox.w - button->sharpness, button->bbox.y + button->bbox.h }, button->colors.accent, { 1, 1 } },
		{ { button->bbox.x, button->bbox.y + button->bbox.h }, button->colors.background, { 1, 1 } },
	};

	if (button->hovered)
	{
		for (int i = 0; i < 4; ++i)
			vertices[i].color = button->colors.hover;
	}

	if (button->clicked)
	{
		for (int i = 0; i < 4; ++i)
			vertices[i].color = button->colors.click;
	}

	int indices[6] = {
		0, 1, 2,
		0, 2, 3
	};

	SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, 6);

	SDL_SetRenderDrawColor(renderer, button->colors.foreground.r, button->colors.foreground.g, button->colors.foreground.b, button->colors.foreground.a);
	pc_draw_text(button->text, button->bbox.x + 10, button->bbox.y + ((float) button->bbox.h / 2) - ((float) button->font_scale / 2), button->font_scale);

	int is_max_w = button->bbox.w >= button->max_w;
	if (is_max_w)
		pc_draw_text(button->extra, button->bbox.x + pc_text_length(button->text, button->font_scale) * 2, button->bbox.y + ((float) button->bbox.h / 2) - ((float) button->font_scale / 2), button->font_scale);


	return update_button(button);
}

pc_mainmenu_t* pc_create_mainmenu(SDL_Window* window)
{
	pc_mainmenu_t* menu = (pc_mainmenu_t*) malloc(sizeof(pc_mainmenu_t));

	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);

	pc_button_colors_t common_colors = {
		.accent = { 255, 255, 255, 255 }, // white
		.click = { 255, 255, 255, 255 }, // white
		.hover = { 0, 255, 0, 255 }, // green
		.background = { 0, 255, 0, 255 }, // green
		.foreground = { 0, 0, 0, 255 } // black
	};

	pc_easing_info_t easing_info = {
		.multiplier = 5,
		.type = PC_EASING_IN
	};

	{
		pc_button_info info = {
			.x = 0,
			.y = wh / 2,
			"Start game",
			"Starts a new Pong game",
			.colors = common_colors,
			.sharpness = 10,
			.easing = easing_info,
			.font_scale = 5
		};

		menu->btn_start_game = pc_create_button(&info);

		info.y += menu->btn_start_game->bbox.h;
		info.text = "Extras";
		info.extra = "More stuff!";
		info.colors.background.g = 0;
		info.colors.background.b = 255;
		info.colors.hover = info.colors.background;

		menu->btn_extras = pc_create_button(&info);

		info.y += menu->btn_extras->bbox.h;
		info.text = "Quit";
		info.extra = "See you next time!";
		info.colors.background.b = 0;
		info.colors.background.r = 255;
		info.colors.hover = info.colors.background;

		menu->btn_quit = pc_create_button(&info);
	}

	return menu;
}

int pc_ui_mainmenu(SDL_Renderer* renderer, pc_mainmenu_t* menu)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	pc_draw_text("PongC2", 0, 0, 30);

	if (pc_ui_button(renderer, menu->btn_start_game))
		return PC_MAINMENU_START;

	if (pc_ui_button(renderer, menu->btn_extras))
		return PC_MAINMENU_EXTRAS;

	if (pc_ui_button(renderer, menu->btn_quit))
		return PC_MAINMENU_QUIT;

	return PC_MAINMENU_NONE;
}