// mass spring class
#ifndef MASS_SPRING_CPP
#define MASS_SPRING_CPP
#include "Node.cpp"
#include <iostream>

using namespace std;

class Mass_spring {
public:
	// 각 두 노드
	Node* a;
	Node* b;
	float spring_coef; // 스프링 계수
	float des_length; // 원래 길이
	float dampling_force; // dampling force
	
	Mass_spring(Node* _a, Node* _b, float _spring_coef, float _des_length) {
		a = _a;
		b = _b;
		spring_coef = _spring_coef;
		des_length = _des_length;
		dampling_force = 0.01;
	}

	void internal_force(double dt) {
		// spring force + damping force
		// 그 후 각 연결된 노드에 힘 전달.
		vec3 force = normalize(a->position - b->position) * (spring_coef * (length(a->position - b->position) - des_length) + dampling_force * dot((a->velocity - b->velocity), (normalize(a->position - b->position))));
		a->add_force(-force);
		b->add_force(force);
		// dt는 안 써도 되나..?
	}
};

#endif