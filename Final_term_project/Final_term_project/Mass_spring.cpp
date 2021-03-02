// mass spring class
#ifndef MASS_SPRING_CPP
#define MASS_SPRING_CPP
#include "Node.cpp"
#include <iostream>

using namespace std;

class Mass_spring {
public:
	// �� �� ���
	Node* a;
	Node* b;
	float spring_coef; // ������ ���
	float des_length; // ���� ����
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
		// �� �� �� ����� ��忡 �� ����.
		vec3 force = normalize(a->position - b->position) * (spring_coef * (length(a->position - b->position) - des_length) + dampling_force * dot((a->velocity - b->velocity), (normalize(a->position - b->position))));
		a->add_force(-force);
		b->add_force(force);
		// dt�� �� �ᵵ �ǳ�..?
	}
};

#endif