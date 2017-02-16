#include "PlayerCube.h"


/// <summary>
/// Constructor
/// </summary>
/// <param name="xOffset"></param>
/// <param name="yOffset"></param>
/// <param name="zOffset"></param>
/// <param name="view"></param>
PlayerCube::PlayerCube(float xOffset, float yOffset, float zOffset,const glm::mat4 & view)
	: MyCube(xOffset, yOffset, zOffset, view)
	, MOVE_SPEED(20.0f)
	, m_squash(false)
	, m_spawning(true)
{
}

/// <summary>
/// Update
/// </summary>
/// <param name="dt"></param>
void PlayerCube::update(double dt)
{
	if (m_spawning) //if spawning do spawn animation
	{
		model = glm::translate(model, glm::vec3(0.0f, -0.02f, 0.0f));
		m_positionTopLeft.y -= 0.02f;
		m_positionTopRight.y -= 0.02f;
	}
	else if (!m_squash) //else if not squash
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			model = glm::translate(model, glm::vec3(-MOVE_SPEED * dt, 0.0f, 0.0f));
			m_positionTopRight.x += -MOVE_SPEED * dt;
			m_positionTopLeft.x += -MOVE_SPEED * dt;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			model = glm::translate(model, glm::vec3(MOVE_SPEED * dt, 0.0f, 0.0f));
			m_positionTopRight.x += MOVE_SPEED * dt;
			m_positionTopLeft.x += MOVE_SPEED * dt;
		}
	}
	else
	{
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
	}
	MyCube::update(dt);
}

/// <summary>
/// get top right of cube
/// </summary>
/// <returns></returns>
sf::Vector3f PlayerCube::getPosRight() const
{
	return m_positionTopRight;
}

/// <summary>
/// get top left of cube
/// </summary>
/// <returns></returns>
sf::Vector3f PlayerCube::getPosLeft() const
{
	return m_positionTopLeft;
}

/// <summary>
/// Set position of the player
/// </summary>
/// <param name="position"></param>
void PlayerCube::resetPosition()
{
	model = glm::translate(model, glm::vec3(-m_positionTopLeft.x, 0, 0));
	m_positionTopLeft = sf::Vector3f(0, 0, 6);
	m_positionTopRight = sf::Vector3f(2, 2, 6);
}

/// <summary>
/// Set the squash bool
/// </summary>
/// <param name="check"></param>
void PlayerCube::setSquash(bool check)
{
	m_squash = check;
}

/// <summary>
/// Set the spawning bool
/// </summary>
/// <param name="check"></param>
void PlayerCube::setSpawning(bool check)
{
	m_spawning = check;
}

/// <summary>
/// Destructor
/// </summary>
PlayerCube::~PlayerCube()
{
	std::cout << "DELETING PLAYER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}
