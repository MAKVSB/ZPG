#pragma once
#include <vector>

enum class MessageType {
	MouseButtonPressed,
	MouseButtonReleased,
	MouseButtonHeld,
	KeyPressed,
	KeyReleased,
	KeyHeld,
	MouseMove
};

struct Observer {
	virtual void notify(MessageType messageType, void* object) = 0;
};

class Observable {
	std::vector<Observer*> observers;
public:
	void add(Observer& obs);
	void remove(Observer& obs);
	void notify(MessageType messageType, void* obj) const;

};