#include "scene.h"

#include <GL/glut.h>

void init_scene(Scene* scene)
{
}

void draw_scene(const Scene* scene)
{
    draw_origin();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
	
	for (i=o; i<10; ++i) {
		glBegin(GL_TRIANLES);

		glColor3f(1, 0, 0);
		glVertex3f(1, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 1, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 1);

		glEnd();
	}
}
