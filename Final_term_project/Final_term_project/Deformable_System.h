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

	// �ʿ��Ϸ���..
	enum class draw_modes {
		DRAW_MASS_NODES = 0,
		DRAW_SPRINGS = 1,
		DRAW_FACES = 2,
	};

	vector<Node*> nodes;
	vector<Mass_spring*> spring;
	vector<Node*> faces;
	vector<vec3> faces_normal; // face���� normal ����, �� step���� ����
	
	int size_x, size_y, size_z;
	double dx, dy, dz;
	// �� ���� �������� coef
	double structural_coef;
	double shear_coef;
	double bending_coef;
	// �� step�� ��� �ùķ��̼�?
	int iteration_n;

	draw_modes drawmode;

	// ���� �Ʒ� coord cache
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