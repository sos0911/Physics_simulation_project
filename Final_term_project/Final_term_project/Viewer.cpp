#include "Viewer.h"

void Viewer::Initialize(int _width, int _height) {
	tex_width = _width;
	tex_height = _height;
	opengl_simulator.Initialize(_width, _height);
	opengl_simulator.Lighting();
}

void Viewer::Reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w / h, 0.1, 1000);
	glViewport(0, 0, w, h);
}

void Viewer::Mouse(int mouse_event, int state, int x, int y) {
	m_Mouse_coord[0] = x;
	m_Mouse_coord[1] = y;
	switch (mouse_event) {
	case GLUT_LEFT_BUTTON:
		m_Mouse_Event[0] = ((state == GLUT_DOWN) ? 1 : 0);
		break;
	case GLUT_MIDDLE_BUTTON:
		m_Mouse_Event[1] = ((state == GLUT_DOWN) ? 1 : 0);
		break;
	case GLUT_RIGHT_BUTTON:
		m_Mouse_Event[2] = ((state == GLUT_DOWN) ? 1 : 0);
		break;
	default:
		break;
	}
	// �̰͵� ���� �ϳ�?
	glutPostRedisplay();
}

void Viewer::Motion(int x, int y) {
	int diffx = x - m_Mouse_coord[0];
	int diffy = y - m_Mouse_coord[1];

	m_Mouse_coord[0] = x;
	m_Mouse_coord[1] = y;

	if (m_Mouse_Event[0]) {
		m_Rotate[0] += (float)0.1 * diffx;
		m_Rotate[1] += (float)0.1 * diffy;
	}
	else if (m_Mouse_Event[1]) {
		// ���� �����ϸ� translate
		m_Translate[0] += (float)0.1 * diffx;
		m_Translate[1] += (float)0.1 * diffy;
	}
	else if (m_Mouse_Event[2]){
		// y�� �������� zoom
		m_zoom += (float)0.2 * diffy;
	}
}

void Viewer::DoRelasekey(unsigned char key, int x, int y) {
	// �̹� ������Ʈ������ ������ ����.
	// Ű���� �ش� key�� ��� �ö���� ��
	// Ű���� �Է� �������� ���� ������ ���� ����
	glutPostRedisplay();
}

void Viewer::Dokeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// pause ���
	case 'p':
	case 'P':
		m_start = !m_start;
		break;
	case 'q':
	case 'Q':
		exit(0);
		break;
	case 'r':
	case 'R':
		opengl_simulator.Initialize(tex_width, tex_height);
		break;
	case 'f':
	case 'F':
		// �̹��� �̰� ����?
		interactionMode[0] = !interactionMode[0];
		break;
	case 'g':
	case 'G':
		// �̹��� �̰� ����?
		interactionMode[1] = !interactionMode[1];
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void Viewer::Update() {
	// update func
	if (m_start) {
		opengl_simulator.Update(interactionMode);
	}
}

void Viewer::Render() {
	// Initialize glut
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// object space -> world space
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	int z_cache = (int)opengl_simulator.get_table_coord()[2] + (int)opengl_simulator.get_table_size()[2] * 2;

	gluLookAt(0.0, 0.0, z_cache, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// 3D �� �̵�(zoom)
	glTranslatef(0.0f, 0.0f, -m_zoom);
	// ȭ�� ���� 2D �̵�
	glTranslatef(m_Translate[0], m_Translate[1], 0.0);
	//glPushMatrix();
	glRotatef(m_Rotate[1], 1.0, 0.0, 0.0);
	glRotatef(m_Rotate[0], 0.0, 1.0, 0.0);

	opengl_simulator.Render();

	// ���� ��ġ���� or ���� �̵�?
	float light_pos[] = { 150.0, 151.0, 150.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}