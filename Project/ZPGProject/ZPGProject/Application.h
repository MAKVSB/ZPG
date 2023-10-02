#pragma once
#include <iostream>

//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>

#include "ShaderProgram.h"
#include "Model.h"

class Application
{
private:
	GLFWwindow* window;

	std::map<std::string, ShaderProgram*> shaderPrograms;
	std::list<Model*> models;


public:
	void initialization();
	void createShaders();
	void createModels();
	void run();
};