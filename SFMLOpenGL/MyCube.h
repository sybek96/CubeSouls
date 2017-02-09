#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Debug.h>
#include "ImgData.h"
#include "IDs.h"

class MyCube
{
public:
	MyCube(const glm::mat4 & view);
	MyCube(float, float, float, const glm::mat4 &);
	~MyCube();
	virtual void update(double);
	virtual void render(const IDs & ids);
	//bool getActive() const;

	static const int VERTICES = 24;	// Total Number of Vertices
	static const int INDICES = 12;	// Total Number of Indexes
	static const int UVS = 48;	// Total Number of UVs
	static const int COLORS = 24;	// Total Number of Colors
	static const GLuint s_INDICES[36];

protected:

	glm::mat4 mvp;
	glm::mat4 projection;
	const glm::mat4 & m_view;
	glm::mat4 model;	// Model View Projection

	GLfloat m_vertices[72];

	float m_xOffset;
	float m_yOffset;
	float m_zOffset;

	//bool m_active;
	sf::Vector3f m_positionTopRight;
	sf::Vector3f m_positionTopLeft;

};

