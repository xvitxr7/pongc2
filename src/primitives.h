#pragma once

#include "common.h"

typedef struct {
    float x, y, w, h;
} pc_rect;

typedef struct {
    float radius, x, y;
} pc_circle;

void pc_init_rect_from_sdl(const SDL_FRect* src, pc_rect* target);

void pc_fill_circle(int32_t _cx, int32_t _cy, int32_t radius);