#include "Cube.h"



Cube::Cube(float xOffset, float yOffset, float zOffset) :
	m_xOffset(xOffset),
	m_yOffset(yOffset),
	m_zOffset(zOffset)
{
}


Cube::~Cube()
{
}

void Cube::initialize()
{
	/* Vertices counter-clockwise winding */
	//FRONT
	vertex[0].coordinate[0] = 0.5f + m_xOffset;		//tr f
	vertex[0].coordinate[1] = 0.5f + m_yOffset;
	vertex[0].coordinate[2] = 0.5f + m_zOffset;

	vertex[1].coordinate[0] = -0.5f + m_xOffset;	//tl f
	vertex[1].coordinate[1] = 0.5f + m_yOffset;
	vertex[1].coordinate[2] = 0.5f + m_zOffset;

	vertex[2].coordinate[0] = -0.5f + m_xOffset;	//bl f
	vertex[2].coordinate[1] = -0.5f + m_yOffset;
	vertex[2].coordinate[2] = 0.5f + m_zOffset;

	vertex[3].coordinate[0] = 0.5f + m_xOffset;		//br b
	vertex[3].coordinate[1] = -0.5f + m_yOffset;
	vertex[3].coordinate[2] = 0.5f + m_zOffset;




	//BACK
	vertex[4].coordinate[0] = 0.5f + m_xOffset;		//tr b
	vertex[4].coordinate[1] = 0.5f + m_yOffset;
	vertex[4].coordinate[2] = -0.5f + m_zOffset;

	vertex[5].coordinate[0] = -0.5f + m_xOffset;	//tl b
	vertex[5].coordinate[1] = 0.5f + m_yOffset;
	vertex[5].coordinate[2] = -0.5f + m_zOffset;

	vertex[6].coordinate[0] = -0.5f + m_xOffset;	//bl b
	vertex[6].coordinate[1] = -0.5f + m_yOffset;
	vertex[6].coordinate[2] = -0.5f + m_zOffset;

	vertex[7].coordinate[0] = 0.5f + m_xOffset;		//br b
	vertex[7].coordinate[1] = -0.5f + m_yOffset;
	vertex[7].coordinate[2] = -0.5f + m_zOffset;



	vertex[0].color[0] = 1.0f;		//Nevajo white
	vertex[0].color[1] = 0.870588f;
	vertex[0].color[2] = 0.678431;

	vertex[1].color[0] = 0.254902f; //Royal blue
	vertex[1].color[1] = 0.411765f;
	vertex[1].color[2] = 0.882353;

	vertex[2].color[0] = 1.0f;		//red
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 1.0f;		//magenta
	vertex[3].color[1] = 0.0f;
	vertex[3].color[2] = 1.0f;

	vertex[4].color[0] = 0.2f;		//Blue
	vertex[4].color[1] = 0.0f;
	vertex[4].color[2] = 1.0f;

	vertex[5].color[0] = 0.0f;		//cyan
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 1.0f;

	vertex[6].color[0] = 0.0f;		//green
	vertex[6].color[1] = 1.0f;
	vertex[6].color[2] = 0.0f;

	vertex[7].color[0] = 1.0f;		//yellow
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 0.0f;

	//front
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 0;   triangles[5] = 2;

	//Top
	triangles[6] = 5;	triangles[7] = 1;	triangles[8] = 0;
	triangles[9] = 5;	triangles[10] = 0;	triangles[11] = 4;

	//Back
	triangles[12] = 6;	triangles[13] = 5;	triangles[14] = 4;
	triangles[15] = 6;	triangles[16] = 4;	triangles[17] = 7;

	//Bottom
	triangles[18] = 2;	triangles[19] = 6;	triangles[20] = 7;
	triangles[21] = 2;	triangles[22] = 7;	triangles[23] = 3;

	//right
	triangles[24] = 7;	triangles[25] = 4;	triangles[26] = 0;
	triangles[27] = 7;	triangles[28] = 0;	triangles[29] = 3;

	//left
	triangles[30] = 2;	triangles[31] = 1;	triangles[32] = 5;
	triangles[33] = 2;	triangles[34] = 5;	triangles[35] = 6;




	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Cube::update()
{
}

void Cube::render()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex), vertex, GL_STATIC_DRAW);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/* Draw Triangle from VBO */

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
