#include "Observer.h"

#include <functional>

void Observable::add(Observer* obs) {
	observers.push_back(obs);
}

void Observable::remove(Observer* obs) {
	observers.erase(
		std::remove(observers.begin(), observers.end(), obs),
		observers.end()
	);
}

void Observable::notify(MessageType messageType, void* obj)
{
	for (auto& obs : observers) {
		obs->listen(messageType, obj);
	}
}