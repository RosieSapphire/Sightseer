#include <stdio.h>
#include <math.h>

#include "rmath/helpers.h"
#include "rmath/mat4.h"
#include "rmath/vec3f.h"

#include "sightseer/input.h"
#include "sightseer/camera.h"

void camera_get_look_pos(struct camera c, rm_vec3f out)
{
	rm_vec3f look_pos = {
		cosf(c.yaw) * cosf(c.pitch),
		sinf(c.pitch),
		sinf(c.yaw) * cosf(c.pitch),
	};

	rm_vec3f_add(c.eye_pos, look_pos, out);
}

void camera_set_angles_from_look_pos(struct camera *c, rm_vec3f look_pos)
{
	c->pitch = asinf(look_pos[1]);
	c->yaw = atan2f(look_pos[2], look_pos[0]);
}

void camera_get_forward_vec(struct camera c, rm_vec3f out)
{
	rm_vec3f look_pos;

	camera_get_look_pos(c, look_pos);
	rm_vec3f_sub(look_pos, c.eye_pos, out);
	rm_vec3f_normalize(out);
}

void camera_get_right_vec(struct camera c, rm_vec3f out)
{
	rm_vec3f forward_vec;

	camera_get_forward_vec(c, forward_vec);
	rm_vec3f_cross(forward_vec, RM_VEC3F_Y, out);
	rm_vec3f_normalize(out);
}

void camera_get_view_mat4(struct camera c, rm_mat4 out)
{
	rm_vec3f look_pos;

	camera_get_look_pos(c, look_pos);
	rm_mat4_look_at(c.eye_pos, look_pos, out);
	camera_get_forward_vec(c, look_pos);
}

void camera_update_rotation(struct camera *c, float sens, struct input i)
{
	rm_vec2f mouse_delta;
	input_get_mouse_delta(i, mouse_delta);

	c->yaw += mouse_delta[0] * sens;
	c->pitch += mouse_delta[1] * sens;
}

void camera_update_position(struct camera *c, float dt, struct input i)
{
	float move_speed = RM_PI * dt;

	if(i.lshift_held) {
		move_speed *= 2;
	}

	float forward_move = i.down_held - i.up_held;
	float right_move = i.left_held - i.right_held;
	rm_vec3f forward_vec;
	rm_vec3f right_vec;
	rm_vec3f move_vec;

	camera_get_forward_vec(*c, forward_vec);
	camera_get_right_vec(*c, right_vec);
	rm_vec3f_scale(forward_vec, forward_move);
	rm_vec3f_scale(right_vec, right_move);

	rm_vec3f_add(forward_vec, right_vec, move_vec);
	rm_vec3f_normalize(move_vec);
	rm_vec3f_scale(move_vec, move_speed);
	rm_vec3f_add(c->eye_pos, move_vec, c->eye_pos);
}
