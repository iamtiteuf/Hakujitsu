#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H
#include "Global_Variables.h"
class Window
{
public:
	bool Create_Window();
	bool Window_Should_Close();
	~Window()
	{
		glfwDestroyWindow(Main_Window);
		glfwTerminate();
	}
	GLuint height = 1080;
	GLuint width = 1920;
	const char* title = "Hakujitsu";
private:
	void SetColorTheme(int index);
};
#endif
