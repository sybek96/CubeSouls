#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <Debug.h>
#include<iostream>
#include<fstream>
#include <string>



#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <memory>
#include "ImgData.h"
#include "MyCube.h"
#include "IDs.h"
#include "WallCube.h"
#include "PlayerCube.h"
#include "Road.h"

class Game
{
public:
	Game(sf::ContextSettings settings);
	~Game();
	void run();
	std::string Game::loadShaderFile(std::string type, std::string contents);
	void cleanUpCubeVector();
	void checkCollision();
	float randNumX();
	void setUpArrayAndBuffer(IDs & ids, const GLuint & sizeBuffer, const GLuint & sizeIndex, const GLuint index[]);
	void setUpShader(GLuint & id, const GLchar** src, const GLenum & type);
	void setUpProgram(GLuint & progID, const GLuint & vsid, const GLuint & fsid);
	void spawnCubes();
	void restartGame();
private:
	enum class GameState{SPAWNING,PLAYING,OVER};
	sf::RenderWindow window;
	sf::Clock m_clock;
	sf::Time m_elapsed;

	const sf::Time TIME_PER_UPDATE = sf::seconds(1 / 60.0f);

	bool isRunning = false;
	void initialize();
	void update(double);
	void render();
	void unload();
	float m_timetospawn = 0;
	ImgData m_texture;
	ImgData m_texture2;
	//MyCube m_cube;
	std::string fileContentsVertex;
	std::string fileContentsFragment;
	std::vector<std::unique_ptr<WallCube>> m_cubes;
	const char* vs_src;
	const char* fs_src;
	IDs m_ids;
	IDs m_idsRoad;
	glm::mat4 m_view;
	std::unique_ptr<PlayerCube> m_playerCube;
	std::unique_ptr<Road> m_road;
	bool m_clearWalls;
	int m_lives;
	GameState m_currentGameState = GameState::SPAWNING;
	float m_wallSpeed;
	bool m_spawning;
	sf::Text m_text;
	sf::Font m_font;
	sf::CircleShape m_circle;
};

#endif