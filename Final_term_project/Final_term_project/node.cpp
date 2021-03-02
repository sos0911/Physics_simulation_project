// node class
#ifndef NODE_CPP
#define NODE_CPP

#include "glm/glm.hpp"
#include <vector>

using namespace std;
using namespace glm;

class Node {

public:

	// ���� ��ġ�� �ӵ�
	vec3 position, velocity;
	vec3 old_position; // ���� ��ġ
	// ���� �������� ��
	vec3 force;
	// �ֺ� faces���� normal��
	vector<vec3> faces_normal; 
	// normal vector
	vec3 normal;
	// texture coord
	vec2 tex_coord;
	// ����
	float mass;
	// ������
	float radius;
	float damping_force; // spring�Ӹ� �ƴ϶� NODE���� �ֺ���.

	bool isfixed; // position�� ������ ����ΰ�?
	
	Node(vec3 _pos, vec3 _normal, vec2 _tex_coord, bool _isfixed) {
		position = _pos;
		old_position = _pos;
		isfixed = _isfixed;
		velocity = vec3(0, 0, 0);
		force = vec3(0, 0, 0);
		normal = _normal;
		tex_coord = _tex_coord;
		mass = 100;
		damping_force = 0.7;
		// ������ ���Ƿ�..
		radius = 0.05;
	}

	void add_force(vec3 additional_force) {
		force += additional_force;
	}
};

#endif