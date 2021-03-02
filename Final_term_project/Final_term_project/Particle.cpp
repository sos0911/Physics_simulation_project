#include "Particle.h"

void particle::init(vec3 center_pos, int _MIN_INIT_VELOCITY, int _MAX_INIT_VELOCITY, int _LENGTH, float _RADIUS, int _mass){

	ps_center_pos = center_pos;
	MIN_INIT_VELOCITY = _MIN_INIT_VELOCITY;
	MAX_INIT_VELOCITY = _MAX_INIT_VELOCITY;
	LENGTH = _LENGTH;
	RADIUS = _RADIUS;
	mass = _mass;
	Particles_radius = _LENGTH;

	// �ð� ����
	maxlifetime = (float)(rand() % 10) + 5;
	lifetime = 0.0f;
	// firework simulation
	// center_pos �������� ���� ����
	// �ʱ� ������ ���� ����� ���¿��� random ����
	// ���� �ּ� �ӵ��� �ִ� �ӵ� ����

	// ���� ���� ����
	vec3 dir(rand_zero_center_float(), 0, rand_zero_center_float());
	vec3 temp = normalize(dir);
	dir = temp;
	dir *= rand_zero_center_float() * Particles_radius;

	position = ps_center_pos + dir;

	float diff = sqrt(pow(center_pos.x - position.x, 2) + pow(center_pos.z - position.z, 2));

	float x = (rand_zero_center_float() * (MAX_INIT_VELOCITY - MIN_INIT_VELOCITY) + MIN_INIT_VELOCITY)/3;
	float y = (rand_zero_center_float() * (MAX_INIT_VELOCITY - MIN_INIT_VELOCITY + diff) + MIN_INIT_VELOCITY);
	float z = (rand_zero_center_float() * (MAX_INIT_VELOCITY - MIN_INIT_VELOCITY) + MIN_INIT_VELOCITY)/3;

	velocity = vec3(x, y, z);
}

float particle::rand_float() {
	// ��ȯ �� : 0 ~ 1
	float value = rand() / float(RAND_MAX);
	return value;
}

float particle::rand_zero_center_float() {
	// ��ȯ �� : -1 ~ 1
	float value = (rand() - (RAND_MAX + 1) / 2) / float(RAND_MAX + 1);
	return value;
}

void particle::Movement(float dt, vec3 force) {
	vec3 acc = force / (float)mass;
	velocity += acc * dt;
	position += velocity * dt;

	lifetime += dt;
}

void particle::Collision_Boundary() {
	// �ٿ������ ��ƼŬ �� �浹 ó��
	// ������ �ٿ������ ���� ���� ���� ���� �ѵ�..
	// TODO : stuck ? -> ��� dot.product�� �־�� �ϳ�..
	float COR = 0.1f;
	if (position.x <= -LENGTH + RADIUS + ps_center_pos.x && dot(vec3(1,0,0), velocity) < 0) {
		position.x = -LENGTH + RADIUS;
		velocity.x *= (-1.0f) * COR;
	}
	if (position.x >= LENGTH - RADIUS + ps_center_pos.x && dot(vec3(-1, 0, 0), velocity) < 0) {
		position.x = LENGTH - RADIUS;
		velocity.x *= (-1.0f) * COR;
	}
	if (position.y <= -LENGTH + RADIUS + ps_center_pos.y && dot(vec3(0, 1, 0), velocity) < 0) {
		position.y = -LENGTH + RADIUS;
		velocity.y *= (-1.0f) * COR;
	}
	if (position.y >= LENGTH - RADIUS + ps_center_pos.y && dot(vec3(0, -1, 0), velocity) < 0) {
		position.y = LENGTH - RADIUS;
		velocity.y *= (-1.0f) * COR;
	}
	if (position.z <= -LENGTH + RADIUS + ps_center_pos.z && dot(vec3(0, 0, 1), velocity) < 0) {
		position.z = -LENGTH + RADIUS;
		velocity.z *= (-1.0f) * COR;
	}
	if (position.z >= LENGTH - RADIUS + ps_center_pos.z && dot(vec3(0, 0, -1), velocity) < 0) {
		position.z = LENGTH - RADIUS;
		velocity.z *= (-1.0f) * COR;
	}
}