#ifndef _PLAYER_CUBE
#define _PLAYER_CUBE

#include "MyCube.h"
class PlayerCube :
	public MyCube
{
public:
	//constructor
	PlayerCube(float, float, float, const glm::mat4 &);

	//update
	void update(double) override;

	//get top right position
	sf::Vector3f getPosRight() const;

	//get top left position
	sf::Vector3f getPosLeft() const;

	//reset cube position
	void resetPosition();

	//set squash method
	void setSquash(bool check);

	//change spawning bool
	void setSpawning(bool check);

	//destructor
	~PlayerCube();
private:
	//cube move speed
	const float MOVE_SPEED;

	//squash bool
	bool m_squash;

	//spawning bool
	bool m_spawning;
};

#endif // !_PLAYER_CUBE
