#ifndef Deformable_System_h
#define Deformable_System_h

#include "GL/freeglut.h"
#include <vector>
#include "node.cpp"
#include <iostream>
#include "Mass_spring.cpp"

using namespace std;

class mass_cloth{
public:

	// 필요하려나..
	enum class draw_modes {
		DRAW_MASS_NODES = 0,
		DRAW_SPRINGS = 1,
		DRAW_FACES = 2,
	};

	vector<Node*> nodes;
	vector<Mass_spring*> spring;
	vector<Node*> faces;
	vector<vec3> faces_normal; // face들의 normal 저장, 매 step마다 갱신
	
	int size_x, size_y, size_z;
	double dx, dy, dz;
	// 각 종류 스프링의 coef
	double structural_coef;
	double shear_coef;
	double bending_coef;
	// 한 step당 몇번 시뮬레이션?
	int iteration_n;

	draw_modes drawmode;

	// 왼쪽 아래 coord cache
	vec3 start_coord;

	// methods
	void init(int x, int y, int z, int tex_width, int tex_height);
	int Findindex(int x, int y, int z);
	bool boundary_check(int x, int y, int z);

	void compute_force(double dt, vec3 ext_force);
	void integrate(double dt);
	void collision_response(vec3 ground);
	void computeNormal();

	// render
	void draw(int width, int height);
	void RenderFace(int width, int height);

};

#endif