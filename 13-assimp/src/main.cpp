#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include "../include/stb/stb_image.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "camera.h"
#include "model.h"

const unsigned int width = 800;
const unsigned int height = 800;


int main()
{

	// Initialize
    // ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 800, "learnopengl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	stbi_set_flip_vertically_on_load(true);
	
	// Camera, shader, model
    // ------------------------------
	Camera camera(width, height);
	camera.eye = glm::vec3(0,0.5f,3);
	Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag");
	Model m1("res/objects/backpack/backpack.obj", false); 	

	while (!glfwWindowShouldClose(window))
	{
		camera.handleInput(window);

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		camera.setView(shaderProgram, "view");
		camera.setProjection(shaderProgram, "projection", 45.0f, 0.1f, 100.0f);

		m1.setModelMatrix(shaderProgram, "model");
		
		m1.Draw(shaderProgram);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}