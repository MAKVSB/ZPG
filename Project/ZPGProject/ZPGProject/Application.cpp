#pragma once
#include "Application.h"

#include "Cube.h"
#include "Triangle.h"

// Placeholder (GLM probably have some matrix functions to do that in combination with camera
void translateObject(std::vector<float>& vertices, float dx, float dy, float dz) {
	for (size_t i = 0; i < vertices.size(); i += 8) {
		vertices[i] += dx; // Translate along the x-axis
		vertices[i + 1] += dy; // Translate along the y-axis
		vertices[i + 2] += dz; // Translate along the z-axis
	}
}

// Placeholder (GLM probably have some matrix functions to do that in combination with camera
void scaleObject(std::vector<float>& vertices, float dx, float dy, float dz) {
	for (size_t i = 0; i < vertices.size(); i += 8) {
		vertices[i] *= dx; // Translate along the x-axis
		vertices[i + 1] *= dy; // Translate along the y-axis
		vertices[i + 2] *= dz; // Translate along the z-axis
	}
}

void Application::initialization() {
	//void error_callback(int error, const char* description) { fputs(description, stderr); }
	//glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	////inicializace konkretni verze
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	//GLM test

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(10, 10, 20), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);
}

void Application::createShaders() {
	ShaderProgram* firstShader = new ShaderProgram();
	firstShader->addShader(GL_VERTEX_SHADER, "vertex_shader.glsl");
	firstShader->addShader(GL_FRAGMENT_SHADER, "fragment_shader.glsl");
	firstShader->compile();
	firstShader->check();
	shaderPrograms[std::string("firstShader")] = firstShader;

	ShaderProgram* secondShader = new ShaderProgram();
	secondShader->addShader(GL_VERTEX_SHADER, "vertex_shader_positional_color.glsl");
	secondShader->addShader(GL_FRAGMENT_SHADER, "fragment_shader_positional_color.glsl");
	secondShader->compile();
	secondShader->check();
	shaderPrograms[std::string("secondShader")] = secondShader;
}

void Application::createModels() {

	scaleObject(cubeVertexData, .7f, .7f, .7f);
	translateObject(cubeVertexData, 0, -.2f, 0);
	Model* firstModel = new Model(cubeVertexData);
	firstModel->shader = shaderPrograms[std::string("firstShader")];
	models.push_back(firstModel);
	scaleObject(triangleVertexData, .7f, .7f, .7f);
	translateObject(triangleVertexData, 0, .5f, -.1f);
	Model* secondModel = new Model(triangleVertexData);
	secondModel->shader = shaderPrograms[std::string("secondShader")];
	models.push_back(secondModel);
}

void Application::run() {
	//main vykreslovací while
	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (Model* element : models) {
			element->draw();
		}
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
