#include <Game.h>



//const std::string filename = "coordinates.tga";
//const std::string filename1 = "cube.tga";
//const std::string filename = "grid.tga";
//const std::string filename = "grid_wip.tga";
const std::string filename = "minecraft.tga";
//const std::string filename = "texture.tga";
//const std::string filename = "texture_2.tga";
//const std::string filename = "uvtemplate.tga";





Game::Game(sf::ContextSettings settings)
	: window(sf::VideoMode(800, 600),
		"Introduction to OpenGL Texturing",
		sf::Style::Default,
		settings)
	, m_ids()
	, m_idsRoad()
	, m_view(glm::lookAt(
		glm::vec3(0.0f, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		glm::vec3(0.0f, 0.0f, 0.0f),	// Camera looking at origin
		glm::vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	))
	, m_playerCube(new PlayerCube(1.0f, 5.0f, 5.0f, m_view))
	, m_road(new Road(0.0f,0.0f,5.0f,m_view))
	, m_clearWalls(false)
	, m_lives(2)
	, m_wallSpeed(50.0f)
	, m_spawning(true)
	, m_circle(50.0f)
{
	m_circle.setFillColor(sf::Color::Cyan);
	m_circle.setPosition(sf::Vector2f(0.0f, 0.0f));
	if (!m_font.loadFromFile("./SNAP___.TTF"))
	{
		std::cout << "ERROR LOADING FONT" << std::endl;
	}
	m_text.setString("TOP KEK");
	m_text.setFont(m_font);
	m_text.setPosition(sf::Vector2f(0.0f,0.0f));
	m_text.setColor(sf::Color::Yellow);
	m_text.setCharacterSize(50u);
	auto seed = time(nullptr);
	DEBUG_MSG("Generating random seed:\n   - Seed: " + std::to_string(seed) + "\n");
	srand(seed);
	// Camera Matrix
	m_view = glm::lookAt(
		glm::vec3(m_playerCube->getPosLeft().x + 1, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		glm::vec3(m_playerCube->getPosLeft().x + 1, 0, 0),	// Camera looking at centre of player
		glm::vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	);
	m_road.reset(new Road(0.0f, 0.0f, 5.0f, m_view));
}

Game::~Game() {}


void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning)
	{
		m_elapsed += m_clock.restart();

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}

		while (m_elapsed > TIME_PER_UPDATE)
		{
			m_elapsed -= TIME_PER_UPDATE;
			update(TIME_PER_UPDATE.asSeconds());
		}

		cleanUpCubeVector();
		render();
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Calling Cleanup...");
#endif
	unload();

}

void Game::initialize()
{
	isRunning = true;
	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));
	std::string temp = loadShaderFile("Vertex", fileContentsVertex);
	const char* vs_src = temp.c_str(); //Vertex Shader Src

	std::string temp2 = loadShaderFile("Fragment", fileContentsFragment);
	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = temp2.c_str();; //Fragment Shader Src

	glewInit();
	m_texture.m_img_data = stbi_load(filename.c_str(), &m_texture.m_width, &m_texture.m_height, &m_texture.m_comp_count, 4); //add for next texture
																															 // Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);


	setUpArrayAndBuffer(m_ids, ((3 * MyCube::VERTICES) + (4 * MyCube::COLORS) + (2 * MyCube::UVS)) * sizeof(GLfloat), 3 * MyCube::INDICES * sizeof(GLuint), MyCube::s_INDICES);

	setUpShader(m_ids.m_vsid, reinterpret_cast<const GLchar**>(&vs_src), GL_VERTEX_SHADER);

	setUpShader(m_ids.m_fsid, reinterpret_cast<const GLchar**>(&fs_src), GL_FRAGMENT_SHADER);

	setUpProgram(m_ids.m_progID, m_ids.m_vsid, m_ids.m_fsid);

	//Use Progam on GPU
	glUseProgram(m_ids.m_progID);



	if (m_texture.m_img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_ids.m_to);
	glBindTexture(GL_TEXTURE_2D, m_ids.m_to);


	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D,					//2D Texture Image
		0,								//Mipmapping Level 
		GL_RGBA,						//GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		m_texture.m_width,				//Width
		m_texture.m_height,				//Height
		0,								//Border
		GL_RGBA,						//Bitmap
		GL_UNSIGNED_BYTE,				//Specifies Data type of image data
		m_texture.m_img_data			//Image Data
	);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	m_ids.m_positionID = glGetAttribLocation(m_ids.m_progID, "sv_position");
	m_ids.m_colorID = glGetAttribLocation(m_ids.m_progID, "sv_color");
	m_ids.m_uvID = glGetAttribLocation(m_ids.m_progID, "sv_uv");
	m_ids.m_textureID = glGetUniformLocation(m_ids.m_progID, "f_texture");
	m_ids.m_mvpID = glGetUniformLocation(m_ids.m_progID, "sv_mvp");
}

