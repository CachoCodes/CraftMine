Shader* globalShader = nullptr;
Texture* globalTexture = nullptr;
Camera* globalCamera = nullptr;
GLFWwindow* window = nullptr;
float contador = 0.0f;

const int RENDER_DISTANCE = 8;
const int CHUNKS_PER_FRAME = 1;

std::queue<std::pair<int, int>> chunkLoadQueue;
std::unordered_set<uint64_t> queuedChunks;

void RegenerateChunkByID(uint64_t id) {
	if (WORLD.contains(id)) {
		WORLD.at(id).GenerateMesh();
	}
}

void QueueChunksAroundPlayer(int playerChunkX, int playerChunkZ) {
	for (int x = playerChunkX - RENDER_DISTANCE; x <= playerChunkX + RENDER_DISTANCE; x++) {
		for (int z = playerChunkZ - RENDER_DISTANCE; z <= playerChunkZ + RENDER_DISTANCE; z++) {
			uint64_t id = ChunkIDHelper(x, z);

			if (!WORLD.contains(id) && !queuedChunks.contains(id)) {
				chunkLoadQueue.push({ x, z });
				queuedChunks.insert(id);
			}
		}
	}
}

void ProcessChunkLoadQueue() {
	for (int i = 0; i < CHUNKS_PER_FRAME && !chunkLoadQueue.empty(); i++) {
		auto [x, z] = chunkLoadQueue.front();
		chunkLoadQueue.pop();

		uint64_t id = ChunkIDHelper(x, z);
		queuedChunks.erase(id);

		if (WORLD.contains(id))
			continue;

		WORLD.try_emplace(id, x, z);
		WORLD.at(id).GenerateChunkData();

		std::unordered_set<uint64_t> chunksToRemesh;

		auto AddIfExists = [&](int cx, int cz) {
			uint64_t cid = ChunkIDHelper(cx, cz);

			if (WORLD.contains(cid)) {
				chunksToRemesh.insert(cid);
			}
			};

		AddIfExists(x, z);

		AddIfExists(x + 1, z);
		AddIfExists(x - 1, z);
		AddIfExists(x, z + 1);
		AddIfExists(x, z - 1);

		for (uint64_t cid : chunksToRemesh) {
			RegenerateChunkByID(cid);
		}
	}
}

void UnloadFarChunks(int playerChunkX, int playerChunkZ) {
	std::vector<uint64_t> chunksToDelete;

	for (auto& [id, chunk] : WORLD) {
		int dx = std::abs(chunk.getChunkX() - playerChunkX);
		int dz = std::abs(chunk.getChunkZ() - playerChunkZ);

		if (dx > RENDER_DISTANCE || dz > RENDER_DISTANCE) {
			chunksToDelete.push_back(id);
		}
	}

	for (uint64_t id : chunksToDelete) {
		WORLD.erase(id);
	}
}

void UpdateChunksAroundPlayer() {
	int playerChunkX = WorldToChunkCoord(globalCamera->Position.x);
	int playerChunkZ = WorldToChunkCoord(globalCamera->Position.z);

	if (playerChunkX == lastPlayerChunkX && playerChunkZ == lastPlayerChunkZ)
		return;

	lastPlayerChunkX = playerChunkX;
	lastPlayerChunkZ = playerChunkZ;

	std::vector<std::pair<int, int>> newChunks;

	// 1. Crear data de chunks nuevos
	for (int x = playerChunkX - RENDER_DISTANCE; x <= playerChunkX + RENDER_DISTANCE; x++) {
		for (int z = playerChunkZ - RENDER_DISTANCE; z <= playerChunkZ + RENDER_DISTANCE; z++) {
			uint64_t id = ChunkIDHelper(x, z);

			if (!WORLD.contains(id)) {
				WORLD.try_emplace(id, x, z);
				WORLD.at(id).GenerateChunkData();

				newChunks.push_back({ x, z });
			}
		}
	}

	// 2. Juntar chunks que necesitan remesh, sin duplicados
	std::unordered_set<uint64_t> chunksToRemesh;

	auto AddIfExists = [&](int x, int z) {
		uint64_t id = ChunkIDHelper(x, z);

		if (WORLD.contains(id)) {
			chunksToRemesh.insert(id);
		}
		};

	for (auto [x, z] : newChunks) {
		AddIfExists(x, z);

		AddIfExists(x + 1, z);
		AddIfExists(x - 1, z);
		AddIfExists(x, z + 1);
		AddIfExists(x, z - 1);
	}

	// 3. Regenerar cada chunk solo una vez
	for (uint64_t id : chunksToRemesh) {
		RegenerateChunkByID(id);
	}

	UnloadFarChunks(playerChunkX, playerChunkZ);
}

void InitEngine() {
	//EngineFunctions::DebugLinesView();
	globalCamera = new Camera(EngineData::WindowWidth, EngineData::WindowHeight, glm::vec3(0.0f, 115.0f, 0.0f));
	globalShader = new Shader("Resources/shaders/Perspective-Texture/vertex.glsl", "Resources/shaders/Perspective-Texture/fragment.glsl");
	globalTexture = new Texture("Resources/atlas.png", TextureFormat::RGBA);
	UniformLocations::init_Perspective_Texture(globalShader->ID);
	globalTexture->addtoVRAM();
	InitializeNoise(WORLD_SEED);
}

void mainloop() {
	contador += EngineData::deltaTime;
	if (contador > 3.0f) {
		contador = 0.0f;
		std::cout << "CamPos: x:" << globalCamera->Position.x << " y:" << globalCamera->Position.y << " z:" << globalCamera->Position.z << "\n";
	}
	globalShader->Activate();
	globalCamera->Inputs(window, EngineData::deltaTime);
	globalTexture->SendtoShader(UniformLocations::Texture);
	UpdateChunksAroundPlayer();
	globalCamera->Matrix(90.0f, 0.1f, 1000.0f, UniformLocations::CameraMatrix);
	for (auto& [clave, chunk] : WORLD) {
		chunk.sendModelMat();
		chunk.RenderChunk();
	}
}
void FinishEngine() {
	globalShader->Delete();
}