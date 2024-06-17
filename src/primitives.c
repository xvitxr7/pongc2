#include "primitives.h"
#include "state.h"

void pc_init_rect_from_sdl(const SDL_FRect* src, pc_rect* target) {
    target->x = src->x;
    target->y = src->y;
    target->w = src->w;
    target->h = src->h;
}

void pc_fill_circle(int32_t _cx, int32_t _cy, int32_t radius) {
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(pc_state.renderer, _cx + dx, _cy + dy);
            }
        }
    }
}