#include <Game.h>



//const std::string filename = "coordinates.tga";
//const std::string filename1 = "cube.tga";
//const std::string filename = "grid.tga";
//const std::string filename = "grid_wip.tga";
//const std::string filename = "minecraft.tga";
const std::string filename = "neoncube.png";
//const std::string filename = "texture.tga";
//const std::string filename = "texture_2.tga";
//const std::string filename = "uvtemplate.tga";

//COLORS
static sf::Vector3f const WHITE = sf::Vector3f(255.0f, 255.0f, 255.0f);


/// <summary>
/// Game constructor
/// </summary>
/// <param name="settings"></param>
Game::Game(sf::ContextSettings settings)
	: window(sf::VideoMode(800, 600),
		"Introduction to OpenGL Texturing",
		sf::Style::Default,
		settings)
	, m_ids()
	, m_idsRoad()
	, m_view(glm::lookAt(
		glm::vec3(0.0f, 3.0f, 10.0f),	// Camera (x,y,z), in World Space
		glm::vec3(0.0f, 0.0f, 0.0f),	// Camera looking at origin
		glm::vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	))
	, m_playerCube(new PlayerCube(1.0f, 5.0f, 5.0f, m_view))
	, m_clearWalls(false)
	, m_lives(2)
	, m_currentGameState(GameState::SPLASH_SCREEN)
	, m_wallSpeed(50.0f)
	, m_spawning(true)
	, m_distance(0)
	, m_secondCounterSplash(0)
	, m_alphaLogo(0)
	, m_alphaSplashUp(true)
	, m_screenCenter(0,0)
{
	m_screenCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
	auto seed = time(nullptr);
	DEBUG_MSG("Generating random seed:\n   - Seed: " + std::to_string(seed) + "\n");
	srand(seed);
	// Camera Matrix
	m_view = glm::lookAt(
		glm::vec3(m_playerCube->getPosLeft().x + 1, 3.0f, 10.0f),	// Camera (x,y,z), in World Space
		glm::vec3(m_playerCube->getPosLeft().x + 1, 0, 0),	// Camera looking at centre of player
		glm::vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	);
}

/// <summary>
/// game destructor
/// </summary>
Game::~Game() {}

/// <summary>
/// main game loop
/// </summary>
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

