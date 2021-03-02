#ifndef SPHERE_CPP
#define SPHERE_CPP

#include "glm/glm.hpp"
#include "Deformable_System.h"

using namespace glm;

class sphere {
public:
	float radius;
	int mass;
	vec3 position, velocity;

	sphere(float _radius, vec3 _center_coord, int _mass) {
		radius = _radius;
		position = _center_coord;
		velocity = vec3(0, 0, 0);
		mass = _mass;
	}

	void Movement(float dt, vec3 force) {
		vec3 acc = force / (float)mass;
		velocity += acc * dt;
		position += velocity * dt;
	}

	float FindDistanceBetween(vec3 a, vec3 b) {
		// a와 b 간 거리를 찾는다
		float dist = (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)));
		return dist;
	}

	void collision_response(mass_cloth* cloth, vec3 ground) {
		// 구와 땅 충돌 + 구와 옷감 충돌
			
		// ground collision
		vec3 ground_normal(0, 1, 0);
		if (this->position.y - ground.y <= this->radius && dot(ground_normal, this->velocity) < 0) {
			// collision detected
			// cout << "collision_response" << '\n';

			vec3 v_n = dot(ground_normal, this->velocity) * ground_normal;
			vec3 v_t = this->velocity - v_n;
			this->velocity = v_t - (float)0.1*v_n;
		}

		// 구와 옷감 충돌
		// 파티클-파티클 간 충돌으로 모델링
		for (int i = 0; i < cloth->nodes.size(); i++) {
			vec3 pos_ij = cloth->nodes[i]->position - this->position;
			vec3 pos_ji = this->position - cloth->nodes[i]->position;
			float distance = length(pos_ij);
			float collidedist = this->radius + cloth->nodes[i]->radius;
			// 공과 각 노드마다 수행
			if (distance <= collidedist) {
				vec3 normal1 = (pos_ij) / (float)distance;
				vec3 normal2 = (pos_ji) / (float)distance;
				vec3 vn1 = normal1 * (dot(normal1 , this->velocity));
				vec3 vn2 = normal2 * (dot(normal2, cloth->nodes[i]->velocity));

				vec3 vt1 = this->velocity - vn1;
				vec3 vt2 = cloth->nodes[i]->velocity - vn2;

				vec3 relvel = cloth->nodes[i]->velocity - this->velocity;
				float mass_sum = this->mass + cloth->nodes[i]->mass;

				if (dot(relvel, pos_ij) < 0) {
					// collision detected
					this->velocity = (2.0f * vn2 * cloth->nodes[i]->mass + vn1 * (this->mass - cloth->nodes[i]->mass)) / (mass_sum)+vt1;

					cloth->nodes[i]->velocity = (2.0f * vn1 * (float)this->mass + vn1 * (cloth->nodes[i]->mass - this->mass)) / (mass_sum)+vt2;

				}

			}

		}

	}
};

#endif