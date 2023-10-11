#pragma once
#include <vector>
#include <functional>

enum class MessageType {
	//window callbacks
	MouseButtonPressed,
	MouseButtonReleased,
	MouseButtonHeld,
	KeyPressed,
	KeyReleased,
	KeyHeld,
	MouseMove,
	WindowResize,
	WindowFocusChange,
	WindowVisibleChange,
	ScrollOffsetChange,

	//camera messages
	CameraProjectionChange,
	CameraViewChange,
	CameraChanged,
};

class Observer {
public:
	virtual void listen(MessageType messageType, void* object) = 0;
};

class Observable {
	std::vector <Observer*> observers;
public:
	void add(Observer* obs);
	void remove(Observer* obs);
	void notify(MessageType messageType, void* obj);
};