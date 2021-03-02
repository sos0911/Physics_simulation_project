#include "Deformable_System.h"

void mass_cloth::init(int x, int y, int z, int tex_width, int tex_height) {
	// initialization
	// (x,y,z)부터 시작하여 모든 축 좌표 ++
	// int index = 0;
	for (int i_x = 0; i_x < size_x; i_x += dx) {
		for (int i_y = 0; i_y < size_y; i_y += dy) {
			for (int i_z = 0; i_z < size_z; i_z += dz) {
				// position
				// 각 구석데기 위쪽 한 노드씩만 고정
				Node* temp;
				if ((i_x == 0 && i_z == 0) || (i_x == size_x - 1 && i_z == 0))
					temp = new Node(vec3(i_x + x, i_y + y, i_z + z), vec3(0, 1, 0), vec2(((float)(1.0)/size_x)*i_x, ((float)(1.0) / size_z) * i_z), true);
				else
					temp = new Node(vec3(i_x + x, i_y + y, i_z + z), vec3(0, 1, 0), vec2(((float)(1.0) / size_x) * i_x, ((float)(1.0) / size_z) * i_z), false);
				nodes.push_back(temp);
			}
		}
	}

	// spring init
	// spring들 자체는 종류 관계없이 하나로 모아 관리
	
	// structural 
	for (int i_x = 0; i_x < size_x; i_x += dx) {
		for (int i_y = 0; i_y < size_y; i_y += dy) {
			for (int i_z = 0; i_z < size_z; i_z += dz) {
				if (boundary_check(i_x + 1, i_y, i_z)) {
					Mass_spring* sp = new Mass_spring(nodes[Findindex(i_x, i_y, i_z)], nodes[Findindex(i_x + 1, i_y, i_z)], structural_coef, dx);
					spring.push_back(sp);
				}
				if (boundary_check(i_x, i_y, i_z + 1)) {
					Mass_spring* sp = new Mass_spring(nodes[Findindex(i_x, i_y, i_z)], nodes[Findindex(i_x, i_y, i_z + 1)], structural_coef, dy);
					spring.push_back(sp);
				}
			}
		}
	}

	// shear 
	for (int i_x = 0; i_x < size_x; i_x += dx) {
		for (int i_y = 0; i_y < size_y; i_y += dy) {
			for (int i_z = 0; i_z < size_z; i_z += dz) {
				if (boundary_check(i_x + 1, i_y, i_z + 1)) {
					Mass_spring* sp = new Mass_spring(nodes[Findindex(i_x, i_y, i_z)], nodes[Findindex(i_x + 1, i_y, i_z + 1)], shear_coef, sqrt(dx*dx + dy*dy));
					spring.push_back(sp);
				}
				if (boundary_check(i_x + 1, i_y, i_z - 1)) {
					Mass_spring* sp = new Mass_spring(nodes[Findindex(i_x, i_y, i_z)], nodes[Findindex(i_x + 1, i_y, i_z - 1)], shear_coef, sqrt(dx*dx + dy*dy));
					spring.push_back(sp);
				}
			}
		}
	}

	// bending
	for (int i_x = 0; i_x < size_x; i_x += dx) {
		for (int i_y = 0; i_y < size_y; i_y += dy) {
			for (int i_z = 0; i_z < size_z; i_z += dz) {
				if (boundary_check(i_x + 2, i_y, i_z)) {
					Mass_spring* sp = new Mass_spring(nodes[Findindex(i_x, i_y, i_z)], nodes[Findindex(i_x + 2, i_y, i_z)], bending_coef, dx*2);
					spring.push_back(sp);
				}
				if (boundary_check(i_x, i_y, i_z + 2)) {
					Mass_spring* sp = new Mass_spring(nodes[Findindex(i_x, i_y, i_z)], nodes[Findindex(i_x, i_y, i_z + 2)], bending_coef, dy*2);
					spring.push_back(sp);
				}
			}
		}
	}

	////////////////////////
	// gernerating face
	////////////////////////
	
	for (int i_x = 0; i_x < size_x; i_x += dx) {
		for (int i_y = 0; i_y < size_y; i_y += dy) {
			for (int i_z = 0; i_z < size_z; i_z += dz) {
				if (boundary_check(i_x + 1, i_y, i_z) && boundary_check(i_x+1, i_y, i_z-1)){
					// 반시계 방향
					faces.push_back(nodes[Findindex(i_x, i_y, i_z)]);
					faces.push_back(nodes[Findindex(i_x+1, i_y, i_z)]);
					faces.push_back(nodes[Findindex(i_x+1, i_y, i_z-1)]);
				}
				if (boundary_check(i_x + 1, i_y, i_z-1) && boundary_check(i_x, i_y, i_z-1)){
					// 반시계 방향
					faces.push_back(nodes[Findindex(i_x, i_y, i_z)]);
					faces.push_back(nodes[Findindex(i_x + 1, i_y, i_z-1)]);
					faces.push_back(nodes[Findindex(i_x, i_y, i_z-1)]);
				}
			}
		}
	}

	cout << "node size : " << nodes.size() << '\n';
	cout << "spring size : " << spring.size() << '\n';
	cout << "face size : " << faces.size() << '\n';

	// face normal vector initialize
	faces_normal.assign(faces.size() / 3, vec3(0, 0, 0));

	// TODO : generate exture coord 

	
}

