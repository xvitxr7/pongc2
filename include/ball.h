#pragma once

#include "common.h"
#define PC_BALL_HIT_MULTIPLIER 1.1

typedef struct {
    float radius,
          ax, ay;

    pc_rect bbox;
} pc_ball;

pc_ball* pc_init_ball(float radius);
void pc_update_ball(pc_ball* ball);
void pc_draw_ball();