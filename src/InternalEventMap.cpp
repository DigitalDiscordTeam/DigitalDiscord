#include "InternalEventMap.h"

void InternalEventMap::set(Events::Event& _event, bool setstate) {
	if (EventMap[_event.id] == 0 && !setstate) {
		InternalErrLog::LogMain.append(time(NULL), "MapIsAlreadyStoragingError");
		throw MapIsAlreadyStoragingError{};
	}
	else {
		if (setstate) {
			EventMap[_event.id] = 1; // 1 = true
			_event.is = true;
		}
		else {
			EventMap[_event.id] = 0; // 0 = false
			_event.is = false;
		}
	}
}

void InternalEventMap::set(const Events::Event _event, bool conpact, bool setstate) { //if you use Events::compact
	assert(_event.state == Events::eventType::NOEVENT); //only true events!
	if (EventMap[_event.id] == 0 && !setstate) {
		InternalErrLog::LogMain.append(time(NULL), "MapIsAlreadyStoragingError");
		throw MapIsAlreadyStoragingError{};
	}
	else {
		if (setstate) {
			EventMap[_event.id] = 1; // 1 = true
		}
		else {
			EventMap[_event.id] = 0; // 0 = false
		}
	}
}

bool InternalEventMap::get(std::string id) {
	if (EventMap[id] == 0) {
		return false;
	}
	else {
		return true;
	}
}

void InternalEventMap::updateEvent(Events::Event& _event) {
	if (EventMap[_event.id] == 1) {
		_event.is = true;
	}
	else {
		_event.is = false;
	}
}