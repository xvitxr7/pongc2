#include "easing.h"

static void ease_impl(float* v, float t, int type, float mul) {
	switch (type)
	{
		default:
		case PC_EASING_LINEAR:
		*v += mul;
			break;
	}
}

int pc_ease_in(float* v, float t, pc_ease_info* i) {
	if (*v >= t)
		return 0;

	ease_impl(v, t, i->type, i->multiplier);
	return 1;
}

int pc_ease_out(float* v, float t, pc_ease_info* i) {
	if (*v <= t)
		return 0;

	ease_impl(v, t, i->type, -i->multiplier);
	return 1;
}