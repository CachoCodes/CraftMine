class Chunk;


inline uint64_t ChunkIDHelper(int x, int z) {
	return (uint64_t(x) << 32) ^ uint32_t(z);
}

struct PendingBlock {
	int x;
	int y;
	int z;
	BlockType type;
};

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<int> dist(1, 69420);

uint32_t WORLD_SEED = dist(rng);

std::unordered_map<uint64_t, Chunk> WORLD;
std::unordered_map<uint64_t, std::vector<PendingBlock>> PENDING_BLOCKS;

uint32_t Hash2D(int x, int z, uint32_t seed);

int WorldToChunkCoordInt(int worldCoord);
int WorldToLocalCoord(int worldCoord, int chunkCoord);

void AddBlockGlobal(int worldX, int y, int worldZ, BlockType blockID);
void ApplyPendingBlocksToChunk(int chunkX, int chunkZ);
void AddTreeGlobal(int worldX, int y, int worldZ);

BlockType getBlockGlobal(int x, int y, int z, int chunkX, int chunkZ);

class Chunk {
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	glm::mat4 model = glm::mat4(1.0f);
	int chunkX, chunkZ;
	BlockType ChunkData[EngineData::CHUNKWIDTH * EngineData::CHUNKHEIGHT * EngineData::CHUNKWIDTH];
	int index_num = 0;

	void DeleteMesh() {
		if (EBO != 0) {
			glDeleteBuffers(1, &EBO);
			EBO = 0;
		}

		if (VBO != 0) {
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}

		if (VAO != 0) {
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
	}
	//Mesh Builders
	void placeTopface(int x, int y, int z, BlockType blockID) {
		//Y+
		// Add vertices and indices for the top face of the block at (x, y, z) based on its blockID
		if (blockID == BlockType::GRASS) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(1.0f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::DIRT) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(1.0f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(1.0f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.75f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::STONE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(1.0f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.75f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::WATER) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.4375f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.4375f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.4375f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.4375f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::COAL_ORE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::BEDROCK) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::GLASS) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}

		else if (blockID == BlockType::IRON_ORE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::GRAVEL) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::SAND) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::COBBLESTONE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::OAK_PLANKS) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(0.25f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.0f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::OAK_LOG) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.25f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.0f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::OAK_LEAVES) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(0.25f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.0f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.0f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2); // Top face triangle 2
			index_num += 4;
		}
	}

	void placeBottomface(int x, int y, int z, BlockType blockID) {
		//Y-
		// Add vertices and indices for the top face of the block at (x, y, z) based on its blockID
		if (blockID == BlockType::GRASS) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(1.0f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(1.0f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.75f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::DIRT) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(1.0f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(1.0f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.75f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::STONE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(1.0f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.75f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::WATER) {
			return;
		}
		else if (blockID == BlockType::COAL_ORE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::BEDROCK) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::GLASS) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}

		else if (blockID == BlockType::IRON_ORE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::GRAVEL) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::SAND) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::COBBLESTONE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::OAK_PLANKS) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(0.25f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.0f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::OAK_LOG) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.25f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.0f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::OAK_LEAVES) {
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(0.25f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.0f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.0f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
	}

	void placeRightface(int x, int y, int z, BlockType blockID) {
	//X+
	if (blockID == BlockType::GRASS) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f);  vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::DIRT) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::STONE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::WATER) {
		return;
	}
	else if (blockID == BlockType::COAL_ORE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::BEDROCK) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::GLASS) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::IRON_ORE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::GRAVEL) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::SAND) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::COBBLESTONE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_PLANKS) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LOG) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LEAVES) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
}
	
	void placeLeftface(int x, int y, int z, BlockType blockID) {
	//X-
	if (blockID == BlockType::GRASS) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f);  vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::DIRT) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::STONE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::WATER) {
		return;
	}
	else if (blockID == BlockType::COAL_ORE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::BEDROCK) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::GLASS) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::IRON_ORE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::GRAVEL) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::SAND) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::COBBLESTONE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_PLANKS) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LOG) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LEAVES) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 1);
		indices.push_back(index_num); indices.push_back(index_num + 3); indices.push_back(index_num + 2);
		index_num += 4;
	}
}

	void placeFrontface(int x, int y, int z, BlockType blockID) {
	//Z+
	if (blockID == BlockType::GRASS) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f);  vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::DIRT) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::STONE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::WATER) {
		return;
	}
	else if (blockID == BlockType::COAL_ORE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::BEDROCK) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::GLASS) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::IRON_ORE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::GRAVEL) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::SAND) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::COBBLESTONE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_PLANKS) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LOG) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LEAVES) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
}

	void placeBackface(int x, int y, int z, BlockType blockID) {
	//Z-
	if (blockID == BlockType::GRASS) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f);  vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::DIRT) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::STONE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::WATER) {
		return;
	}
	else if (blockID == BlockType::COAL_ORE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::BEDROCK) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::GLASS) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::IRON_ORE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::GRAVEL) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::SAND) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::COBBLESTONE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_PLANKS) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LOG) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LEAVES) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
}
	//Mesh Builders
