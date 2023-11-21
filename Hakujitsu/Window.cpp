#include "Window.h"

bool Window::Create_Window()
{
	if (!glfwInit())
	{
		std::cout << "failed to initialize \n";
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	Main_Window = glfwCreateWindow(width, height, title, 0, 0);
	if (!Main_Window)
	{
		std::cout << "failed to createe window \n";
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(Main_Window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to Initialize glew \n";
		glfwDestroyWindow(Main_Window);
		glfwTerminate();
		return EXIT_FAILURE;
	}
	SetColorTheme(4);
	return EXIT_SUCCESS;
}
void Window::SetColorTheme(int index)
{
	switch (index)
	{
	case 1:
		glClearColor(Background_Color[0][0], Background_Color[0][1], Background_Color[0][2], Background_Color[0][3]);
		break;
	case 2:
		glClearColor(Background_Color[1][0], Background_Color[1][1], Background_Color[1][2], Background_Color[1][3]);
		break;
	case 3:
		glClearColor(Background_Color[2][0], Background_Color[2][1], Background_Color[2][2], Background_Color[2][3]);
		break;
	default:
		glClearColor(Background_Color[3][0], Background_Color[3][1], Background_Color[3][2], Background_Color[3][3]);
		break;
	}

}
bool Window::Window_Should_Close()
{
	if (glfwWindowShouldClose(Main_Window))
	{
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}