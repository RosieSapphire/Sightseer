#include <stdio.h>
#include "rmath/vec3f.h"
#include "sightseer/camera.h"
#include "sightseer/input.h"

int main()
{
	struct camera cam = {{0, 0, 0}, 0, 0};
	rm_vec3f focus = {0, 1, 3};

	rm_vec3f_normalize(focus);
	camera_set_angles_from_look_pos(&cam, focus);
	camera_get_look_pos(cam, focus);

	printf("Cam Pos: %f, %f, %f\n", cam.eye_pos[0],
			cam.eye_pos[1], cam.eye_pos[2]);
	printf("Cam Pitch and Yaw: %f, %f\n", cam.pitch, cam.yaw);
	printf("Cam Focus: %f, %f, %f\n", focus[0], focus[1], focus[2]);

	return 0;
}
