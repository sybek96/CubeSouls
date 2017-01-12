#pragma once

#include <iostream>
#include <gl/glew.h>
#include <gl/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "Vector3.h"
#include "Matrix3.h"

class Game
{
public:
	Game(sf::ContextSettings);
	~Game();
	void run();
private:
	typedef struct
	{
		float coordinate[3];
		float color[3];
	} Vertex;

	Vertex vertex[8];
	GLubyte triangles[36];

	/* Variable to hold the VBO identifier */
	GLuint vbo[1];
	GLuint index;

	sf::Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	void applyTransformation(const Matrix3&);

	sf::Clock clock;
	sf::Time elapsed;

	float rotationAngle = 0.0f;

	Matrix3 m_scale;
	Matrix3 m_rotate;
	Matrix3 m_translate;
};

