#include "Observer.h"

#include <functional>

void Observable::add(Observer* obs) {
	observers.emplace_back(obs);
}

void Observable::remove(Observer* obs) {
	observers.erase(
		std::remove(observers.begin(), observers.end(), obs),
		observers.end()
	);
}

void Observable::notify(MessageType messageType, void* obj)
{
	auto startCount = observers.size();
	for (auto& obs : observers) {
		auto currCount = observers.size();
		if (currCount != startCount) break;
		obs->listen(messageType, obj);
	}
}