#ifndef Viewer_h
#define Viewer_h

#include "Simulator.h"
#include "GL/freeglut.h"
#include <iostream>

class Viewer {
	// simulator cache
	Simulator opengl_simulator;
	// mouse coord cache
	int m_Mouse_coord[2] = { 0,0 };
	// mouse click event
	// ¿ÞÂÊ, ÈÙ, ¿À¸¥ÂÊ Å¬¸¯
	bool m_Mouse_Event[3] = { false,false,false };
	bool interactionMode[2] = { false, false };

	// simulation condition
	bool m_start = false;

	// rotate, translation, zoom cache
	float m_Rotate[2] = { 0,0 };
	float m_Translate[2] = { 0,0 };
	float m_zoom = 0.0f;

	// texture coord
	int tex_width, tex_height;
public:
	void Initialize(int width, int height);
	void Reshape(int w, int h);
	void Mouse(int mouse_event, int state, int x, int y);
	void Motion(int x, int y);
	void Dokeyboard(unsigned char key, int x, int y);
	void DoRelasekey(unsigned char key, int x, int y);
	void Update();
	void Render();
};

#endif