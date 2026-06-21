#define GLM_ENABLE_EXPERIMENTAL
#define FASTNOISE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <string>
#include <FastNoiseLite/FastNoiseLite.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stb/stb_image.h>
#include <random>
#include "Classes/EngineFunctions.hpp"
#include "Classes/Camera.hpp"
#include "Classes/Shader.hpp"
#include "Classes/Texture.hpp"
#include "Classes/Chunk.hpp"
#include "mainloop.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	window = glfwCreateWindow(EngineData::WindowWidth, EngineData::WindowHeight, "CraftMine", nullptr, nullptr);
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	int width, height, channels;
	unsigned char* pixels = stbi_load("Resources/icon.png", &width, &height, &channels, 4);

	if (pixels) {
		GLFWimage icons[1];
		icons[0].width = width;
		icons[0].height = height;
		icons[0].pixels = pixels;
		glfwSetWindowIcon(window, 1, icons);
		stbi_image_free(pixels);
	}
	else {
		std::cerr << "Failed to load window icon" << std::endl;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	if (glfwExtensionSupported("GL_ARB_bindless_texture")) {
		std::cout << "Bindless textures are supported.\n";
	}
	else {
		std::cout << "Bindless textures are NOT supported.\n";
		return -1;
	}
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* version = glGetString(GL_VERSION);
	const unsigned char* shading = glGetString(GL_SHADING_LANGUAGE_VERSION);

	std::cout << "=========================================\n";
	std::cout << "     INFORMACION DE OPENGL Y LA GPU     \n";
	std::cout << "=========================================\n";
	std::cout << "Vendor: " << (vendor ? (const char*)vendor : "Desconocido") << "\n";
	std::cout << "GPU:    " << (renderer ? (const char*)renderer : "Desconocido") << "\n";
	std::cout << "OpenGL: " << (version ? (const char*)version : "Desconocido") << "\n";
	std::cout << "GLSL:   " << (shading ? (const char*)shading : "Desconocido") << "\n";
	std::cout << "=========================================\n";

	glViewport(0, 0, EngineData::WindowWidth, EngineData::WindowHeight);
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);	
	InitEngine();
	while (!glfwWindowShouldClose(window)) {
		EngineFunctions::DeltaTime();
		EngineFunctions::CalculateFps(EngineData::deltaTime);
		glClearColor(0.6f, 0.6, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		mainloop();
		glfwSwapBuffers(window);
	}
	FinishEngine();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	EngineData::WindowWidth = width;
	EngineData::WindowHeight = height;
	glViewport(0, 0, EngineData::WindowWidth, EngineData::WindowHeight);
}