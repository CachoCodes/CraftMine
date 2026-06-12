class Chunk;

inline uint64_t ChunkIDHelper(int x, int y) {
	return (uint64_t(x) << 32) ^ (uint32_t(y));
}

std::unordered_map<uint64_t, Chunk> WORLD;


class Chunk {
private:
	GLuint VAO, VBO, EBO;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	glm::mat4 model = glm::mat4(1.0f);
	int chunkX, chunkZ;
	BlockType ChunkData[EngineData::CHUNKWIDTH * EngineData::CHUNKHEIGHT * EngineData::CHUNKWIDTH];
	int index_num = 0;

	//Mesh Builders
	void placeTopface(int x, int y, int z, BlockType blockID) {
		//Y+
		// Add vertices and indices for the top face of the block at (x, y, z) based on its blockID
		if (blockID == BlockType::GRASS) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(1.0f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::DIRT) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(1.0f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(1.0f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.75f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::STONE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(1.0f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.75f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::WATER) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.4375f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.4375f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.4375f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.4375f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::COAL_ORE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::BEDROCK) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::GLASS) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(0.75f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.5f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}

		else if (blockID == BlockType::IRON_ORE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::GRAVEL) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::SAND) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::COBBLESTONE) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(0.5f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.25f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::OAK_PLANKS) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f); vertices.push_back(0.25f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f); vertices.push_back(0.0f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::OAK_LOG) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.25f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.0f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
			index_num += 4;
		}
		else if (blockID == BlockType::OAK_LEAVES) {
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f); vertices.push_back(0.25f); // Top face vertex 1
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f); // Top face vertex 2
			vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.0f); // Top face vertex 3
			vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f); vertices.push_back(0.0f); // Top face vertex 4
			indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2); // Top face triangle 1
			indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3); // Top face triangle 2
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
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::DIRT) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::STONE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
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
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::BEDROCK) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::GLASS) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::IRON_ORE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::GRAVEL) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::SAND) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::COBBLESTONE) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_PLANKS) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LOG) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f); vertices.push_back(0.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LEAVES) {
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.0f);
		vertices.push_back(x + 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
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
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::DIRT) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::STONE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(1.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
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
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::BEDROCK) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f);  vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::GLASS) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.75f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::IRON_ORE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::GRAVEL) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::SAND) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.50f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::COBBLESTONE) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.5f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_PLANKS) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.0f);  vertices.push_back(0.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.25f); vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LOG) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.5f); vertices.push_back(0.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(0.75f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
		index_num += 4;
	}
	else if (blockID == BlockType::OAK_LEAVES) {
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y + 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.25f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z + 0.5f); vertices.push_back(0.75f); vertices.push_back(0.0f);
		vertices.push_back(x - 0.5f); vertices.push_back(y - 0.5f); vertices.push_back(z - 0.5f); vertices.push_back(1.0f);  vertices.push_back(0.0f);
		indices.push_back(index_num); indices.push_back(index_num + 1); indices.push_back(index_num + 2);
		indices.push_back(index_num); indices.push_back(index_num + 2); indices.push_back(index_num + 3);
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

	//Terrain Generators
	void addTree(int x, int y, int z) {
			// Tronco

			// Primera capa: cruz
			setBlock(x, y + 5, z, BlockType::OAK_LEAVES);
			setBlock(x + 1, y + 5, z, BlockType::OAK_LEAVES);
			setBlock(x - 1, y + 5, z, BlockType::OAK_LEAVES);
			setBlock(x, y + 5, z + 1, BlockType::OAK_LEAVES);
			setBlock(x, y + 5, z - 1, BlockType::OAK_LEAVES);

			// Segunda capa: 3x3
			for (int dx = -1; dx <= 1; dx++) {
				for (int dz = -1; dz <= 1; dz++) {
					setBlock(x + dx, y + 4, z + dz, BlockType::OAK_LEAVES);
				}
			}

			// Tercera capa: 5x5
			for (int dx = -2; dx <= 2; dx++) {
				for (int dz = -2; dz <= 2; dz++) {
					setBlock(x + dx, y + 3, z + dz, BlockType::OAK_LEAVES);
				}
			}
			for (int i = 0; i < 5; i++) {
				setBlock(x, y + i, z, BlockType::OAK_LOG);
			}
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

	void setBlock(int x, int y, int z, BlockType blockID) {
		ChunkData[y * EngineData::CHUNKWIDTH * EngineData::CHUNKWIDTH + z * EngineData::CHUNKWIDTH + x] = blockID;
	}

	BlockType getBlock(int x, int y, int z) {
		return ChunkData[y * EngineData::CHUNKWIDTH * EngineData::CHUNKWIDTH + z * EngineData::CHUNKWIDTH + x];
	}

	void GenerateChunkData() {
		for (int z = 0; z < EngineData::CHUNKWIDTH; z++)
		{
			for (int x = 0; x < EngineData::CHUNKWIDTH; x++)
			{
				int worldX = chunkX * EngineData::CHUNKWIDTH + x;
				int worldZ = chunkZ * EngineData::CHUNKWIDTH + z;

				float heightNoise = std::pow(terrainNoise.GetNoise((float)worldX,(float)worldZ),1.0f);

				int terrainHeight = 81 + (int)(heightNoise * 20.0f);

				for (int y = 0; y < EngineData::CHUNKHEIGHT; y++){
					if (y == 0) {
						setBlock(x, y, z, BlockType::BEDROCK);
						continue;
					}
					
					if (y > terrainHeight){
						setBlock(x, y, z, BlockType::AIR);
						continue;
					}
					
					float cave =
						caveNoise.GetNoise(
							(float)worldX,
							(float)y,
							(float)worldZ
						);

					if (cave > 0.3f)
					{
						setBlock(x, y, z, BlockType::AIR);
						continue;
					}

					if (y == terrainHeight)
					{
						setBlock(x, y, z, BlockType::GRASS);
					}
					else if (y >= terrainHeight - 3)
					{
						setBlock(x, y, z, BlockType::DIRT);
					}
					else
					{
						setBlock(x, y, z, BlockType::STONE);
					}
				}
			}
		}
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