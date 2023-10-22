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
	auto test2 = this->observers;
	auto test = observers.size();
	for (auto& obs : observers) {
		auto test4 = this->observers;
		auto test3 = observers.size();
		if (test3 != test) break;
		obs->listen(messageType, obj);
	}
}