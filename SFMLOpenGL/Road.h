#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <IDs.h>

class Road
{
public:
	Road(float xOffset, float yOffset, float zOffset, const glm::mat4 & view);
	~Road();
	void render(const IDs & ids);

	

	static const GLuint s_VERTICES_NR = 3u * 4u;

	static const GLuint s_COLOURS_NR = 4u * 4u;
	static const GLuint s_UVS_NR = 2u * 4u;
	static const GLuint s_INDICES_NR = 2u * 3u;

	static const GLuint s_VERTICES_SIZE = s_VERTICES_NR * sizeof(GLfloat);
	static const GLuint s_COLOURS_SIZE = s_COLOURS_NR * sizeof(GLfloat);
	static const GLuint s_UVS_SIZE = s_UVS_NR * sizeof(GLfloat);

	static const GLuint s_INDICES_SIZE = s_INDICES_NR * sizeof(GLuint);
	
	static const GLuint s_BUFFER_SIZE = s_VERTICES_SIZE + s_COLOURS_SIZE + s_UVS_SIZE;

	static const GLuint indices[s_INDICES_NR];

private:
	glm::vec3 m_position;
	float m_width;
	float m_height;

	GLfloat vertices[s_VERTICES_NR] =
	{
		// Bottom Face
		-1.00f, -1.00f, -1.00f, // [4]	// (12)
		1.00f, -1.00f, -1.00f, // [5]	// (13)
		1.00f, -1.00f,  1.00f, // [1]	// (14)
		-1.00f, -1.00f,  1.00f, // [0]	// (15)
	};

	GLfloat colours[s_COLOURS_NR] =
	{
		// Bottom Face
		0.0f, 1.0f, 1.0f, 1.0f, // [4]	// (12)
		0.0f, 1.0f, 1.0f, 1.0f, // [5]	// (13)
		0.0f, 1.0f, 1.0f, 1.0f, // [1]	// (14)
		0.0f, 1.0f, 1.0f, 1.0f, // [0]	// (15)
	};
	GLfloat uvs[s_UVS_NR] =
	{
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.1f, 0.0f
	};

	

	const glm::mat4 & m_view;
	const glm::mat4 m_projection;
	glm::mat4 m_model;
	glm::mat4 m_mvp;

	float m_xOffset;
	float m_yOffset;
	float m_zOffset;
};

