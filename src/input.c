#include "rmath/vec2f.h"
#include "sightseer/input.h"

void input_get_mouse_delta(struct input i, rm_vec2f out)
{
	rm_vec2f_sub(i.mouse_pos_now, i.mouse_pos_last, out);
}
