// node class
#ifndef NODE_CPP
#define NODE_CPP

#include "glm/glm.hpp"
#include <vector>

using namespace std;
using namespace glm;

class Node {

public:

	// 현재 위치와 속도
	vec3 position, velocity;
	vec3 old_position; // 직전 위치
	// 현재 가해지는 힘
	vec3 force;
	// 주변 faces들의 normal들
	vector<vec3> faces_normal; 
	// normal vector
	vec3 normal;
	// texture coord
	vec2 tex_coord;
	// 질량
	float mass;
	// 반지름
	float radius;
	float damping_force; // spring뿐만 아니라 NODE에도 둬보자.

	bool isfixed; // position이 고정된 노드인가?
	
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
		// 반지름 임의로..
		radius = 0.05;
	}

	void add_force(vec3 additional_force) {
		force += additional_force;
	}
};

#endif