void Game::update(double dt)
{
#if (DEBUG >= 2)
	DEBUG_MSG("Updating...");
#endif
	switch (m_currentGameState)
	{
	case Game::GameState::SPAWNING:
		if (m_playerCube->getPosLeft().y > 0)
		{
			m_playerCube->update(dt);
		}
		else
		{
			m_playerCube->setSpawning(false);
			m_currentGameState = GameState::PLAYING;
		}
		break;
	case Game::GameState::PLAYING:
		m_playerCube->update(dt);	//update the player

		m_view = glm::lookAt(
			glm::vec3(m_playerCube->getPosLeft().x + 1, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
			glm::vec3(m_playerCube->getPosLeft().x + 1, 0, 0),	// Camera looking at centre of player
			glm::vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
		);
		m_timetospawn += dt;
		if (m_timetospawn > 0.7)
		{
			m_timetospawn -= 0.7;
			spawnCubes();
		}
		for (auto& cube : m_cubes) //update all walls
		{
			cube->update(dt);
		}
		checkCollision();
		if (m_clearWalls)
		{
			m_cubes.clear();
			m_timetospawn = 0.0f;
			spawnCubes();
			m_clearWalls = false;
		}
		if (m_lives == 0)
		{
			m_currentGameState = GameState::OVER;
		}
		break;
	case Game::GameState::OVER:
		for (auto& cube : m_cubes) //update all walls
		{
			cube->update(dt);
		}
		m_timetospawn += dt;
		if (m_timetospawn > 1.8)
		{
			m_playerCube->update(dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			restartGame();
		}
		break;
	default:
		break;
	}
	//std::cout << m_cubes.size() << std::endl;
}

void Game::render()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif

	//std::cout << m_playerCube->getPosLeft().x << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.25, 0.5, 0.8, 0.0f);

	//m_road->render(m_idsRoad);

	//m_cube.render();
	for (auto& cube : m_cubes)
	{
		cube->render(m_ids);
	}
	m_playerCube->render(m_ids);
	
	window.setActive(false);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	window.pushGLStates();

	//window.resetGLStates();
	
	window.draw(m_text);
	window.draw(m_circle);
	window.popGLStates();


	window.display();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void Game::unload()
{
	//m_cube.unload();
	stbi_image_free(m_texture.m_img_data);		//Free image
}


/// <summary>
/// loading the vertex shader details from txt file
/// </summary>
/// <returns></returns>
std::string Game::loadShaderFile(std::string type, std::string contents)
{
	std::ifstream myReadFile;
	std::string string;
	myReadFile.open(type + "Shader.txt");
	while (!myReadFile.eof()) // To get you all the lines.
	{
		getline(myReadFile, string); // Saves the line in STRING.
		contents.append(string + "\n"); // Prints our STRING.
	}
	myReadFile.close();
	std::cout << contents;
	return contents;
}

void Game::cleanUpCubeVector()
{
	auto current = m_cubes.begin();
	auto end = m_cubes.end();
	for (; current != end; )
	{
		if ((*current)->getActive() == false)
		{
			current = m_cubes.erase(current);
			end = m_cubes.end();
		}
		else
		{
			current++;
		}
	}
}
/// <summary>
/// Method to check a collision between the boxes
/// </summary>
void Game::checkCollision()
{
	for (auto & cube : m_cubes)
	{
		if ((cube->getPosLeft().x < m_playerCube->getPosLeft().x && cube->getPosRight().x > m_playerCube->getPosLeft().x) || (cube->getPosLeft().x < m_playerCube->getPosRight().x && cube->getPosRight().x > m_playerCube->getPosRight().x))
		{
			if (cube->getPosLeft().z < m_playerCube->getPosLeft().z && cube->getPosLeft().z > m_playerCube->getPosLeft().z - 2)
			{
				//std::cout << "COLLISION DETECTED!!!!!!!!" << std::endl;
				m_lives--;
				if (m_lives != 0)
				{
					m_playerCube->resetPosition();
					m_clearWalls = true;
				}
				else
				{
					for (auto & cube : m_cubes)
					{
						cube->setStop(true);
					}
					m_playerCube->setSquash(true);
				}
			}
		}
	}
}

/// <summary>
/// used to get a random x position
/// </summary>
/// <returns></returns>
float Game::randNumX()
{
	return rand() % 51 + (-25); //number between -25 and 25
}

void Game::setUpArrayAndBuffer(IDs & ids, const GLuint & sizeBuffer, const GLuint & sizeIndex, const GLuint index[])
{
	glGenBuffers(1, &ids.m_vbo); //Gen Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, ids.m_vbo);

	//Vertices 3 x,y,z , Colors 4 RGBA, UV/ST 2
	glBufferData(GL_ARRAY_BUFFER, sizeBuffer, nullptr, GL_STATIC_DRAW);
	glGenBuffers(1, &ids.m_vib); //Gen Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ids.m_vib);
	//Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndex, index, GL_STATIC_DRAW); //indices are in cube
}

void Game::setUpShader(GLuint & id, const GLchar ** src, const GLenum & type)
{
	GLint isCompiled = 0;
	DEBUG_MSG("Setting Up Shader");

	id = glCreateShader(type);
	glShaderSource(id, 1, src, nullptr);
	glCompileShader(id);

	//Check is Shader Compiled
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) 
	{
		DEBUG_MSG("Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Compilation Error");
	}
}

void Game::setUpProgram(GLuint & progID, const GLuint & vsid, const GLuint & fsid)
{
	GLint isLinked = 0;
	
	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();
	glAttachShader(progID, vsid);
	glAttachShader(progID, fsid);
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_TRUE) 
	{
		DEBUG_MSG("Shader Linked");
		glDetachShader(progID, vsid);
		glDetachShader(progID, fsid);
		glDeleteShader(vsid);
		glDeleteShader(fsid);
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}
}


void Game::spawnCubes()
{
	//m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -60.0f, m_view, m_wallSpeed)));
	//m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -64.0f, m_view, m_wallSpeed)));
	//m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -68.0f, m_view, m_wallSpeed)));
	//m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -70.0f, m_view, m_wallSpeed)));
	//m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -74.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -78.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -82.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -86.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -90.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -94.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -98.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -102.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -104.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -108.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -112.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -116.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -120.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -124.0f, m_view, m_wallSpeed)));
	m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, -128.0f, m_view, m_wallSpeed)));
	m_wallSpeed += 2.0f;
}

void Game::restartGame()
{
	m_currentGameState = GameState::SPAWNING;
	m_clearWalls = false;
	m_lives = 2;
	m_wallSpeed = 50.0f;
	m_cubes.clear();
	m_playerCube.reset(new PlayerCube(1.0f, 5.0f, 5.0f, m_view));
	m_view = glm::lookAt(
		glm::vec3(m_playerCube->getPosLeft().x + 1, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		glm::vec3(m_playerCube->getPosLeft().x + 1, 0, 0),	// Camera looking at centre of player
		glm::vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	);
	m_timetospawn = 0.0f;
}

