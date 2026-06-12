//Rehacer parte de Chunk.hpp
Shader* globalShader = nullptr;
Texture* globalTexture = nullptr;
Camera* globalCamera = nullptr;
GLFWwindow* window = nullptr;
float contador = 0.0f;

void InitEngine() {
	//EngineFunctions::DebugLinesView();
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dist(1, 69420);

	globalCamera = new Camera(EngineData::WindowWidth, EngineData::WindowHeight, glm::vec3(0.0f, 115.0f, 0.0f));
	globalShader = new Shader("Resources/shaders/Perspective-Texture/vertex.glsl", "Resources/shaders/Perspective-Texture/fragment.glsl");
	globalTexture = new Texture("Resources/atlas.png", TextureFormat::RGBA);
	UniformLocations::init_Perspective_Texture(globalShader->ID);
	InitializeNoise(dist(rng));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++){
			WORLD.insert(std::make_pair(ChunkIDHelper(i, j), Chunk(i, j)));
			WORLD[ChunkIDHelper(i, j)].GenerateChunkData();
		}
	}
	WORLD[ChunkIDHelper(3, 3)].addTree(3, WORLD[ChunkIDHelper(3,3)].getHighestGround(3,3), 3);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			WORLD[ChunkIDHelper(i, j)].GenerateMesh();
		}
	}
	globalTexture->addtoVRAM();
}

void mainloop() {
	contador += EngineData::deltaTime;
	if (contador > 3.0f) {
		contador = 0.0f;
		std::cout << "CamPos: x:" << globalCamera->Position.x << " y:" << globalCamera->Position.y << " z:" << globalCamera->Position.z << "\n";
	}
	globalShader->Activate();
	globalCamera->Inputs(window, EngineData::deltaTime);
	globalCamera->Matrix(90.0f, 0.1f, 1000.0f, UniformLocations::CameraMatrix);
	globalTexture->SendtoShader(UniformLocations::Texture);
	for (auto& [clave, chunk] : WORLD) {
		chunk.sendModelMat();
		chunk.RenderChunk(); // Renderiza directamente cada chunk existente
	}
}
void FinishEngine() {
	globalShader->Delete();
}