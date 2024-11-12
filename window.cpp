#include "window.h"

Window::Window()
{
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++)
		keys[i] = 0;

}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;

	for (size_t i = 0; i < 1024; i++)
		keys[i] = 0;
}

int Window::Initialize()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialze GLFW\n";
		glfwTerminate();
		return 1;
	}

	//setting up opengl properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);         //core profile
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                   //allows forward compatability

	//creating window
	mainWindow = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);

	if (!mainWindow)
	{
		std::cout << "Failed to create main window!\n";
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//setting context for glew to use
	glfwMakeContextCurrent(mainWindow);

	//handle inputs
	createCallbacks();

	//hiding mouse cursor in the mainWindow
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//allows modern opengl features
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		std::cout << "Failed to initialize glew\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	
	glEnable(GL_DEPTH_TEST);
	//setting viewport
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}


void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//std::cout << "Pressed: " << key << "\n";
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//std::cout << "Released: " << key << "\n";
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMove)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMove = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//std::cout << "(" << theWindow->xChange << "," << theWindow->yChange << ")\n";
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}