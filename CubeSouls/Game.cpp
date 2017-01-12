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
	while (isRunning) {

		std::cout << "Game running..." << std::endl;

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
				applyTransformation(m_scale);
				break;
			case sf::Keyboard::E:
				m_scale = Matrix3::scale(0.9, 0.9, 0.9);
				applyTransformation(m_scale);
				break;
			case sf::Keyboard::Left:
				m_rotate = Matrix3::rotation(Matrix3::Axis::Y, -3);
				applyTransformation(m_rotate);
				break;
			case sf::Keyboard::Right:
				m_rotate = Matrix3::rotation(Matrix3::Axis::Y, 3);
				applyTransformation(m_rotate);
				break;
			case sf::Keyboard::W:
				m_translate = Matrix3::translate(0, 0.1);
				applyTransformation(m_translate);
				break;
			case sf::Keyboard::S:
				m_translate = Matrix3::translate(0, -0.1);
				applyTransformation(m_translate);
				break;
			case sf::Keyboard::D:
				m_translate = Matrix3::translate(0.1, 0);
				applyTransformation(m_translate);
				break;
			case sf::Keyboard::A:
				m_translate = Matrix3::translate(-0.1, 0);
				applyTransformation(m_translate);
				break;
			case sf::Keyboard::Up:
				m_rotate = Matrix3::rotation(Matrix3::Axis::X, -3);
				applyTransformation(m_rotate);
				break;
			case sf::Keyboard::Down:
				m_rotate = Matrix3::rotation(Matrix3::Axis::X, 3);
				applyTransformation(m_rotate);
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

	isRunning = true;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -3.0f);
	glewInit();

	/* Vertices counter-clockwise winding */
	//FRONT
	vertex[0].coordinate[0] = 0.5f;		//tr f
	vertex[0].coordinate[1] = 0.5f;
	vertex[0].coordinate[2] = 0.5f;

	vertex[1].coordinate[0] = -0.5f;	//tl f
	vertex[1].coordinate[1] = 0.5f;
	vertex[1].coordinate[2] = 0.5f;

	vertex[2].coordinate[0] = -0.5f;	//bl f
	vertex[2].coordinate[1] = -0.5f;
	vertex[2].coordinate[2] = 0.5f;

	vertex[3].coordinate[0] = 0.5f;		//br b
	vertex[3].coordinate[1] = -0.5f;
	vertex[3].coordinate[2] = 0.5f;




	//BACK
	vertex[4].coordinate[0] = 0.5f;		//tr b
	vertex[4].coordinate[1] = 0.5f;
	vertex[4].coordinate[2] = -0.5f;

	vertex[5].coordinate[0] = -0.5f;	//tl b
	vertex[5].coordinate[1] = 0.5f;
	vertex[5].coordinate[2] = -0.5f;

	vertex[6].coordinate[0] = -0.5f;	//bl b
	vertex[6].coordinate[1] = -0.5f;
	vertex[6].coordinate[2] = -0.5f;

	vertex[7].coordinate[0] = 0.5f;		//br b
	vertex[7].coordinate[1] = -0.5f;
	vertex[7].coordinate[2] = -0.5f;



	vertex[0].color[0] = 1.0f;		//Nevajo white
	vertex[0].color[1] = 0.870588f;
	vertex[0].color[2] = 0.678431;

	vertex[1].color[0] = 0.254902f; //Royal blue
	vertex[1].color[1] = 0.411765f;
	vertex[1].color[2] = 0.882353;

	vertex[2].color[0] = 1.0f;		//red
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 1.0f;		//magenta
	vertex[3].color[1] = 0.0f;
	vertex[3].color[2] = 1.0f;

	vertex[4].color[0] = 0.2f;		//Blue
	vertex[4].color[1] = 0.0f;
	vertex[4].color[2] = 1.0f;

	vertex[5].color[0] = 0.0f;		//cyan
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 1.0f;

	vertex[6].color[0] = 0.0f;		//green
	vertex[6].color[1] = 1.0f;
	vertex[6].color[2] = 0.0f;

	vertex[7].color[0] = 1.0f;		//yellow
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 0.0f;

	//front
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 0;   triangles[5] = 2;

	//Top
	triangles[6] = 5;	triangles[7] = 1;	triangles[8] = 0;
	triangles[9] = 5;	triangles[10] = 0;	triangles[11] = 4;

	//Back
	triangles[12] = 6;	triangles[13] = 5;	triangles[14] = 4;
	triangles[15] = 6;	triangles[16] = 4;	triangles[17] = 7;

	//Bottom
	triangles[18] = 2;	triangles[19] = 6;	triangles[20] = 7;
	triangles[21] = 2;	triangles[22] = 7;	triangles[23] = 3;

	//right
	triangles[24] = 7;	triangles[25] = 4;	triangles[26] = 0;
	triangles[27] = 7;	triangles[28] = 0;	triangles[29] = 3;

	//left
	triangles[30] = 2;	triangles[31] = 1;	triangles[32] = 5;
	triangles[33] = 2;	triangles[34] = 5;	triangles[35] = 6;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	glCullFace(GL_BACK);
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	std::cout << "Update up" << std::endl;
}

void Game::render()
{
	std::cout << "Drawing" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex), vertex, GL_STATIC_DRAW);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/* Draw Triangle from VBO */

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	std::cout << "Cleaning up" << std::endl;

	glDeleteBuffers(1, vbo);
}

/// <summary>
/// Method to apply transformations
/// </summary>
/// <param name="transform"></param>
void Game::applyTransformation(const Matrix3 & transform)
{
	for (unsigned int i = 0u; i < VERTICES_SIZE; i++)
	{
		Vector3 point = Vector3(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2]);
		point = transform * point;
		vertex[i].coordinate[0] = point.getX();
		vertex[i].coordinate[1] = point.getY();
		vertex[i].coordinate[2] = point.getZ();
	}
}

