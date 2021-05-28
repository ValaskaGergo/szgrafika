#include "draw.h"
#include "model.h"
#include "callbacks.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

float sizeOfPlatform = 3000.0f;
extern GLfloat light_ambient[4];

double platformWidth = 3000;
double platformLength = 3000;
double platformHeight = 3000;

GLfloat material_ambient_default[] = {0.9, 0.9, 0.9, 0.5};

void draw_content(World* world)
{
	Platform roomToDraw = world -> platform;
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
		draw_walls(roomToDraw);
		draw_ground(roomToDraw);
	glPopMatrix();
	
	//Labyrinth:
	draw_objects(-2700, 500, 0);
	draw_objects(-2100, 500, 0);
	draw_objects(-1500, 500, 0);
	draw_objects(-900, 500, 0);
	draw_objects(-300, 500, 0);
	
	draw_objects(-2700, -800, 0);
	draw_objects(-2100, -800, 0);
	draw_objects(-1500, -800, 0);
	draw_objects(-900, -800, 0);
	
	draw_objects(-300, -800, 0);
	draw_objects(-300, -1200, 0);
	draw_objects(-300, -1600, 0);
	draw_objects(-300, -2000, 0);
	draw_objects(-300, -2400, 0);
	draw_objects(-300, -2800, 0);
	
	draw_objects(800, 700, 0);
	draw_objects(800, 1200, 0);
	draw_objects(800, 1600, 0);
	draw_objects(800, 2200, 0);
	draw_objects(800, 2800, 0);
	
	draw_objects(-300, 1200, 0);
	draw_objects(200, 2800, 0);
	
	draw_objects(-300, 2800, 0);
	draw_objects(-900, 2800, 0);
	draw_objects(-1500, 2800, 0);
	draw_objects(-2100, 2800, 0);
	
	draw_objects(-300, 1600, 0);
	draw_objects(-900, 1600, 0);
	draw_objects(-1500, 1600, 0);
	draw_objects(-2100, 1600, 0);
	draw_objects(-2100, 2200, 0);
	
	draw_objects(800, 200, 0);
	draw_objects(800, -300, 0);
	draw_objects(800, -800, 0);
	draw_objects(800, -1200, 0);
	draw_objects(800, -1600, 0);
	draw_objects(800, -2800, 0);
	draw_objects(300, -2800, 0);
	
	draw_objects(1400, -2800, 0);
	draw_objects(1800, -2800, 0);
	draw_objects(2200, -2800, 0);
	draw_objects(2800, -2800, 0);
	
	draw_objects(2800, -2300, 0);
	draw_objects(2800, -1700, 0);
	draw_objects(2800, -1200, 0);
	draw_objects(2800, -700, 0);
	
	draw_objects(2800, 400, 0);
	draw_objects(2300, 400, 0);
	draw_objects(1700, 400, 0);
	draw_objects(1200, 400, 0);
	
	
	glPushMatrix();
		glTranslatef(world->raptors[0].position.x, world->raptors[0].position.y, world->raptors[0].position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->raptors[0].material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->raptors[0].texture);
		glScalef(100.0f, 100.0f, 100.0f);
		glRotatef(world->raptors[0].rotation, 0, 1, 0);

		draw_model(&world->raptors[0].model);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(world->raptors[1].position.x, world->raptors[1].position.y, world->raptors[1].position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->raptors[1].material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->raptors[1].texture);
		glScalef(100.0f, 100.0f, 100.0f);
		glRotatef(world->raptors[1].rotation, 0, 1, 0);

		draw_model(&world->raptors[1].model);
    glPopMatrix();


	if (move_raptor_id != -1)
	{
		world->raptors[move_raptor_id].position.x = camera.position.x;
		world->raptors[move_raptor_id].position.z = camera.position.z;
	}
}

void draw_objects(int moveX, int moveZ,int degree) {
	glPushMatrix();
		glTranslatef(world.objects.position.x+moveX, world.objects.position.y, world.objects.position.z+moveZ);
		glRotatef(degree, 0, 1, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world.objects.material_ambient);

		glBindTexture(GL_TEXTURE_2D, world.objects.texture);
		glScalef(5.0f, 5.0f, 5.0f);
		glRotatef(180,0,90,90);

		draw_model(&world.objects.model);
    glPopMatrix();
}

void draw_ground(Platform platform) {
	glBindTexture(GL_TEXTURE_2D, platform.ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z;
	float uvTile = 1.0f / (2.0f * sizeOfPlatform / 50.0f);
	for (x = -sizeOfPlatform; x < sizeOfPlatform; x += 50.0f) {
		for (z = -sizeOfPlatform; z < sizeOfPlatform; z += 50.0f) {
			float uvX = x / sizeOfPlatform / 2 + 0.5f;
			float uvY = z / sizeOfPlatform / 2 + 0.5f;
			glTexCoord2f(uvX, uvY);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z);
			glTexCoord2f(uvX + uvTile, uvY);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z);
			glTexCoord2f(uvX + uvTile, uvY + uvTile);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z + 50);
			glTexCoord2f(uvX, uvY + uvTile);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z + 50);
		}
	}
	glEnd();
}

void draw_walls(Platform platform) {
	glBindTexture(GL_TEXTURE_2D, platform.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-sizeOfPlatform, 0, -sizeOfPlatform);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-sizeOfPlatform, sizeOfPlatform, -sizeOfPlatform);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfPlatform, sizeOfPlatform, sizeOfPlatform);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfPlatform, 0, sizeOfPlatform);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, platform.right);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfPlatform, 0, sizeOfPlatform);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfPlatform, sizeOfPlatform, sizeOfPlatform);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sizeOfPlatform, sizeOfPlatform, -sizeOfPlatform);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sizeOfPlatform, 0, -sizeOfPlatform);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, platform.front);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfPlatform, 0, -sizeOfPlatform);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfPlatform, 0, -sizeOfPlatform);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfPlatform, sizeOfPlatform, -sizeOfPlatform);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfPlatform, sizeOfPlatform, -sizeOfPlatform);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, platform.back);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-sizeOfPlatform, 0, sizeOfPlatform);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-sizeOfPlatform, sizeOfPlatform, sizeOfPlatform);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sizeOfPlatform, sizeOfPlatform, sizeOfPlatform);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sizeOfPlatform, 0, sizeOfPlatform);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, platform.top);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfPlatform, sizeOfPlatform, sizeOfPlatform);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfPlatform, sizeOfPlatform, -sizeOfPlatform);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfPlatform, sizeOfPlatform, -sizeOfPlatform);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfPlatform, sizeOfPlatform, sizeOfPlatform);
	glEnd();
}

void draw_help(int texture) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(WINDOW_WIDTH, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}