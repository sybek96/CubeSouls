#include "Game.h"

static bool flip;

Game::Game(sf::ContextSettings settings) : window(sf::VideoMode(800, 600), "OpenGL Cube", sf::Style::Default, settings)
{
}

Game::~Game() {}

const unsigned int VERTICES_SIZE = 8u;

void Game::run()
{

	initialize();
	sf::Event event;
	while (isRunning) 
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
			switch (event.key.code)
			{
			case sf::Keyboard::Q:
				m_scale = Matrix3::scale(1.1, 1.1, 1.1);
				applyTransformation(m_scale,m_cube);
				break;
			case sf::Keyboard::E:
				m_scale = Matrix3::scale(0.9, 0.9, 0.9);
				applyTransformation(m_scale, m_cube);
				break;
			case sf::Keyboard::Left:
				m_rotate = Matrix3::rotation(Matrix3::Axis::Y, -3);
				applyTransformation(m_rotate, m_cube);
				break;
			case sf::Keyboard::Right:
				m_rotate = Matrix3::rotation(Matrix3::Axis::Y, 3);
				applyTransformation(m_rotate, m_cube);
				break;
			case sf::Keyboard::W:
				translate(0.1, Matrix3::Axis::Y, m_cube);
				break;
			case sf::Keyboard::S:
				translate(-0.1, Matrix3::Axis::Y, m_cube);
				break;
			case sf::Keyboard::D:
				translate(0.1, Matrix3::Axis::X, m_cube);
				break;
			case sf::Keyboard::A:
				translate(-0.1, Matrix3::Axis::X, m_cube);
				break;
			case sf::Keyboard::R:
				translate(0.1, Matrix3::Axis::Z, m_cube);
				break;
			case sf::Keyboard::T:
				translate(-0.1, Matrix3::Axis::Z, m_cube);
				break;
			case sf::Keyboard::Up:
				m_rotate = Matrix3::rotation(Matrix3::Axis::X, -3);
				applyTransformation(m_rotate, m_cube);
				break;
			case sf::Keyboard::Down:
				m_rotate = Matrix3::rotation(Matrix3::Axis::X, 3);
				applyTransformation(m_rotate, m_cube);
				break;
			default:
				break;
			}
		}
		update();
		render();
	}

}



void Game::initialize()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	isRunning = true;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -6.0f);
	glewInit();

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);
	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	//initialise the cubes
	m_cube.initialize(); 
	m_cube2.initialize();
	m_cube3.initialize();
	m_cube4.initialize();
	m_cube5.initialize();
	m_cube6.initialize();
	m_cube7.initialize();
	m_cube8.initialize();
	m_cube9.initialize();
	m_cube10.initialize();
	m_cube11.initialize();
	m_cube12.initialize();
}

void Game::update()
{
	glCullFace(GL_BACK);

	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();
	}
	m_cube.update();
	m_cube2.update();
	m_cube3.update();
	m_cube4.update();
	m_cube5.update();
	m_cube6.update();
	m_cube7.update();
	m_cube8.update();
	m_cube9.update();
	m_cube10.update();
	m_cube11.update();
	m_cube12.update();
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	m_cube.render();
	m_cube2.render();
	m_cube3.render();
	m_cube4.render();
	m_cube5.render();
	m_cube6.render();
	m_cube7.render();
	m_cube8.render();
	m_cube9.render();
	m_cube10.render();
	m_cube11.render();
	m_cube12.render();
	window.display();
}

void Game::unload()
{
	glDeleteBuffers(1, vbo);
}

/// <summary>
/// Method to apply transformations
/// </summary>
/// <param name="transform"></param>
void Game::applyTransformation(const Matrix3 & transform, Cube& cube)
{
	for (unsigned int i = 0u; i < VERTICES_SIZE; i++)
	{
		Vector3 point = Vector3(cube.vertex[i].coordinate[0], cube.vertex[i].coordinate[1], cube.vertex[i].coordinate[2]);
		point = transform * point;
		cube.vertex[i].coordinate[0] = point.getX();
		cube.vertex[i].coordinate[1] = point.getY();
		cube.vertex[i].coordinate[2] = point.getZ();
	}
}
/// <summary>
/// Method to translate the cube
/// </summary>
/// <param name="offset">the offset by which to move</param>
/// <param name="axis">the axis to rotate by</param>
/// <param name="cube">the cube to rotate</param>
void Game::translate(float offset, Matrix3::Axis axis, Cube& cube)
{
	for (unsigned int i = 0u; i < VERTICES_SIZE; i++)
	{
		Vector3 point = Vector3(cube.vertex[i].coordinate[0], cube.vertex[i].coordinate[1], cube.vertex[i].coordinate[2]);
		cube.vertex[i].coordinate[0] = Matrix3::translate(point, offset, axis).getX();
		cube.vertex[i].coordinate[1] = Matrix3::translate(point, offset, axis).getY();
		cube.vertex[i].coordinate[2] = Matrix3::translate(point, offset, axis).getZ();
	}
}



