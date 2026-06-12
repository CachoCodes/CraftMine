class Texture {
public:

	GLuint textureID;
	GLuint64 textureHandle;

	Texture() {}
	Texture(std::string path, TextureFormat format = TextureFormat::RGB) {
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);

		int requestedChannels = (format == TextureFormat::RGBA) ? 4 : 3;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, requestedChannels);

		if (!data) {
			std::cout << "ERROR: Failed to load texture: " << path << std::endl;
			textureID = 0;
			textureHandle = 0;
			return;
		}

		std::cout << "Loaded: " << path << " (" << width << "x" << height << ", " << requestedChannels << " channels)\n";

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLenum glFormat = (format == TextureFormat::RGBA) ? GL_RGBA : GL_RGB;
		GLenum internalFormat = (format == TextureFormat::RGBA) ? GL_RGBA8 : GL_RGB8;

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);

		textureHandle = glGetTextureHandleARB(textureID);
	}

	void addtoVRAM() {
		glMakeTextureHandleResidentARB(textureHandle);
	}

	void removefromVRAM() {
		glMakeTextureHandleNonResidentARB(textureHandle);
	}

	void SendtoShader(GLuint uniformLocation) {
		glUniformHandleui64ARB(uniformLocation, textureHandle);
	}
};