public:
	Chunk(){}
	Chunk(int x, int z) {
		chunkX = x;
		chunkZ = z;
		model = glm::translate(model, glm::vec3(chunkX * EngineData::CHUNKWIDTH, 0.0f, chunkZ * EngineData::CHUNKWIDTH));
		std::cout << " X:" << chunkX << " Z:" << chunkZ;
	}
	~Chunk() {
		DeleteMesh();
	}

	int getChunkX() const {
		return chunkX;
	}

	int getChunkZ() const {
		return chunkZ;
	}

	//Terrain Generators
	void addTree(int x, int y, int z) {
		int worldX = chunkX * EngineData::CHUNKWIDTH + x;
		int worldZ = chunkZ * EngineData::CHUNKWIDTH + z;

		AddTreeGlobal(worldX, y, worldZ);
	}

	int getHighestGround(int x, int z) {
		for (int i = EngineData::CHUNKHEIGHT - 2; i >= 0; --i) {
			if (getBlock(x, i + 1, z) == BlockType::AIR &&
				getBlock(x, i, z) == BlockType::GRASS) {
				return i + 1;
			}
		}

		return 0;
	}

	void GenerateTrees() {
		for (int z = 0; z < EngineData::CHUNKWIDTH; z++) {
			for (int x = 0; x < EngineData::CHUNKWIDTH; x++) {
				int y = getHighestGround(x, z);

				if (y <= 0)
					continue;

				if (y + 7 >= EngineData::CHUNKHEIGHT)
					continue;

				int worldX = chunkX * EngineData::CHUNKWIDTH + x;
				int worldZ = chunkZ * EngineData::CHUNKWIDTH + z;

				uint32_t hash = Hash2D(worldX, worldZ, WORLD_SEED);

				// Más bajo = menos árboles
				if (hash % 1000 < 8) {
					AddTreeGlobal(worldX, y, worldZ);
				}
			}
		}
	}

	bool isInsideLocalBlock(int x, int y, int z) const {
		return x >= 0 && x < EngineData::CHUNKWIDTH &&
			z >= 0 && z < EngineData::CHUNKWIDTH &&
			y >= 0 && y < EngineData::CHUNKHEIGHT;
	}

	void setBlock(int x, int y, int z, BlockType blockID) {
		if (!isInsideLocalBlock(x, y, z))
			return;

		ChunkData[
			y * EngineData::CHUNKWIDTH * EngineData::CHUNKWIDTH +
				z * EngineData::CHUNKWIDTH +
				x
		] = blockID;
	}

	BlockType getBlock(int x, int y, int z) {
		if (!isInsideLocalBlock(x, y, z))
			return BlockType::BLOCK_NOT_LOADED;

		return ChunkData[
			y * EngineData::CHUNKWIDTH * EngineData::CHUNKWIDTH +
				z * EngineData::CHUNKWIDTH +
				x
		];
	}

	void GenerateChunkData() {
		for (int z = 0; z < EngineData::CHUNKWIDTH; z++) {
			for (int x = 0; x < EngineData::CHUNKWIDTH; x++) {
				int worldX = chunkX * EngineData::CHUNKWIDTH + x;
				int worldZ = chunkZ * EngineData::CHUNKWIDTH + z;

				float heightNoise = std::pow(
					terrainNoise.GetNoise((float)worldX, (float)worldZ),
					1.0f
				);

				int terrainHeight = 81 + (int)(heightNoise * 20.0f);

				for (int y = 0; y < EngineData::CHUNKHEIGHT; y++) {
					if (y == 0) {
						setBlock(x, y, z, BlockType::BEDROCK);
						continue;
					}

					if (y > terrainHeight) {
						setBlock(x, y, z, BlockType::AIR);
						continue;
					}

					float cave = caveNoise.GetNoise(
						(float)worldX,
						(float)y,
						(float)worldZ
					);

					if (cave > 0.3f) {
						setBlock(x, y, z, BlockType::AIR);
						continue;
					}

					if (y == terrainHeight) {
						setBlock(x, y, z, BlockType::GRASS);
					}
					else if (y >= terrainHeight - 3) {
						setBlock(x, y, z, BlockType::DIRT);
					}
					else {
						setBlock(x, y, z, BlockType::STONE);
					}
				}
			}
		}

		GenerateTrees();

		ApplyPendingBlocksToChunk(chunkX, chunkZ);
	}
	//Terrain Generators


	void GenerateMesh() {
		vertices.clear();
		indices.clear();
		index_num = 0;

		for (int x = 0; x < EngineData::CHUNKWIDTH; x++) {
			for (int y = 0; y < EngineData::CHUNKHEIGHT; y++) {
				for (int z = 0; z < EngineData::CHUNKWIDTH; z++) {

					BlockType current = getBlock(x, y, z);

					if (current == BlockType::AIR)
						continue;

					// X+
					if (x == EngineData::CHUNKWIDTH - 1) {
						if (getBlockGlobal(0, y, z, chunkX + 1, chunkZ) == BlockType::AIR ||
							getBlockGlobal(0, y, z, chunkX + 1, chunkZ) == BlockType::BLOCK_NOT_LOADED)
						{
							placeRightface(x, y, z, current);
						}
					}
					else if (getBlock(x + 1, y, z) == BlockType::AIR) {
						placeRightface(x, y, z, current);
					}

					// X-
					if (x == 0) {
						if (getBlockGlobal(EngineData::CHUNKWIDTH - 1, y, z, chunkX - 1, chunkZ) == BlockType::AIR ||
							getBlockGlobal(EngineData::CHUNKWIDTH - 1, y, z, chunkX - 1, chunkZ) == BlockType::BLOCK_NOT_LOADED)
						{
							placeLeftface(x, y, z, current);
						}
					}
					else if (getBlock(x - 1, y, z) == BlockType::AIR) {
						placeLeftface(x, y, z, current);
					}

					// Y+
					if (y == EngineData::CHUNKHEIGHT - 1 ||
						getBlock(x, y + 1, z) == BlockType::AIR)
					{
						placeTopface(x, y, z, current);
					}

					// Y-
					if (y == 0 ||
						getBlock(x, y - 1, z) == BlockType::AIR)
					{
						placeBottomface(x, y, z, current);
					}

					// Z+
					if (z == EngineData::CHUNKWIDTH - 1) {
						if (getBlockGlobal(x, y, 0, chunkX, chunkZ + 1) == BlockType::AIR ||
							getBlockGlobal(x, y, 0, chunkX, chunkZ + 1) == BlockType::BLOCK_NOT_LOADED)
						{
							placeFrontface(x, y, z, current);
						}
					}
					else if (getBlock(x, y, z + 1) == BlockType::AIR) {
						placeFrontface(x, y, z, current);
					}

					// Z-
					if (z == 0) {
						if (getBlockGlobal(x, y, EngineData::CHUNKWIDTH - 1, chunkX, chunkZ - 1) == BlockType::AIR ||
							getBlockGlobal(x, y, EngineData::CHUNKWIDTH - 1, chunkX, chunkZ - 1) == BlockType::BLOCK_NOT_LOADED)
						{
							placeBackface(x, y, z, current);
						}
					}
					else if (getBlock(x, y, z - 1) == BlockType::AIR) {
						placeBackface(x, y, z, current);
					}
				}
			}
		}

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(GLfloat),vertices.data(),	GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(GLuint),indices.data(),	GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,5 * sizeof(GLfloat),(void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);

		std::cout << "Mesh uploaded: "
			<< vertices.size()
			<< " verts, "
			<< indices.size()
			<< " indices\n";
	}

	void sendModelMat() {
		glUniformMatrix4fv(UniformLocations::ModelMatrix, 1, GL_FALSE, glm::value_ptr(model));
	}
	void RenderChunk() {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	BlockType getBlockGlobal(int x, int y, int z, int chunkX, int chunkZ) {
		if (x > EngineData::CHUNKWIDTH || z > EngineData::CHUNKWIDTH || y > EngineData::CHUNKHEIGHT) {
			std::cerr << "Dumbass \n";
		}
		if (WORLD.contains(ChunkIDHelper(chunkX, chunkZ))) {
			return WORLD[ChunkIDHelper(chunkX, chunkZ)].getBlock(x, y, z);
		}
		else {
			return BlockType::BLOCK_NOT_LOADED;
		}
	}
};


