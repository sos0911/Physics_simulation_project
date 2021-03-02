#ifndef Simulator_h
#define Simulator_h

#include "Particle_System.h"
#include "glm/glm.hpp"
#include "Deformable_System.h"
#include "Sphere.cpp"
#include <iostream>
#define NUMBER_OF_PARTICLE 10000
#define GL_PI 3.1415f

using namespace glm;

class Simulator{

	// pobj 선언
	GLUquadric* pobj = gluNewQuadric();

	float table_size[3] = { 300,10,300}; // size(x쪽, y쪽, z쪽)
	float table_middle_coord[3] = { 0,0,0 }; // 중심 좌표(x,y,z)
	float timestep;

	// ground
	vec3 ground;
	// particle system cache
	ParticleSystem* fireworks;
	// cloth system cache
	mass_cloth* cloth;
	// sphere cache
	sphere* sp;
	// texture coord cache
	int width, height;
	// Ring radius, thick cache
	float ring_radius = table_size[1] / 2;
	float ring_thick = table_size[0] / 24;

	public:
		float* get_table_size();
		float* get_table_coord();

		void Initialize(int width, int height);
		void Lighting();
		void Update(bool interactionmode[2]);
		void Render();
		
		void DrawTable(float w, float h, float t, float x, float y, float z);
		void DrawDisk(float inner, float outer, int slices, int loops);
		void DrawRing(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h, GLfloat thick);
		void DrawSphere();
};

#endif