/// <summary>
/// Method to initialise the game
/// </summary>
void Game::initialize()
{
	window.pushGLStates();
	if (!m_font.loadFromFile("./SNAP____.TTF")) //loading the font
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	if (!m_backgroundTexture.loadFromFile("./background1.png")) //loading background texture
	{
		std::string s("Error loading background texture");
		throw std::exception(s.c_str());
	}
	if (!m_heartTexture.loadFromFile("./heart1.png")) //loading heart texture
	{
		std::string s("Error loading heart texture");
		throw std::exception(s.c_str());
	}
	if (!m_SplashLogoTexture.loadFromFile("./Logo.png")) //loading logo texture
	{
		std::string s("Error loading logo texture");
		throw std::exception(s.c_str());
	}
	m_distanceText.setColor(sf::Color(255, 255, 255, 170));
	m_distanceText.setPosition(100.f, 20.f);
	//setting up hearts
	m_heart1.setTexture(m_heartTexture);
	m_heart2.setTexture(m_heartTexture);
	m_heart1.setPosition(sf::Vector2f(500.0f, 20.0f));
	m_heart1.setScale(0.25f, 0.25f);
	m_heart2.setPosition(sf::Vector2f(550.0f, 20.0f));
	m_heart2.setScale(0.25f, 0.25f);
	//making the background texture bind to background sprite
	m_backgroundSprite.setTexture(m_backgroundTexture);
	//Dealing with splash screen
	m_splashLogoSprite.setTexture(m_SplashLogoTexture);
	m_splashLogoSprite.setOrigin(m_splashLogoSprite.getGlobalBounds().width / 2, m_splashLogoSprite.getGlobalBounds().height / 2);
	m_splashLogoSprite.setPosition(m_screenCenter);
	m_splashLogoSprite.setColor(sf::Color(0.0f, 0.0f, 0.0f, m_alphaLogo));
	m_splashLogoSprite.setScale(0.8f, 0.8f);
	m_distanceText.setFont(m_font);
	window.popGLStates();
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

/// <summary>
/// The update loop
/// </summary>
/// <param name="dt">time</param>
void Game::update(double dt)
{
#if (DEBUG >= 2)
	DEBUG_MSG("Updating...");
#endif
	switch (m_currentGameState)
	{
	case Game::GameState::SPLASH_SCREEN:
		if (m_alphaSplashUp) //increse alpha while below 254 then decrease it to below 1 (fade in and out effect)
		{
			m_alphaLogo += 0.7f;
			if (m_alphaLogo > 254)
			{
				m_alphaSplashUp = false;
			}
		}
		else
		{
			if (m_alphaLogo > 1)
			{
				m_alphaLogo -= 0.9f;
			}
		}
		m_splashLogoSprite.setColor(sf::Color(WHITE.x, WHITE.y, WHITE.z, m_alphaLogo));
		m_secondCounterSplash += dt * 100; //add time since last update
		if (m_secondCounterSplash >= 700) //check if 7 sec is up switch to title
		{
			m_currentGameState = GameState::SPAWNING;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))	//alternatively press space to skip splash screen
		{
			m_currentGameState = GameState::SPAWNING;
		}
		break;
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
		m_distance += m_wallSpeed / 500;
		m_view = glm::lookAt(
			glm::vec3(m_playerCube->getPosLeft().x + 1, 3.0f, 10.0f),	// Camera (x,y,z), in World Space
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
		m_distanceText.setString("Distance: " + std::to_string(static_cast<int>(m_distance)));
		break;
	case Game::GameState::OVER:
		for (auto& cube : m_cubes) //update all walls
		{
			cube->update(dt);
		}
		m_timetospawn += dt;
		if (m_timetospawn > 3.5f)
		{
			m_distanceText.setString("Distance: " + std::to_string(static_cast<int>(m_distance)) + "\nPress space to restart");
			m_distanceText.setPosition(m_screenCenter.x - 160.0f, m_screenCenter.y - 50.0f);
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
}

/// <summary>
/// Render method for drawing to screen
/// </summary>
void Game::render()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	switch (m_currentGameState)
	{
	case Game::GameState::SPLASH_SCREEN:
		window.pushGLStates();
		window.draw(m_backgroundSprite);
		window.draw(m_splashLogoSprite);
		window.popGLStates();
		m_playerCube->render(m_ids);
		break;
	case Game::GameState::SPAWNING:
		window.pushGLStates();

		window.draw(m_backgroundSprite);
		window.draw(m_distanceText);
		if (m_lives > 1)
		{
			window.draw(m_heart2);
		}
		if (m_lives > 0)
		{
			window.draw(m_heart1);
		}
		// Restore OpenGL render states
		// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7

		window.popGLStates();

		for (auto& cube : m_cubes)
		{
			cube->render(m_ids);
		}
		m_playerCube->render(m_ids);
		break;
	case Game::GameState::PLAYING:
		window.pushGLStates();

		window.draw(m_backgroundSprite);
		window.draw(m_distanceText);
		if (m_lives > 1)
		{
			window.draw(m_heart2);
		}
		if (m_lives > 0)
		{
			window.draw(m_heart1);
		}
		window.popGLStates();
		for (auto& cube : m_cubes)
		{
			cube->render(m_ids);
		}
		m_playerCube->render(m_ids);
		break;
	case Game::GameState::OVER:
		window.pushGLStates();
		window.draw(m_backgroundSprite);
		window.draw(m_distanceText);
		if (m_lives > 1)
		{
			window.draw(m_heart2);
		}
		if (m_lives > 0)
		{
			window.draw(m_heart1);
		}
		// Restore OpenGL render states
		// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7

		window.popGLStates();
		for (auto& cube : m_cubes)
		{
			cube->render(m_ids);
		}
		m_playerCube->render(m_ids);
		break;
	default:
		break;
	}
	window.display();
}

/// <summary>
/// Unload the image data
/// </summary>
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

/// <summary>
/// Clean up the wall vector
/// will check inactive cubes and clear them from the vector
/// </summary>
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

/// <summary>
/// Setting up the buffer and array
/// </summary>
/// <param name="ids"></param>
/// <param name="sizeBuffer"></param>
/// <param name="sizeIndex"></param>
/// <param name="index"></param>
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

/// <summary>
/// Setting up a shader
/// </summary>
/// <param name="id"></param>
/// <param name="src"></param>
/// <param name="type"></param>
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

/// <summary>
/// Setting up a program to run on GPU
/// </summary>
/// <param name="progID"></param>
/// <param name="vsid"></param>
/// <param name="fsid"></param>
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

/// <summary>
/// Spawning cubes method will spawn a wave of cubes
/// </summary>
void Game::spawnCubes()
{
	float start = -78.0f;
	for (int i = 0; i < 13; i++)
	{
		m_cubes.push_back(std::unique_ptr<WallCube>(new WallCube(m_playerCube->getPosLeft().x + randNumX(), 1.0f, start, m_view, m_wallSpeed)));
		start -= 8;
	}
	m_wallSpeed += 2.0f;
}

/// <summary>
/// Restart the game
/// reset all variables to initial values
/// </summary>
void Game::restartGame()
{
	m_currentGameState = GameState::SPAWNING;
	m_clearWalls = false;
	m_lives = 2;
	m_wallSpeed = 50.0f;
	m_cubes.clear();
	m_playerCube.reset(new PlayerCube(1.0f, 5.0f, 5.0f, m_view));
	m_view = glm::lookAt(
		glm::vec3(m_playerCube->getPosLeft().x + 1, 3.0f, 10.0f),	// Camera (x,y,z), in World Space
		glm::vec3(m_playerCube->getPosLeft().x + 1, 0, 0),	// Camera looking at centre of player
		glm::vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	);
	m_timetospawn = 0.0f;
	m_distance = 0;
	m_distanceText.setPosition(100.f, 20.f);
	m_distanceText.setString("Distance: " + std::to_string(static_cast<int>(m_distance)));
}

