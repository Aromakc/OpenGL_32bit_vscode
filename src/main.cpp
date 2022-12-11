#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <malloc.h>

std::string vertexShader = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

std::string fragmentShader = 
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
	"}\n\0";

static unsigned int  CompileShader(unsigned int type, const std::string& source){
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); //pointing to src initial character
	glShaderSource(id,1, &src, nullptr);
	glCompileShader(id);

	//Error Handling
	int result;
	glGetShaderiv(id,GL_COMPILE_STATUS,&result);
	if(result == GL_FALSE){
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); //maxlength = logLength
		char* message = (char*)_alloca(length * sizeof(char)); //message store infolog, so given fixed length  
		// char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message); //shader,maxLength,*length,*infolog 
		
		std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex":"fragment") << "shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		// delete message;
		return 0;
	}
	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	unsigned int program = glCreateProgram(); //creates a program and returns a id
	glAttachShader(program,vs);
	glAttachShader(program,fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(fs);
	glDeleteShader(vs);
 	
	return program;
}

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

	gladLoadGL();

	glViewport(0,0,800,800);

	float positions[]={
		-0.5f, -0.5f, 0.0f,
     	0.5f, -0.5f, 0.0f,
     	0.0f,  0.5f, 0.0f
	};

	unsigned int VAO,VBO;
	
	glGenVertexArrays(1, &VAO); 
	glBindVertexArray(VAO);
	
	glGenBuffers(1,&VBO); //1 buffer	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	
	unsigned int programShader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(programShader);

	while(!glfwWindowShouldClose(window)){
		
		glClear(GL_COLOR_BUFFER_BIT); //clear back buffer and assign new color
		glDrawArrays(GL_TRIANGLES,0,3);

		glfwSwapBuffers(window); //swap back buffer with front buffer
		glfwPollEvents(); //window responding: appering resizing
	}	

	glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
