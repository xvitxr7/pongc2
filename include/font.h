#pragma once

#include "common.h"

#define PC_CHAR_COUNT 255

struct pc_font {
    const char* chars[PC_CHAR_COUNT];
    struct {
        uint8_t w, h;
    } indices[PC_CHAR_COUNT];
};

// PongSans Font™
extern struct pc_font pc_pong_sans;

void pc_init_font();
void pc_draw_text(const char* _text, float _x, float _y, uint32_t _scale);