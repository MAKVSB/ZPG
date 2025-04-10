/**
 * @file callbackManager.h
 *
 * @brief Manages callbacks from OpenGL directly
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "GlobalInclude.h"

#include <map>

#include "Observer.h"
class CallbackManager : public Observable
{
public:
	struct CBKeyData {
		int key;
		int state;
		int mods;
		std::map<int, int>* map;
	};

	struct CBCursorData {
		double x;
		double y;
	};

	struct CBResizeData {
		int width;
		int height;
	};

	struct CBIconifyData {
		bool visible;
	};

	struct CBFocusData {
		bool focused;
	};

	struct CBScrollData {
		double x;
		double y;
	};

	struct CBButtonData {
		int button;
		int mods;
		CBCursorData mousePos;
	};

	static CallbackManager* init(GLFWwindow* window) {
		if (instance == nullptr) {
			instance = new CallbackManager(window);
		}
		return instance;
	}

	static CallbackManager* getInstance() {
		return instance;
	}

	static void destroy() {
		delete instance;
	}
private:
	static CallbackManager* instance;

	static void cbError(int error, const char* description);

	static void cbKey(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void cbCursor(GLFWwindow* window, double x, double y);

	static void cbButton(GLFWwindow* window, int button, int action, int mode);

	static void cbWindowFocus(GLFWwindow* window, int focused);

	static void cbIconify(GLFWwindow* window, int iconified);

	static void cbResize(GLFWwindow* window, int width, int height);

	static void cbScroll(GLFWwindow* window, double xoffset, double yoffset);

	static void registerCallbacks(GLFWwindow* window);
	static void unregisterCallbacks(GLFWwindow* window);

	static std::map<int, int> keypressMap;
	static CBCursorData lastMousePos;

	CallbackManager(GLFWwindow* window);
	~CallbackManager();

	static GLFWwindow* window;
};

