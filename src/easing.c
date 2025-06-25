#include "easing.h"
#include <math.h>
#include <stdio.h>

static void ease_impl(float* v, float t, int type, float mul, float* index) {
	float delta = (t - *v) + 20;

	switch (type)
	{
		default:
		case PC_EASING_LINEAR:
		*v += mul;
			break;

		case PC_EASING_IN:
			*index += 0.5;
			*v += pow(sin((M_PI * *index) / t) * delta, 2) * mul; // thank you desmos for being so incredibly useful for stuff like this
			break;
	}
}

int pc_ease_in(float* v, float t, pc_easing_info_t* i) {
	if (*v >= t)
	{
		i->index = 0;
		return 0;
	}

	if (i->multiplier < 0)
	{
		i->multiplier *= -1;
		i->index = 0;
	}

	ease_impl(v, t, i->type, i->multiplier, &i->index);
	return 1;
}

int pc_ease_out(float* v, float t, pc_easing_info_t* i) {
	if (*v <= t)
	{
		i->index = 0;
		return 0;
	}

	if (i->multiplier > 0)
	{
		i->multiplier *= -1;
		i->index = 0;
	}

	ease_impl(v, t, i->type, i->multiplier, &i->index);
	return 1;
}