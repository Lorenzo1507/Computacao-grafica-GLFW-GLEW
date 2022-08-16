//Biblioteca principal onde podemos dar printf e fazer todo o básico
#include <iostream>
//administra as extensões do opengl
#include "GL/glew.h"
//glfw cria janelas 
#include "GLFW/glfw3.h"

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

	//Enquanto a janela não deveria fechar
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Habilita os eventos de usuario
		glfwPollEvents();

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}
