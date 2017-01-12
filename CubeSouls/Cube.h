#pragma once

#include <iostream>
#include <gl/glew.h>
#include <gl/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "Vector3.h"
#include "Matrix3.h"
class Cube
{
public:
	Cube(float xOffset = 0, float yOffset = 0, float zOffset = 0);
	~Cube();
	void initialize();
	void update();
	void render();
	typedef struct
	{
		float coordinate[3];
		float color[3];
	} Vertex;
	Vertex vertex[8];
	GLubyte triangles[36];
private:
	/* Variable to hold the VBO identifier */
	GLuint index;
	float m_xOffset;
	float m_yOffset;
	float m_zOffset;
};

