#ifndef INTERNAL_EVENTS_H
#define INTERNAL_EVENTS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"

#include <string>
#include <vector>
#include <map>

namespace Events {
	std::map<std::string, std::string> EventIdMap; // name : id
	std::map<std::string, std::string> EventNameMap; // id : name

	enum class eventType { TRUEEVENT, NOEVENT, UNKNOWN};
	enum class translateType { ID, NAME };
	using tT = translateType;
	using eT = eventType;

	class Event {
	public:
		eT state = eT::UNKNOWN;
		bool is = false;
		std::string id = ""; // 4 chars only!
		std::string name = "";

		Event(std::string name, std::string id);

		Event() { //to avoid stack overflows during Events::compact
			id = "----";
			name = "noEvent";
			state = eT::NOEVENT;
		}

		~Event();

		bool operator==(Event& _event) {
			if (_event.id == this->id) {
				return true;
			}
			return false;
		}

		bool operator!=(Event& _event) {
			return _event.id != this->id ? true : false;
		}

		operator bool() {
			return is;
		}

		eventType getState() {
			return state;
		}
	};

	//Event FirstRun("FirstRun", "1000");

	std::string translate(std::string value, translateType type) {
		if (type == translateType::ID) {
			return EventIdMap[value];
		}
		else {
			return EventNameMap[value];
		}
	}

	Event compact(std::string name, std::string id) {
		Event ret;
		ret.id = id;
		ret.name = name;
		return ret;
	}

	Event compact(const Event* _event) {
		Event ret;
		ret.id = _event->id;
		ret.name = _event->name;

		return ret;
	}
}

namespace InternalEventVec {
	std::vector<Events::Event> eventVec;

	bool isIn(const std::string id) {
		for (size_t i = 0; i < eventVec.size(); ++i) {
			if (eventVec[i].id == id) {
				return true;
			}
		}
		return false;
	}

	void append(Events::Event& Event) {
		eventVec.push_back(Event);
	}
	void append(const Events::Event Event) { //if you use std::compact
		eventVec.push_back(Event);
	}

	void del(Events::Event Event) {
		for (size_t i = 0; i < eventVec.size(); ++i) {
			if (eventVec[i].id == Event.id) {
				eventVec.erase(eventVec.begin() + i);
			}
		}
		throw VecCantDeleteError;
	}

	void del(std::string id) {
		for (size_t i = 0; i < eventVec.size(); ++i) {
			if (eventVec[i].id == id) {
				eventVec.erase(eventVec.begin() + i);
				return;
			}
		}
		throw VecCantDeleteError;
	}
}

Events::Event::Event(std::string name, std::string id) {
	//checks id
	while(id.length() > 4) {
		id.erase(id.end());
	}

	this->name = name;
	this->id = id;
	this->state = Events::eventType::TRUEEVENT;
	EventIdMap[name] = id;
	EventNameMap[id] = name;

	InternalEventVec::append(Events::compact(this->name,this->id));
}

Events::Event::~Event() {
	if (this->getState() == Events::eventType::TRUEEVENT) {
		if (this->id == "----") {
			throw VecCantDeleteError;
		}

		EventIdMap.erase(this->name);
		EventNameMap.erase(this->id);

		if (!InternalEventVec::eventVec.empty()) {
			InternalEventVec::del(this->id);
		}
	}
}

#endif