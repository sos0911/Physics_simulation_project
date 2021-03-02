#ifndef PARTICLE_CPP
#define PARTICLE_CPP
#include "glm/glm.hpp"
#include <random>
#include <iostream>
#include <windows.h>
#include <iostream>

using namespace glm;
using namespace std;

class particle {

public:

	int MIN_INIT_VELOCITY;
	int MAX_INIT_VELOCITY;
	// 바운더리 박스 한 변 길이
	float LENGTH = 30;
	// 입자 반지름
	float RADIUS = 0.5f;
	float Particles_radius; // 파티클 시스템 반경
	// 입자 최대 생존 가능시간
	float maxlifetime;
	// 입자 생존시간(경과한 시간)
	float lifetime;
	int mass = 1;
	vec3 velocity, position;
	vec3 ps_center_pos; // 파티클 시스템 중심점
	void init(vec3 center_pos, int _MIN_INIT_VELOCITY, int _MAX_INIT_VELOCITY, int _LENGTH, float _RADIUS, int _mass);
	float rand_float();
	float rand_zero_center_float();

	// euler
	void Movement(float dt, vec3 force);
	void Collision_Boundary(); 
};

#endif