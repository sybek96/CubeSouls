#ifndef _WallCube
#define _WallCube
#include "MyCube.h"

class WallCube :
	public MyCube
{
public:
	WallCube(float, float, float, const glm::mat4 &, float speed
	);
	~WallCube();
	bool getActive() const;
	void update(double) override;
	sf::Vector3f getPosRight() const;
	sf::Vector3f getPosLeft() const;
	void setStop(bool check);
private:
	bool m_active;
	float m_moveSpeed;
	const float CRUMBLE_SPEED;
	bool m_stop;
	double m_time;
	double m_timeToFall;
	int m_direction;
	bool m_fall;
	const float FALL_SPEED;
};
#endif // !_WallCube
