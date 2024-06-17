#pragma once

#include "common.h"
#include "primitives.h"
#include <stdint.h>

typedef enum {
    PC_PLAYERINPUT_ARROWS,
    PC_PLAYERINPUT_MODERN,
    PC_PLAYERINPUT_MOUSE
} pc_player_input_type;

typedef enum {
    PC_PLAYERTYPE_HUMAN,
    PC_PLAYERTYPE_COM
} pc_player_type;

typedef float pc_com_level;
#define PC_COMLEVEL_EASY   7
#define PC_COMLEVEL_MEDIUM 13
#define PC_COMLEVEL_HARD   19
#define PC_COMLEVEL_IMP    INT32_MAX // 🤓

typedef enum {
    PC_TEAM_LEFT,
    PC_TEAM_RIGHT
} pc_teams;

typedef struct {
    uint8_t   index;
    pc_bbox bbox;

    pc_teams team;

    pc_player_type type;
    pc_player_input_type input_type;

    // Computer A.I level.
    pc_com_level com_l;
} pc_player;

pc_player* pc_init_human_player(pc_player_input_type);
pc_player* pc_init_com_player(pc_com_level);
void pc_draw_player(const pc_player*);
void pc_adjust_player_position(pc_player*);

void pc_player_control(pc_player*);
void pc_player_com(pc_player*);