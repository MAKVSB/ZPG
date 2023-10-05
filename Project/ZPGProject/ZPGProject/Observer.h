#pragma once
#include <vector>
#include <functional>

enum class MessageType {
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
	ScrollOffsetChange
};

class Observable {
	using observerFuntion = void(MessageType messageType, void* object);
	std::vector <observerFuntion*> observers;
public:
	void add(observerFuntion* obs);
	void remove(observerFuntion* obs);
	void notify(MessageType messageType, void* obj);
};