#include "Particle_System.h"

void ParticleSystem::init(int num_of_particle, vec3 _center_pos, float _radius) {
	center_pos = _center_pos;
	radius = _radius;
	particles.clear();
	for (int i = 0; i < num_of_particle; i++) {
		particle temp;
		particles.push_back(temp);
	}

	//랜덤 시드값
	srand((unsigned int)time(0));

	for (int i = 0; i < particles.size(); i++) {
		particles[i].init(center_pos, 1, 7, radius * 3, 1.0f, 1);
	}
}

void ParticleSystem::set_gravity(vec3 gravity) {
	gravity_point = gravity;
}

void ParticleSystem::Movement(float time) {
	// 입자 움직임 구현
	for (int i = 0; i < particles.size(); i++) {
		//vec3 force = vec3(0,0,0);
		vec3 force = gravity_point / (float)50;
		particles[i].Movement(time, force);
	}
}

void ParticleSystem::Collision() {
	// 충돌처리 구현
	for (int i = 0; i < particles.size(); i++) {
		particles[i].Collision_Boundary();
		// TODO : 파티클 간의 충돌
	}
}

void ParticleSystem::draw() {
	glPushMatrix();

	// TODO : particle draw
	glEnable(GL_POINT_SMOOTH);

	glEnable(GL_BLEND);                 // Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   // Type Of Blending To Perform

	for (int i = 0; i < particles.size(); i++) {
		vec3 pos = particles[i].position;
		// color : red
		vec3 color = vec3(1, 0, 0);
		glColor3f(color.x, color.y, color.z);
		glPointSize(1.0f);

		glBegin(GL_POINTS);
		vec3 light_pos(150.0, 151.0, 150.0);
		vec3 normal = normalize(light_pos - pos);
		glVertex3f(pos.x, pos.y, pos.z);
		glNormal3f(normal.x, normal.y, normal.z);
		glEnd();
	}

	glDisable(GL_BLEND);

	glPopMatrix();
}

void ParticleSystem::DeleteoldParticles() {
	// 오래된 파티클 제거
	for (auto itr = particles.begin(); itr != particles.end();) {
		if (itr->lifetime > itr->maxlifetime)
			itr = particles.erase(itr);
		else
			itr++;
	}
}

void ParticleSystem::MakenewParticles(int numpertime) {
	// 새로운 파티클 생성
	// 어느 빈도로?
	for (int i = 0; i < numpertime; i++) {
		particle temp;
		particles.push_back(temp);
		temp.init(center_pos, 1, 7, radius * 3, 1.0f, 1);
	}
}