int lastPlayerChunkX = 999999;
int lastPlayerChunkZ = 999999;

int WorldToLocalCoord(int worldCoord, int chunkCoord) {
	return worldCoord - chunkCoord * EngineData::CHUNKWIDTH;
}

int WorldToChunkCoord(float worldCoord) {
	return static_cast<int>(std::floor(worldCoord / EngineData::CHUNKWIDTH));
}

int WorldToChunkCoordInt(int worldCoord) {
	return static_cast<int>(
		std::floor(
			static_cast<float>(worldCoord) / EngineData::CHUNKWIDTH
		)
		);
}

void RegenerateChunkIfExists(int x, int z) {
	uint64_t id = ChunkIDHelper(x, z);

	if (WORLD.contains(id)) {
		WORLD.at(id).GenerateMesh();
	}
}

void AddBlockGlobal(int worldX, int y, int worldZ, BlockType blockID) {
	if (y < 0 || y >= EngineData::CHUNKHEIGHT)
		return;

	int targetChunkX = WorldToChunkCoordInt(worldX);
	int targetChunkZ = WorldToChunkCoordInt(worldZ);

	int localX = WorldToLocalCoord(worldX, targetChunkX);
	int localZ = WorldToLocalCoord(worldZ, targetChunkZ);

	uint64_t id = ChunkIDHelper(targetChunkX, targetChunkZ);

	if (WORLD.contains(id)) {
		WORLD.at(id).setBlock(localX, y, localZ, blockID);
	}
	else {
		PENDING_BLOCKS[id].push_back({
			localX,
			y,
			localZ,
			blockID
			});
	}
}

