#pragma once

enum pc_easing {
	PC_EASING_LINEAR,
	PC_EASING_IN,
	PC_EASING_OUT
};

typedef struct {
	int   type;
	float index;
	float multiplier;
} pc_easing_info_t;

// For increasing values.
int pc_ease_in(float* v, float t, pc_easing_info_t* i);
// For decreasing values.
int pc_ease_out(float* v, float t, pc_easing_info_t* i);