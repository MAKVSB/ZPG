#include "Observer.h"

#include <functional>

void Observable::add(observerFuntion* obs) {
	observers.push_back(obs);
}

void Observable::remove(observerFuntion* obs) {
	observers.erase(
		std::remove(observers.begin(), observers.end(), obs),
		observers.end()
	);
}

void Observable::notify(MessageType messageType, void* obj)
{
	for (auto& obs : observers) {
		obs(messageType, obj);
	}
}