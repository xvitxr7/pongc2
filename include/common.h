#pragma once

#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define assertm(_exp, _msg) assert(((void)_msg, _exp))

// Bounding box.
typedef SDL_FRect pc_bbox;

static inline int pc_is_colliding(const pc_bbox* bb1, const pc_bbox* bb2) {
    return SDL_HasIntersectionF(bb1, bb2);
}

static inline int pc_is_colliding_bbox_line(const pc_bbox* bb, float x1, float y1, float x2, float y2) {
    return SDL_IntersectFRectAndLine(bb, &x1, &y1, &x2, &y2);
}

static inline float pc_distance(float x1, float y1, float x2, float y2) {
    return sqrt(powf(x2 - x1, 2) + powf(y2 - y1, 2));
}

static inline float pc_distance_bbox(const pc_bbox* bb1, const pc_bbox* bb2) {
    return sqrt(powf(bb2->x - bb2->x, 2) + powf(bb2->y - bb2->y, 2));
}