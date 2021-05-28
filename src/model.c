#include "model.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include <obj/load.h>
#include <obj/draw.h>

void init_object(Object* object, int x, int z, int y)
{
	object->position.x = x;
	object->position.y = y;
	object->position.z = z;

	object->material_ambient[0] = 0.75;
	object->material_ambient[1] = 0.75;
	object->material_ambient[2] = 0.75;
	object->material_ambient[3] = 0.5;
}

// Loads the texture file with SOIL
GLuint load_texture(const char* filename) {
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	GLuint texture_name;
	Pixel* image;
	glGenTextures(1, &texture_name);

	int width;
	int height;

	image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

	glBindTexture(GL_TEXTURE_2D, texture_name);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,GL_RGBA,GL_UNSIGNED_BYTE,(Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	return texture_name;
}

void init_entities(World* world) {
	move_raptor_id = -1;

	
	load_model(&world->raptors[0].model, "data/models/raptor.obj");
	world->raptors[0].texture = load_texture("data/textures/raptor.jpg");
	init_object(&world->raptors[0], 2500, 0, 120);
	world->raptors[0].rotation = 270.0f;

	world->raptors[1].model = world->raptors[0].model;
	world->raptors[1].texture = world->raptors[0].texture;
	init_object(&world->raptors[1], -2500, 0, 120);
	world->raptors[1].rotation = 90.0f;

	
	load_model(&world->objects.model, "data/models/Hedge.obj");
	world->objects.texture = load_texture("data/textures/hedge.jpg");
	init_object(&world->objects, -120, 170, 2);

	
	world->platform.ground = load_texture("data/textures/ground.jpg");
	world->platform.top = load_texture("data/textures/top.jpg");
	world->platform.back = load_texture("data/textures/wall.jpg");
	world->platform.front = world->platform.back;
	world->platform.left = world->platform.back;
	world->platform.right = world->platform.back;
	
	
	world->helpTexture = load_texture("data/textures/help.png");
}