int mass_cloth::Findindex(int x, int y, int z) {
	// find index of nodes
	return x * size_y * size_z + y * size_z + z;
}

bool mass_cloth::boundary_check(int x, int y, int z) {
	return x >= 0 && x < size_x && y >= 0 && y < size_y && z >= 0 && z < size_z;
}

void mass_cloth::compute_force(double dt, vec3 ext_force) {
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->add_force(ext_force * nodes[i]->mass);
	}
	for (int i = 0; i < spring.size(); i++) {
		spring[i]->internal_force(dt);
	}
}

void mass_cloth::integrate(double dt) {
	// 보다 나은 기법
	// Symplectic Euler
	int n_size = nodes.size();

	for (int i = 0; i < nodes.size(); i++) {
		if (!nodes[i]->isfixed) {

			// integration
			nodes[i]->velocity *= nodes[i]->damping_force;
			vec3 temp = nodes[i]->position;

			nodes[i]->velocity += (nodes[i]->force / nodes[i]->mass) * (float)(dt);
			nodes[i]->position += nodes[i]->velocity * (float)(dt);
			nodes[i]->old_position = temp;

		}
		nodes[i]->force = vec3(0, 0, 0);
	}

}

void mass_cloth::collision_response(vec3 ground) {
	// collision & check
	// ground와 self-check collision 전부 수행
	// ground는 y값만 보면 됨!
	float threshold = 0.5;
	vec3 ground_normal = vec3(0, 1, 0);

	// ground collision
	for (int i = 0; i < nodes.size(); i++) {
		//if (dot((nodes[i]->position - ground), ground_normal) < threshold && dot(ground_normal, nodes[i]->velocity) < 0) {
		if (dot((nodes[i]->position - ground), ground_normal) < threshold && dot(ground_normal, nodes[i]->velocity) < 0) {
			// collision detected
			vec3 v_n = dot(ground_normal, nodes[i]->velocity) * ground_normal;
			vec3 v_t = nodes[i]->velocity - v_n;
			nodes[i]->velocity = v_t - (float)5*v_n;

		}
	}

	// TODO : self-collision
	// 노드들 간의 충돌

	// TODO : node-face collision
	// 노드 - face 간 충돌

}

void mass_cloth::computeNormal() {
	// normal 계산
	// faces_normal 갱신 using faces
	// 6개씩 잘라서 보면 된다..
	// 그 중 앞 3개, 뒷 세개 따로구현
	int index = 0;
	for (int i = 0; i < faces.size(); i+=6) {
		
		vec3 n1 = faces[i + 2]->position - faces[i]->position;
		vec3 n2 = faces[i + 1]->position - faces[i]->position;
		vec3 res = normalize(cross(n2, n1));
		faces_normal[index++] = res;

		vec3 n3 = faces[i + 5]->position - faces[i + 3]->position;
		vec3 n4 = faces[i + 4]->position - faces[i + 3]->position;
		vec3 res2 = normalize(cross(n4, n3));
		faces_normal[index++] = res2;
	}

	// vertex normal
	// node의 normal에 저장됨.
	for (int i = 0; i < faces.size(); i++) {
		// node마다 주변 face normal들 저장
		faces[i]->faces_normal.push_back(faces_normal[i / 3]);
	}

	for (int i = 0; i < nodes.size(); i++) {
		vec3 res = vec3(0, 0, 0);
		for (int j = 0; j < nodes[i]->faces_normal.size(); j++) {
			res += nodes[i]->faces_normal[j];
		}
		nodes[i]->normal = normalize(res);
	}

}

void mass_cloth::draw(int width, int height) {
	// rendering draw
	switch (drawmode) {
	case draw_modes::DRAW_MASS_NODES:
		// TODO
		break;
	case draw_modes::DRAW_SPRINGS:
		// TODO
		break;
	case draw_modes::DRAW_FACES:
		// 삼각형 메쉬들을 렌더링
		// 버텍스에 할당된 각 노멀들과 같이.
		RenderFace(width, height);
		break;
	default:
		break;
	}
}

void mass_cloth::RenderFace(int width, int height) {
	// render face
	// texture도 매핑
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faces.size(); i+=3) {
		for (int j = 0; j < 3; j++) {
			Node* np = faces[i + j];
			glTexCoord2f(np->tex_coord.x, np->tex_coord.y);
			glNormal3f(np->normal.x, np->normal.y, np->normal.z);
			glVertex3f(np->position.x, np->position.y, np->position.z);
		}
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


