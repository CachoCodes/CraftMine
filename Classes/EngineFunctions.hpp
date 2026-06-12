namespace UniformLocations {
	GLuint ModelMatrix = 0;
	GLuint CameraMatrix = 0;
	GLuint Texture = 0;
	void init_Perspective_Texture(GLuint shaderID) {
		ModelMatrix = glGetUniformLocation(shaderID,"ModelMatrix");
		CameraMatrix = glGetUniformLocation(shaderID, "CameraMatrix");;
		Texture = glGetUniformLocation(shaderID, "Texture");;
	}
}
enum class TextureFormat {
	RGB,
	RGBA
};

enum BlockType : unsigned char {
	AIR = 0,
	DIRT = 1,
	GRASS = 2,
	GRAVEL = 3,
	STONE = 4,
	WATER = 5,
	COAL_ORE = 6,
	BEDROCK = 7,
	GLASS = 8,
	IRON_ORE = 9,
	SAND = 10,
	COBBLESTONE = 11,
	OAK_PLANKS = 12,
	OAK_LOG = 13,
	OAK_LEAVES = 14,
	BLOCK_NOT_LOADED = 255
};


FastNoiseLite terrainNoise;
FastNoiseLite caveNoise;

void InitializeNoise(int seed) {
	terrainNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	terrainNoise.SetSeed(seed);
	terrainNoise.SetFrequency(0.005f);
	terrainNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
	terrainNoise.SetFractalOctaves(2);
	caveNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	caveNoise.SetSeed(seed * 3 % 78 * 67);
	caveNoise.SetFrequency(0.04f);
}

namespace EngineData{
	const int CHUNKWIDTH = 16;
	const int CHUNKHEIGHT = 256;
	int WindowWidth = 1280;
	int WindowHeight = 720;
    float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	int FPS = 0;
	int renderDistance = 8;
}

namespace EngineFunctions{
    void DebugLinesView() {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void ClearColor(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
		glClearColor(x, y, z, w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	float DeltaTime() {
		float currentFrame = glfwGetTime();
		EngineData::deltaTime = currentFrame - EngineData::lastFrame;
		EngineData::lastFrame = currentFrame;
		return EngineData::deltaTime;
	}

	void ClearDepthBuffer() {
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	int CalculateFps(float deltaTime) {
		EngineData::FPS = (int)(1.0f / deltaTime);
		return EngineData::FPS;
	}

	std::string get_file_contents(const std::string& filename) {
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << filename << "\n";
		}
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

	void shader_compilation_status(GLuint shaderID) {
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << "\n";
		}
	}

	void shader_linking_status(GLuint programID) {
		GLint success;
		GLchar infoLog[512];
		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(programID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << "\n";
		}
	}
}
