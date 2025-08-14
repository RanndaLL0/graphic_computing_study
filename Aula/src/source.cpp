#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

const GLint WIDTH = 1024, HEIGHT = 728;

int main() {
	// iniciar o glfw
	if (!glfwInit()) {
		printf("Erro ao inicializar o GLFW");
		glfwTerminate();
		return 1;
	}

	//configurações para a inicialização da janela
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core profile -- extensões basicas para o opengl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//O glew ira utilizar da arquitetura disponivel da placa de video OBS: GL -> glew.
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "PogersGL", NULL,NULL);

	if (!window) {
		printf("Erro ao criar a janela");
		glfwTerminate();
		return 1;
	}
	
	//armazena em buffer o tamanho real da janela
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	//trás para o contexto a janela que iremos exibir
	glfwMakeContextCurrent(window);

	//iniciando o glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("Erro ao iniciar o GLEW");

		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	glViewport(0,0,bufferWidth,bufferHeight);
	
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}