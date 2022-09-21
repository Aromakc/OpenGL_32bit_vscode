#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    glfwInit();
    
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800,800, "Aromac",NULL,NULL);

	if(window ==NULL){
		std::cout<< "Failed to create window" << std::endl;
	glfwTerminate();
	return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL(); //load glad so it configures OpenGL

	glViewport(0,0,800,800);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //color of background
	glClear(GL_COLOR_BUFFER_BIT); //clear back buffer and assign new color

	glfwSwapBuffers(window); //swap back buffer with front buffer


	while(!glfwWindowShouldClose(window)){
		glfwPollEvents(); //window responding: appering resizing
	}

	glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}