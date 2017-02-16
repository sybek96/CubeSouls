#ifndef _WallCube
#define _WallCube
#include "MyCube.h"

class WallCube :
	public MyCube
{
public:
	//constructor
	WallCube(float, float, float, const glm::mat4 &, float speed);

	//destructor
	~WallCube();

	//get active bool
	bool getActive() const;

	//update
	void update(double) override;

	//get right position
	sf::Vector3f getPosRight() const;

	//get left position
	sf::Vector3f getPosLeft() const;

	//set the stop bool
	void setStop(bool check);

	//generate a random value for time to fall
	float genRandTime();

private:
	//active bool
	bool m_active;

	//movement speed
	float m_moveSpeed;

	//crumble speed
	const float CRUMBLE_SPEED;

	//stop moving bool
	bool m_stop;

	//time
	double m_time;

	//time to fall
	double m_timeToFall;

	//direction of movement (-1 left / 1 right)
	int m_direction;

	//fall bool
	bool m_fall;

	//falling speed
	const float FALL_SPEED;

	//a random time
	float m_randTime;
};
#endif // !_WallCube
