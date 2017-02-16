#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <IDs.h>

class Road
{
public:
	//constructor
	Road(float xOffset, float yOffset, float zOffset, const glm::mat4 & view);

	//destructor
	~Road();

	//render
	void render(const IDs & ids);


	static const GLuint s_VERTICES_NR = 3u * 4u; //number of vertices
	static const GLuint s_COLOURS_NR = 4u * 4u; //colour number
	static const GLuint s_UVS_NR = 2u * 4u; //uv's number
	static const GLuint s_INDICES_NR = 2u * 3u; //indices number

	static const GLuint s_VERTICES_SIZE = s_VERTICES_NR * sizeof(GLfloat); //vertices size
	static const GLuint s_COLOURS_SIZE = s_COLOURS_NR * sizeof(GLfloat); //colour size
	static const GLuint s_UVS_SIZE = s_UVS_NR * sizeof(GLfloat); //uvs size

	static const GLuint s_INDICES_SIZE = s_INDICES_NR * sizeof(GLuint); //indices size
	
	static const GLuint s_BUFFER_SIZE = s_VERTICES_SIZE + s_COLOURS_SIZE + s_UVS_SIZE; //buffer size

	static const GLuint indices[s_INDICES_NR]; //indices

private:
	//indices
	glm::vec3 m_position;

	//cube width
	float m_width;

	//cube height
	float m_height;

	//vertices
	GLfloat vertices[s_VERTICES_NR] =
	{
		// Bottom Face
		-1.00f, -1.00f, -1.00f, // [4]	// (12)
		1.00f, -1.00f, -1.00f, // [5]	// (13)
		1.00f, -1.00f,  1.00f, // [1]	// (14)
		-1.00f, -1.00f,  1.00f, // [0]	// (15)
	};

	//colours
	GLfloat colours[s_COLOURS_NR] =
	{
		// Bottom Face
		0.0f, 1.0f, 1.0f, 1.0f, // [4]	// (12)
		0.0f, 1.0f, 1.0f, 1.0f, // [5]	// (13)
		0.0f, 1.0f, 1.0f, 1.0f, // [1]	// (14)
		0.0f, 1.0f, 1.0f, 1.0f, // [0]	// (15)
	};

	//uvs
	GLfloat uvs[s_UVS_NR] =
	{
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.1f, 0.0f
	};

	//view matrix
	const glm::mat4 & m_view;

	//projection matrix
	const glm::mat4 m_projection;

	//model matrix
	glm::mat4 m_model;

	//matrix view projection
	glm::mat4 m_mvp;

	//x offset
	float m_xOffset;
	
	//y offset
	float m_yOffset;

	//z offset
	float m_zOffset;
};

