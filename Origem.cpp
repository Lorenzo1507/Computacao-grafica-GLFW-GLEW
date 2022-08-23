//Biblioteca principal onde podemos dar printf e fazer todo o básico
#include <iostream>
//administra as extensões do opengl
#include "GL/glew.h"
//glfw cria janelas 
#include "GLFW/glfw3.h"

GLuint VAO, VBO, programa;

//Vertex Shader. usar espaços depois apertar o botão insert para deixar todas as quebras de linha ajeitadas, apenas mais uma questão visual
static const char* vShader = "                                       \n\
#version 330                                                         \n\
                                                                     \n\
layout(location=0) in vec2 pos;                                      \n\
                                                                     \n\
                                                                     \n\
void main(){                                                         \n\
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);                      \n\
}                                                                    \n\
																	";

static const char* fShader = "                                       \n\
#version 330                                                         \n\
                                                                     \n\
layout(location=0) in vec2 pos;                                      \n\
                                                                     \n\
                                                                     \n\
void main(){                                                         \n\
    gl_Position = vec4(1.0, 0.0, 0.0, 1.0);                          \n\
}                                                                    \n\
																	";


void criarTriangulos()
{
	GLfloat vertices[] = {
		//x, y
		0.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f
	};

	//Cria o VAO (são todas as propriedades de um vertice como cores, transformação, etc... só tem um VAO por programa)
	glGenVertexArrays(1, &VAO);
	//Coloca o VAO em contexto
	glBindVertexArray(VAO);
		//O tab é apenas visual, mas é só para sabermos que o VBO surge através do VAO
		//No VBO guarda os dados reais do vertice (como posição, cores, etc. pode ter mais de um VBO)
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			//Explica os valores de x e y (mostra onde começa, pula dois itens para ler apenas o x e y e não o z e o rgba)
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); //remover do contexto o VAO
}

void CompilaShader() {
	//Cria um programa
	programa = glCreateProgram();
	GLuint _vShader = glCreateShader(GL_VERTEX_SHADER); //Cria um shader
	GLuint _fShader = glCreateShader(GL_FRAGMENT_SHADER); //Cria um shader

	//Cria um valor tipo char com 1 dado apenas dentro do array. Um tipo de gambiarra para converter chaar em GLChar
	const GLchar* vCode[1];
	const GLchar* fCode[1];

	vCode[0] = vShader; //Codigo do vShader
	fCode[0] = fShader; //Codigo do fShader

	glShaderSource(_vShader, 1, vCode, NULL); //associa o shader ao código
	glCompileShader(_vShader); //Compila o shader

	glShaderSource(_fShader, 1, fCode, NULL); //associa o shader ao código
	glCompileShader(_fShader); //Compila o shader

	glAttachShader(programa, _vShader);
	glAttachShader(programa, _fShader);
}

int main() {
	//Se não conseguir incializar
	if (!glfwInit())
	{
		printf("GLFW: Não pode ser inicializado");
		return 1;
	}

	//Classe para criar o objeto da janela
	GLFWwindow *mainWindow = glfwCreateWindow(800, 600, "Sekai wo hakai koto ni shita no da", NULL, NULL);

	if (!mainWindow)
	{
		printf("GLFW: erro ao criar a janela.");
		//Usa terminate para não ficar ocupando espaço atoa na memória
		glfwTerminate();
		return 1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Função para definir uma janela com principal
	glfwMakeContextCurrent(mainWindow);

	//Se o glew (gerenciador de extenções) não conseguir inicializar
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW: Não pode ser inicializado");

		//Essas duas funções são usadas para limpar o espaço de memória por completo
		glfwDestroyWindow(mainWindow);
		glfwTerminate();

		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	criarTriangulos();
	CompilaShader();

	//Enquanto a janela não deveria fechar
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Habilita os eventos de usuario
		glfwPollEvents();

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		//Desenha o triangulo
		glUseProgram(programa);
			glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}
