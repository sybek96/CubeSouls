#ifndef _PLAYER_CUBE
#define _PLAYER_CUBE

#include "MyCube.h"
class PlayerCube :
	public MyCube
{
public:
	PlayerCube(float, float, float, const glm::mat4 &);
	void update(double) override;
	sf::Vector3f getPosRight() const;
	sf::Vector3f getPosLeft() const;
	void resetPosition();
	void setSquash(bool check);
	void setSpawning(bool check);
	~PlayerCube();
private:
	const float MOVE_SPEED;
	bool m_squash;
	bool m_spawning;
};

#endif // !_PLAYER_CUBE
