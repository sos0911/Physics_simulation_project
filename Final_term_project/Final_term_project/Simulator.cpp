#include "Simulator.h"
#include "GL/freeglut.h"
#include "Box2D/Box2D.h"

void Simulator::Initialize(int _width, int _height) {
	timestep = 0.1;

	gluQuadricNormals(pobj, GLU_SMOOTH);

	// cloth simulator
	ground = vec3(0, table_middle_coord[1] + table_size[1] / 2, 0);
	cloth = new mass_cloth();

	// texture cache
	width = _width;	
	height = _height;

	// �� node �� �Ÿ��� 1
	cloth->dx = 1;
	cloth->dy = 1;
	cloth->dz = 1;
	cloth->size_x = 50;
	cloth->size_y = 1;
	cloth->size_z = 50;
	cloth->structural_coef = 1500;
	cloth->shear_coef = 50;
	cloth->bending_coef = 1000;
	cloth->iteration_n = 100;
	cloth->drawmode = mass_cloth::draw_modes::DRAW_FACES;
	cloth->init(-cloth->size_x/2 - 50, table_middle_coord[1] + table_size[1] + cloth->size_x, -cloth->size_z/2, _width, _height);

	// �� �����
	sp = new sphere(15, vec3(-cloth->size_x / 2 - 50 + cloth->size_x/2, table_middle_coord[1] + table_size[1] + 15, -cloth->size_z / 2 - 30), 100);

	// particle simultator
	// ���� ���� �׸���.
	fireworks = new ParticleSystem();
	fireworks->init(NUMBER_OF_PARTICLE, vec3(0, 10.0f, 0), ring_radius - ring_thick - 3);
	fireworks->set_gravity(vec3(0, -9.8, 0));
}

void Simulator::Lighting() {
	// TODO : Lighting
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // background color setup

	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);

	glFrontFace(GL_CCW); //�ݽð�������� ���� �������� �ո�
	glEnable(GL_CULL_FACE); //������ �κ��� �׷����� �ʰ� �Ѵ�.

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	// point-light
	float light_pos[] = { 150.0, 151.0, 150.0, 1.0 }; 

	float light_dir[] = { -1,-1,-1,0.0 };
	float light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	float light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float frontColor[] = { 0.8, 0.8, 0.8, 1 }; // �̰� ����..

	float matShininess = 256;
	float noMat[] = { 0,0,0,1 }; // ??

	float matSpec[] = { 1.0,1.0,1.0,1.0 };

	///*glMaterialfv(GL_FRONT, GL_EMISSION, noMat);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, frontColor);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, frontColor);
	//glMateriali(GL_FRONT, GL_SHININESS, matShininess);*/

	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0f);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 80.0f);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHT0);

}

void Simulator::Update(bool interactionmode[2]) {
	// TODO : particle & cloth update
	// cloth->iteration_n = ?
	vec3 gravity(0.0, -9.8 / cloth->iteration_n, 0.0);

	vec3 external_force; // cloth�� ���������� �������� �ܺ� ��
	vec3 sphere_force;  // sphere�� ���������� �������� �ܺ� ��


	if (interactionmode[0])
		external_force = gravity + vec3(0.0, 0.0, -10.0 / cloth->iteration_n);
	else
		external_force = gravity;

	if (interactionmode[1])
		sphere_force = gravity + vec3(0.0, 0.0, 10.0 / cloth->iteration_n);
	else
		sphere_force = gravity;

	for (int i = 0; i < cloth->iteration_n; i++) {

		cloth->compute_force(timestep, external_force);
		cloth->integrate(timestep);
		// �� �ȿ��� self-check collision�� ground check�� �� �ҵ�
		// sphere collide�� ���⼭ �ؾ���
		sp->Movement(timestep, sphere_force);
		// ���� cloth ���� �浹 + ���� ���� �浹
		sp->collision_response(cloth, ground);
		// cloth�� ������ �浹
		cloth->collision_response(ground);
	}

	// �������� ���� normal ���(using faces)
	// �� step���� �ڷᱸ�� �ʱ�ȭ
	for (int i = 0; i < cloth->nodes.size(); i++)
		cloth->nodes[i]->faces_normal.clear();
	cloth->computeNormal();

	// particle system update
	fireworks->Movement(timestep);
	// ������ ��ƼŬ ����
	fireworks->DeleteoldParticles();
	// ���ο� ��ƼŬ�� ����
	fireworks->MakenewParticles(100);
	// ��ƼŬ ���� �浹�� �ϴ� ����
	// fireworks->Collision();
	
}

