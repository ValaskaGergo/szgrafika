#ifndef INCLUDE_DRAW_H_
#define INCLUDE_DRAW_H_

#include "model.h"

#ifndef GL_EXT_texture_edge_clamp
#define GL_CLAMP_TO_EDGE                 0x812F
#endif

// Draw the content.
void draw_content(World* world);

// Draws the ground.
void draw_ground(Platform platform);

// Draws the end of the map.
void draw_walls(Platform platform);

// Draws the help menu.
void draw_help(int texture);

// Draws the hedges.
void draw_objects(int moveX, int moveZ,int degree);

// Draws the raptors.
void draw_raptors(int moveX, int moveZ,int degree);

#endif /* INCLUDE_DRAW_H_ */
