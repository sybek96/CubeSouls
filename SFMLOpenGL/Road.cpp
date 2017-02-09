#include "Road.h"

const GLuint Road::indices[Road::s_INDICES_NR]=
{
	// bottom Face
	0u, 1u, 2u,
	2u, 3u, 0u
};

Road::Road(float xOffset, float yOffset, float zOffset, const glm::mat4 & view)
	: m_view(glm::lookAt(
		glm::vec3(2.0f, 4.0f, 10.f),
		glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	))
	, m_projection(glm::perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		0.1f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
	))
	, m_model(glm::mat4(1.0f))
	, m_mvp(1.0f)
	, m_xOffset(xOffset)
	, m_yOffset(yOffset)
	, m_zOffset(zOffset)
{
	m_model = glm::translate(m_model, glm::vec3(m_xOffset, m_yOffset, m_zOffset));
	m_model = glm::scale(m_model, glm::vec3(1.0f, 1.0f, 1.0f));
	m_mvp = m_projection * m_view * m_model;
}


Road::~Road()
{
}

void Road::render(const IDs & ids)
{
	//glDisable(GL_DEPTH_TEST);

	glUseProgram(ids.m_progID);

	//VBO Data....vertices, colors and UV's appended
	glBufferSubData(GL_ARRAY_BUFFER, 0, s_VERTICES_SIZE, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, s_VERTICES_SIZE, s_COLOURS_SIZE, colours);
	glBufferSubData(GL_ARRAY_BUFFER, (s_VERTICES_SIZE + s_COLOURS_SIZE), s_UVS_SIZE, uvs);

	// Send transformation to shader mvp uniform
	glUniformMatrix4fv(ids.m_mvpID, 1, GL_FALSE, &m_mvp[0][0]);

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE1);
	glUniform1i(ids.m_textureID, 0);

	//Set pointers for each parameter (with appropriate starting positions)
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(ids.m_positionID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glVertexAttribPointer(ids.m_colorID, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(s_VERTICES_SIZE));
	glVertexAttribPointer(ids.m_uvID, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(s_VERTICES_SIZE + s_COLOURS_SIZE));

	//Enable Arrays
	glEnableVertexAttribArray(ids.m_positionID);
	glEnableVertexAttribArray(ids.m_colorID);
	glEnableVertexAttribArray(ids.m_uvID);

	//Draw Element Arrays
	glDrawElements(GL_TRIANGLES, s_INDICES_NR, GL_UNSIGNED_INT, NULL);

	//Disable Arrays
	glDisableVertexAttribArray(ids.m_positionID);
	glDisableVertexAttribArray(ids.m_colorID);
	glDisableVertexAttribArray(ids.m_uvID);

	//glEnable(GL_DEPTH_TEST);
}