void Simulator::Render() {
	// TODO : Render particle & cloth
	// draw boundary.. etc

	// Drawboundary();
	
	glColor3f(0.3f, 0.5f, 0.3f);
	DrawTable(table_size[0], table_size[1], table_size[2], table_middle_coord[0], table_middle_coord[1], table_middle_coord[2]);

	//glDisable(GL_CULL_FACE); //������ �κе� �׸���.
	//DrawDisk(0.1f, 0.3f, 26, 13);
	//glEnable(GL_CULL_FACE); //������ �κ��� �׷����� �ʰ� �Ѵ�.

	glColor3f(1.0f, 0.0f, 0.0f);

	DrawRing(0, 0, 0, table_size[0]/12, ring_radius, ring_thick);

	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_CULL_FACE); //������ �κе� �׸���.
	cloth->draw(width, height);
	glEnable(GL_CULL_FACE); //������ �κ��� �׷����� �ʰ� �Ѵ�.

	// �� �׸���
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawSphere();

	// paricle deaw
	fireworks->draw();
}

void Simulator::DrawTable(float w, float h, float t, float x, float y, float z) {
	// draw table
	// (w,h)�� ������
	// t�� �β�
	// (x,y,z)�� �߽���ǥ
	// height�� ���������� ������
	glPushMatrix();

	glScalef(w/2, h/2, t/2);
	glTranslatef(x, y, z);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);   // <1> // TODO : getnormal()
	glVertex3f(1.0f, 1.0f, 1.0f);   // <2>
	glVertex3f(-1.0f, 1.0f, 1.0f);  // <2>
	glVertex3f(-1.0f, -1.0f, 1.0f); // <2>
	glVertex3f(1.0f, -1.0f, 1.0f);  // <2>

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	// �Ʒ���
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// �̰� ����
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	glPopMatrix();
}

void Simulator::DrawDisk(float inner, float outer, int slices, int loops) {
	glPushMatrix();
	glTranslatef(0, 0.6f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluDisk(pobj, inner, outer, slices, loops);
	glPopMatrix();
}

void Simulator::DrawSphere() {
	// �� �׸���
	glPushMatrix();
	glTranslatef(sp->position.x, sp->position.y, sp->position.z);
	glutSolidSphere(sp->radius, 30, 30);
	glPopMatrix();
}

void Simulator::DrawRing(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h, GLfloat thick) {
	/* function createRing()
   ���� �߽� x,y,z��ǥ, ������, ����, �β��� �޾� ���� �����ϴ� �Լ�
   centerx : ���� �߽� x��ǥ
   centery : ���� �߽� y��ǥ
   centerz : ���� �߽� z��ǥ
   radius : ���� ������
   h  : ���� ����
   thick : ���� �β�
   */
	glPushMatrix();
	glTranslatef(0.0f, table_size[1]/2, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	GLfloat x, y, angle;

	glColor3ub(148, 0, 211);
	glBegin(GL_QUAD_STRIP);           //���� ����
	for (angle = (2.0f * GL_PI); angle > 0.0f; angle -= (GL_PI / 8.0f))
	{
		x = centerx + radius * sin(angle);
		y = centery + radius * cos(angle);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(x, y, centerz);
		x = centerx + (radius - thick) * sin(angle);
		y = centery + (radius - thick) * cos(angle);
		glVertex3f(x, y, centerz);
	}
	glEnd();

	int color = 0;
	glBegin(GL_QUAD_STRIP);            //���� �ٱ��� ����
	for (angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius * sin(angle);
		y = centery + radius * cos(angle);
		glNormal3f(sin(angle), cos(angle), 0.0f);
		glVertex3f(x, y, centerz);
		glVertex3f(x, y, centerz + h);
		color++;
	}
	glEnd();

	glColor3ub(148, 0, 211);
	glBegin(GL_QUAD_STRIP);            //���� ���� ����
	for (angle = (2.0f * GL_PI); angle > 0.0f; angle -= (GL_PI / 8.0f))
	{
		x = centerx + (radius - thick) * sin(angle);
		y = centery + (radius - thick) * cos(angle);
		glNormal3f(-sin(angle), -cos(angle), 0.0f);
		glVertex3f(x, y, centerz);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);           //������� �ظ�
	for (angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius * sin(angle);
		y = centery + radius * cos(angle);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(x, y, centerz + h);
		x = centerx + (radius - thick) * sin(angle);
		y = centery + (radius - thick) * cos(angle);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();

	glPopMatrix();
}

float* Simulator::get_table_coord() {
	return table_middle_coord;
}

float* Simulator::get_table_size() {
	return table_size;
}
