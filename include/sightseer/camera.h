#ifndef SIGHTSEER_CAMERA_H
#define SIGHTSEER_CAMERA_H

#include <rmath/mat4.h>
#include "sightseer/input.h"

struct camera {
	rm_vec3f eye_pos;
	float yaw, pitch;
};

void camera_get_look_pos(struct camera c, rm_vec3f out);
void camera_set_angles_from_look_pos(struct camera *c, rm_vec3f look_pos);
void camera_get_forward_vec(struct camera c, rm_vec3f out);
void camera_get_right_vec(struct camera c, rm_vec3f out);
void camera_get_view_mat4(struct camera c, rm_mat4 out);
void camera_update_rotation(struct camera *c, float sens, struct input i);
void camera_update_position(struct camera *c, float dt, struct input i);

#endif
