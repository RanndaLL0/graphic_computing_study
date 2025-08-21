#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

const GLint WIDTH = 1024, HEIGHT = 728;
GLuint VAO, VBO, shaderProgram;

// linguagem GLSL (O vertexShader recebe o x e y para posicionar o triângulo em tela)
// layout(location = 0) in vec2 pos, passo como argumento para o programa um vetor;
// gl_Position recebe um parametro de vetor de 4 variaveis (x,y,z,w)
static const char* vertexShader = "							\n\
#version 330												\n\
															\n\
layout(location=0) in vec2 pos;								\n\
															\n\
void main() {												\n\
	gl_Position() = vec4(pos.x,pos.y,0.0,1.0)				\n\
}															\n\
															\n\
															\n\
";

//Podemos entender um ponto como sendo um fragmento de uma poligono ou figura geométrica
//iremos definir a cor da nossa figura geométrica
//uma vez que sua cor possa ser alterada pela luz do programa
static const char* fragmentShader = "						\n\
#version 330												\n\
															\n\
uniform in vec3 triColor;									\n\
															\n\
void main() {												\n\
	color = vec4(triColor,1.0)								\n\
}															\n\
															\n\
															\n\
";

void createTriangle() {
	GLfloat vertices[] = {
		0.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f,-1.0f
	};

	//ira armazenar o vertifice em memória de video, ira ficar na posição 0 (que não é a posição em memoria ram)
	glGenVertexArrays(1, &VAO);
	//posibilita a alteração do valor em espaço de memória apontando para o endereço
	glBindVertexArray(VAO);
		
	//aloca dentro do VAO o VBO
	glGenBuffers(1, &VBO);
	//aponta para o VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//sinaliza como as informações do vertice estão dispostas
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);

	//deixa de apontar para o VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

//adiciona um programa em execução
void add_triangle(GLuint program, const char* shaderCode, GLenum type) {
	GLuint _shader = glCreateShader(type);
	
	//Converte char para GLchar
	const GLchar* code[1];
	code[0] = shaderCode;

	glShaderSource(_shader, 1, code, NULL);
	glCompileShader(_shader);

	//tratar os erros
	
	glAttachShader(program, _shader);
}

void add_program() {
	shaderProgram = glCreateProgram();
	if (!shaderProgram) {
		printf("Erro ao criar o programa");
		return;
	}
	add_triangle(shaderProgram, vertexShader,GL_VERTEX_SHADER);
	add_triangle(shaderProgram, fragmentShader, GL_FRAGMENT_SHADER);

	glLinkProgram(shaderProgram);
}

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