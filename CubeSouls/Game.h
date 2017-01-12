#pragma once

#include <iostream>
#include <gl/glew.h>
#include <gl/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "Vector3.h"
#include "Matrix3.h"
#include "Cube.h"

class Game
{
public:
	Game(sf::ContextSettings);
	~Game();
	void run();
private:
	sf::Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	void applyTransformation(const Matrix3&, Cube&);
	void translate(float, Matrix3::Axis, Cube&);
	sf::Clock clock;
	sf::Time elapsed;

	float rotationAngle = 0.0f;

	Matrix3 m_scale;
	Matrix3 m_rotate;
	Matrix3 m_translate;

	GLuint vbo[1];

	Cube m_cube{ 0.6f };
	Cube m_cube2{ -0.6f };
	Cube m_cube3{ -2.0f };
	Cube m_cube4{ 2.0f };
	Cube m_cube5{ 0.6f, 1.5f };
	Cube m_cube6{ -0.6f, 1.5f };
	Cube m_cube7{ -2.0f,1.5f };
	Cube m_cube8{ 2.0f,1.5f };
	Cube m_cube9{ 0.6f, -1.5f };
	Cube m_cube10{ -0.6f, -1.5f };
	Cube m_cube11{ -2.0f,-1.5f };
	Cube m_cube12{ 2.0f,-1.5f };
};

