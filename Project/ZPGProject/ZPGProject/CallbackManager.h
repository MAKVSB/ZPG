#pragma once
class CallbackManager
{
private:
	static void cbError(int error, const char* description);

	static void cbKey(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void cbCursor(GLFWwindow* window, double x, double y);

	static void cbButton(GLFWwindow* window, int button, int action, int mode);

	static void cbWindowFocus(GLFWwindow* window, int focused);

	static void cbIconify(GLFWwindow* window, int iconified);

	static void cbResize(GLFWwindow* window, int width, int height);

	static void registerCallbacks(GLFWwindow* window);

public:
	CallbackManager(GLFWwindow* window);
};

