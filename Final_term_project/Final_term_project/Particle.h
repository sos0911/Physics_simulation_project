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
	// �ٿ���� �ڽ� �� �� ����
	float LENGTH = 30;
	// ���� ������
	float RADIUS = 0.5f;
	float Particles_radius; // ��ƼŬ �ý��� �ݰ�
	// ���� �ִ� ���� ���ɽð�
	float maxlifetime;
	// ���� �����ð�(����� �ð�)
	float lifetime;
	int mass = 1;
	vec3 velocity, position;
	vec3 ps_center_pos; // ��ƼŬ �ý��� �߽���
	void init(vec3 center_pos, int _MIN_INIT_VELOCITY, int _MAX_INIT_VELOCITY, int _LENGTH, float _RADIUS, int _mass);
	float rand_float();
	float rand_zero_center_float();

	// euler
	void Movement(float dt, vec3 force);
	void Collision_Boundary(); 
};

#endif