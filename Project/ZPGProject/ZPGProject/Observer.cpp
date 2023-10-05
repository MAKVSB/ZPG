#include "Observer.h"

void Observable::add(Observer& obs) {
	observers.push_back(&obs);
}

void Observable::remove(Observer& obs) {
	auto iter = observers.begin();
	while (iter != observers.end()) {
		if (*iter == &obs) {
			observers.erase(iter);
			return;
		}
		++iter;
	}
}

void Observable::notify(MessageType messageType, void* obj) const {
	for (Observer* obs : observers) {
		obs->notify(messageType, obj);
	}
}