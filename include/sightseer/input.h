#ifndef SIGHTSEER_INPUT_H
#define SIGHTSEER_INPUT_H

#include <rmath/vec2f.h>

struct input {
	uint8_t left_held : 1;
	uint8_t right_held : 1;
	uint8_t up_held : 1;
	uint8_t down_held : 1;
	uint8_t lshift_held : 1;
	uint8_t padding : 3;
	rm_vec2f mouse_pos_last;
	rm_vec2f mouse_pos_now;
};

void input_get_mouse_delta(struct input i, rm_vec2f out);

#endif
