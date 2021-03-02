#ifndef Particle_System_h
#define Particle_System_h

#include "Box2D/Box2D.h"
#include "Particle.h"
#include "GL/freeglut.h"
#include <vector>

using namespace std;

class ParticleSystem {
public:

	vector<particle> particles;
	vec3 gravity_point;
	// ��ƼŬ�� ��ġ�� ���� ������(����).
	vec3 center_pos = vec3(0,0,0); 
	// ��ƼŬ�� ������ �ݰ�
	float radius;

	void init(int num_of_particle, vec3 _center_pos, float _radius);
	void set_gravity(vec3 gravity);
	void draw();

	void Movement(float time);
	void Collision(); // hash grid ��� ����
	void DeleteoldParticles();
	void MakenewParticles(int numpertime);
};

#endif