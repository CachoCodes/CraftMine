class Shader {
public:
	GLuint ID;
	Shader() {}
	Shader(const std::string& vertexPath, const std::string& fragmentPath) {
		std::string vertexSource = EngineFunctions::get_file_contents(vertexPath);
		std::string fragmentSource = EngineFunctions::get_file_contents(fragmentPath);
		const char* vertexCode = vertexSource.c_str();
		const char* fragmentCode = fragmentSource.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexCode, NULL);
		glCompileShader(vertexShader);
		EngineFunctions::shader_compilation_status(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
		glCompileShader(fragmentShader);
		EngineFunctions::shader_compilation_status(fragmentShader);

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		EngineFunctions::shader_linking_status(ID);

		// Shaders are linked into the program, no longer needed
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
		
	void Activate() {
		glUseProgram(ID);
	}
	void Delete() {
		glDeleteProgram(ID);
		delete this;
	}
};