void ApplyPendingBlocksToChunk(int chunkX, int chunkZ) {
	uint64_t id = ChunkIDHelper(chunkX, chunkZ);

	if (!WORLD.contains(id))
		return;

	if (!PENDING_BLOCKS.contains(id))
		return;

	for (const PendingBlock& block : PENDING_BLOCKS.at(id)) {
		WORLD.at(id).setBlock(
			block.x,
			block.y,
			block.z,
			block.type
		);
	}

	PENDING_BLOCKS.erase(id);
}

void AddTreeGlobal(int worldX, int y, int worldZ) {
	
	for (int dx = -2; dx <= 2; dx++) {
		for (int dz = -2; dz <= 2; dz++) {
			AddBlockGlobal(
				worldX + dx,
				y + 3,
				worldZ + dz,
				BlockType::OAK_LEAVES
			);
		}
	}

	// Capa mediana 3x3
	for (int dx = -1; dx <= 1; dx++) {
		for (int dz = -1; dz <= 1; dz++) {
			AddBlockGlobal(
				worldX + dx,
				y + 4,
				worldZ + dz,
				BlockType::OAK_LEAVES
			);
		}
	}

	// Punta 
	AddBlockGlobal(worldX, y + 5, worldZ, BlockType::OAK_LEAVES);
	AddBlockGlobal(worldX + 1, y + 5, worldZ, BlockType::OAK_LEAVES);
	AddBlockGlobal(worldX - 1, y + 5, worldZ, BlockType::OAK_LEAVES);
	AddBlockGlobal(worldX, y + 5, worldZ + 1, BlockType::OAK_LEAVES);
	AddBlockGlobal(worldX, y + 5, worldZ - 1, BlockType::OAK_LEAVES);

	// Tronco 
	for (int i = 0; i < 5; i++) {
		AddBlockGlobal(
			worldX,
			y + i,
			worldZ,
			BlockType::OAK_LOG
		);
	}
}

BlockType getBlockGlobal(int x, int y, int z, int chunkX, int chunkZ) {
	uint64_t id = ChunkIDHelper(chunkX, chunkZ);

	if (!WORLD.contains(id))
		return BlockType::BLOCK_NOT_LOADED;

	return WORLD.at(id).getBlock(x, y, z);
}
//Do not understand a crap of wat goin on
//Big GPT said mor fps == better
uint32_t Hash2D(int x, int z, uint32_t seed) {
	uint32_t h = seed;

	h ^= static_cast<uint32_t>(x) + 0x9e3779b9 + (h << 6) + (h >> 2);
	h ^= static_cast<uint32_t>(z) + 0x9e3779b9 + (h << 6) + (h >> 2);

	h ^= h >> 16;
	h *= 0x7feb352d;
	h ^= h >> 15;
	h *= 0x846ca68b;
	h ^= h >> 16;

	return h;
}