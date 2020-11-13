#ifndef INTERNAL_EVENTS_H
#define INTERNAL_EVENTS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"

#include <string>
#include <vector>
#include <map>

namespace Events { //test
	std::map<std::string, std::string> EventIdMap; // name : id
	std::map<std::string, std::string> EventNameMap; // id : name


	class Event {
	public:
		bool is = false;
		std::string id = "0000"; // 4 chars only!
		std::string name = "";

		Event(std::string name, std::string id);

		~Event();

		bool operator==(Event _event) {
			if (_event.id == this->id) {
				return true;
			}
			return false;
		}

		bool operator!=(Event _event) {
			return _event.id != this->id ? true : false;
		}
	};

	Event FirstRun("FirstRun", "1000");


	enum class translateType { ID, NAME };
	std::string translate(std::string value, translateType type) {
		if (type == translateType::ID) {
			return EventIdMap[value];
		}
		else {
			return EventNameMap[value];
		}
	}

	Event& compact(std::string name, std::string id) {
		Event ret(name, id);
		return ret;
	}
}

namespace InternalEventVec {
	std::vector<Events::Event*> eventVec;

	bool isIn(Events::Event* Event) {
		for (size_t i = 0; i < eventVec.size(); ++i) {
			if (eventVec[i]->id == Event->id) {
				return true;
			}
		}
		return false;
	}

	void append(Events::Event* Event) {
		eventVec.push_back(Event);
	}

	void del(Events::Event* Event) {
		for (size_t i = 0; i < eventVec.size(); ++i) {
			if (eventVec[i]->id == Event->id) {
				delete eventVec[i];
				eventVec[i] = nullptr;
				eventVec.erase(eventVec.begin() + i);
			}
		}
	}
}

Events::Event::Event(std::string name, std::string id) {
	this->name = name;
	this->id = id;
	EventIdMap[name] = id;
	EventNameMap[id] = name;

	InternalEventVec::append(this);
}

Events::Event::~Event() {
	EventIdMap.erase(name);
	EventNameMap.erase(id);

	InternalEventVec::del(this);
}

#endif