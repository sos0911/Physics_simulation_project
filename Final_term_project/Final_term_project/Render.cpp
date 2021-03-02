#include "Render.h"

// ¹Ø´Ü Å×ÀÌºí ·»´õ¸µ
void render_table() {

    glPushMatrix();
    
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // { Front }
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // { Front }
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f); // { Front }
    glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // { Front }

    glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // { Right }
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f); // { Right }
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // { Right }
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f); // { Right }

    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f); // { Back }
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // { Back }
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // { Back }
    glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // { Back }

    glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // { Left }
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // { Left }
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // { Left }
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // { Left }

    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // { Top }
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // { Top }
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // { Top }
    glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // { Top }

    glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f); // { Bottom }
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // { Bottom }
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // { Bottom }
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // { Bottom }
    glEnd();

    glPopMatrix();

}