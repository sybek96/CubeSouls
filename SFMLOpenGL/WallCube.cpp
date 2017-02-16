#include "WallCube.h"


/// <summary>
/// Constructor
/// </summary>
/// <param name="xOffset"></param>
/// <param name="yOffset"></param>
/// <param name="zOffset"></param>
/// <param name="view"></param>
/// <param name="speed"></param>
WallCube::WallCube(float xOffset, float yOffset, float zOffset,const glm::mat4 & view, float speed) 
	: MyCube(xOffset, yOffset, zOffset, view)
	, m_active(true)
	, m_moveSpeed(speed)
	, CRUMBLE_SPEED(2.0f)
	, m_stop(false)
	, m_time(0)
	, m_timeToFall(0)
	, m_direction(1)
	, m_fall(false)
	, FALL_SPEED(40.0f)
	, m_randTime(0.0f)
{
	m_randTime = genRandTime();
}

/// <summary>
/// Destructor
/// </summary>
WallCube::~WallCube()
{
	//std::cout << "Deleting Wall Cube" << std::endl;
}

/// <summary>
/// Get active bool
/// </summary>
/// <returns></returns>
bool WallCube::getActive() const
{
	return m_active;
}

/// <summary>
/// Update
/// </summary>
/// <param name="dt"></param>
void WallCube::update(double dt)
{
	if (!m_stop) //if not stop move cubes toward camera and update positions
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, m_moveSpeed * dt));
		m_positionTopRight.z += m_moveSpeed * dt;
		m_positionTopLeft.z += m_moveSpeed * dt;
		if (m_positionTopRight.z > 10.0f) //if position bigger than 10 set active to false
		{
			m_active = false;
		}
	}
	else //else do the animation of cubes shaking and falling
	{
		m_time += dt;
		m_timeToFall += dt;
		if (!m_fall) //if not fall then just shake
		{
			if (m_time > 0.1)
			{
				m_time -= 0.1;
				m_direction *= -1;
			}
			model = glm::translate(model, glm::vec3(CRUMBLE_SPEED * m_direction * dt, 0.0f, 0.0f));
			m_positionTopRight.x += CRUMBLE_SPEED * m_direction * dt;
			m_positionTopLeft.x += CRUMBLE_SPEED * m_direction * dt;
		}
		else //else fall
		{
			model = glm::translate(model, glm::vec3(0.0f, -FALL_SPEED * dt,0.0f));
			m_positionTopRight.x -= -FALL_SPEED * dt;
			m_positionTopLeft.x -= -FALL_SPEED * dt;
			if (m_positionTopRight.y < -10.0f)
			{
				m_active = false;
			}
		}
		if (m_timeToFall > m_randTime) //if time to fall is bigger than random time then fall is true
		{
			m_fall = true;
		}
	}
	MyCube::update(dt);
}

/// <summary>
/// Get top right position
/// </summary>
/// <returns></returns>
sf::Vector3f WallCube::getPosRight() const
{
	return m_positionTopRight;
}

/// <summary>
/// Get top left position
/// </summary>
/// <returns></returns>
sf::Vector3f WallCube::getPosLeft() const
{
	return m_positionTopLeft;
}

/// <summary>
/// Set stop bool
/// </summary>
/// <param name="check"></param>
void WallCube::setStop(bool check)
{
	m_stop = check;
}

/// <summary>
/// Generate randome number between 0.5 and 2
/// </summary>
/// <returns></returns>
float WallCube::genRandTime()
{
	int num1 = rand() % 16 + 5; // gen num 5 - 20

	float num = num1 / 10.0f;

	return num;
}
