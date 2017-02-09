#include "WallCube.h"



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
{
}


WallCube::~WallCube()
{
	//std::cout << "Deleting Wall Cube" << std::endl;
}

bool WallCube::getActive() const
{
	return m_active;
}

void WallCube::update(double dt)
{
	if (!m_stop)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, m_moveSpeed * dt));
		m_positionTopRight.z += m_moveSpeed * dt;
		m_positionTopLeft.z += m_moveSpeed * dt;
		if (m_positionTopRight.z > 10.0f)
		{
			m_active = false;
		}
	}
	else
	{
		m_time += dt;
		m_timeToFall += dt;
		if (!m_fall)
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
		else
		{
			model = glm::translate(model, glm::vec3(0.0f, -FALL_SPEED * dt,0.0f));
			m_positionTopRight.x -= -FALL_SPEED * dt;
			m_positionTopLeft.x -= -FALL_SPEED * dt;
			if (m_positionTopRight.y < -10.0f)
			{
				m_active = false;
			}
		}
		if (m_timeToFall > 0.5)
		{
			m_fall = true;
		}
	}
	MyCube::update(dt);
}

sf::Vector3f WallCube::getPosRight() const
{
	return m_positionTopRight;
}

sf::Vector3f WallCube::getPosLeft() const
{
	return m_positionTopLeft;
}

void WallCube::setStop(bool check)
{
	m_stop = check;
}
