#include "InternalEvents.h"

Events::Event::Event() { //to avoid stack overflows during Events::compact
	id = "--------";
	name = "noEvent";
	state = eT::NOEVENT;
}

bool Events::Event::operator==(Event& _event) {
	if (_event.id == this->id) {
		return true;
	}
	return false;
}

bool Events::Event::operator!=(Event& _event) {
	return _event.id != this->id ? true : false;
}

Events::Event::operator bool() {
	return is;
}

Events::eventType Events::Event::getState() {
	return state;
}

std::string Events::trans::ttypetovar(std::string value, translateType type) {
	if (type == translateType::ID) {
		return EventIdMap[value];
	}
	else {
		return EventNameMap[value];
	}
}

std::string Events::trans::etypeToString(Events::eT type) {
	switch (type) {
	case eT::NOEVENT: 
		return "NOEVENT";
		break;
	case eT::TRUEEVENT:
		return "TRUEEVENT";
		break;
	case eT::UNKNOWN:
		return "UNKNOWN";
		break;
    default:
        return "";
	}

	return "";
}

Events::Event Events::trans::compact(std::string name, std::string id) {
	Event ret;
	ret.id = id;
	ret.name = name;
	return ret;
}

Events::Event Events::trans::compact(const Event* _event) {
	Event ret;
	ret.id = _event->id;
	ret.name = _event->name;

	return ret;
}


bool InternalEventVec::isIn(const std::string id) {
	for (size_t i = 0; i < eventVec.size(); ++i) {
		if (eventVec[i].id == id) {
			return true;
		}
		}
    return false;
}

void InternalEventVec::append(Events::Event& Event) {
	eventVec.push_back(Event);
}

void InternalEventVec::append(Events::Event Event) { //if you use std::compact
	Event.state = Events::eventType::NOEVENT;
    eventVec.push_back(Event);
}

void InternalEventVec::del(const Events::Event& Event) {
	for (size_t i = 0; i < eventVec.size(); ++i) {
		if (eventVec[i].id == Event.id) {
			eventVec.erase(eventVec.begin() + i);
		}
	}
	throw VecCantDeleteError;
}

void InternalEventVec::del(std::string id) {
	for (size_t i = 0; i < eventVec.size(); ++i) {
		if (eventVec[i].id == id) {
			eventVec.erase(eventVec.begin() + i);
			return;
		}
	}
	throw VecCantDeleteError;
}

size_t InternalEventVec::getIndex(std::string id) {
	for (size_t i = 0; i < eventVec.size(); ++i) {
		if (eventVec[i].id == id) {
			return i;
		}
	}
	return -1;
}

Events::Event::Event(std::string name, std::string id) {
	//checks id
	while(id.length() > 8) {
		id.erase(id.end());
	}

	this->name = name;
	this->id = id;
	this->state = Events::eventType::TRUEEVENT;
	EventIdMap[name] = id;
	EventNameMap[id] = name;

	InternalEventVec::append(Events::trans::compact(this->name,this->id));
}

Events::Event::~Event() {
	if (this->getState() == Events::eventType::TRUEEVENT) {

		EventIdMap.erase(this->name);
		EventNameMap.erase(this->id);

		if (!InternalEventVec::eventVec.empty()) {
			InternalEventVec::del(this->id);
		}
	}
}