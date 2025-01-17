#include "ui.h"
#include "font.h"

pc_button* pc_create_button(pc_rect r, const char* text, const char* extra, pc_color color, pc_color accent, uint32_t font_scale, float sharpness, pc_ease_info* ease) {
	pc_button* button = (pc_button*) malloc(sizeof(pc_button));

	if (!button) return button;

	button->bbox = r;

	button->text  = text;
	button->extra = extra;

	button->font_scale = font_scale;

	button->min_w  = pc_text_length(button->text, button->font_scale) + 20;
	button->bbox.w = button->min_w;
	button->max_w  = button->bbox.w + pc_text_length(button->extra, button->font_scale);
	button->bbox.h = r.h;

	button->color  = color;
	button->accent = accent;

	button->sharpness = sharpness;

	if (ease)
		button->easing = *ease;
	else {
		button->easing.type       = PC_EASING_LINEAR;
		button->easing.multiplier = 10;
	}

	return button;
}

static int update_button(pc_button* button) {
	int mx, my;
	static int last_mouse_state;
	int mstate = SDL_GetMouseState(&mx, &my);

	pc_rect mouse = { mx, my, 5, 5 };

	int hovering = 0;
	int is_mouse_click = (mstate & SDL_BUTTON_LMASK);

	if (SDL_HasIntersectionF(&mouse, &button->bbox)) {
		pc_ease_in(&button->bbox.w, button->max_w, &button->easing);
		hovering = 1;
	}
	else {
		pc_ease_out(&button->bbox.w, button->min_w, &button->easing);
		hovering = 0;
	}

	if (!hovering)
		button->clicked = hovering && is_mouse_click;
	else
		button->clicked = 0;
	
	return button->clicked;
}

int pc_ui_button(SDL_Renderer* renderer, pc_button* button) {
	SDL_Vertex vertices[4] = {
		{ { button->bbox.x, button->bbox.y }, button->color, { 1, 1 } },
		{ { button->bbox.x + button->bbox.w, button->bbox.y }, button->accent, { 1, 1 } },
		{ { button->bbox.x + button->bbox.w - button->sharpness, button->bbox.y + button->bbox.h }, button->accent, { 1, 1 } },
		{ { button->bbox.x, button->bbox.y + button->bbox.h }, button->color, { 1, 1 } },
	};

	int indices[6] = {
		0, 1, 2,
		0, 2, 3
	};

	SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, 6);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	pc_draw_text(button->text, button->bbox.x + 10, button->bbox.y + button->bbox.h / 2 - button->font_scale / 2, button->font_scale);

	return update_button(button);
}