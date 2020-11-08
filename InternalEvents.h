#ifndef INTERNAL_EVENTS_H
#define INTERNAL_EVENTS_H

#include "InternalDef.h"
#include "InternalFsys.h"
#include "InternalErrorLogger.h"

namespace Events {
	std::map<std::string, std::string> EventIdMap; // name : id
	std::map<std::string, std::string> EventNameMap; // id : name


	class Event {
	public:
		bool is = false;
		std::string id = "0000"; // 4 chars only!
		std::string name = "";

		Event(std::string name, std::string id) {
			this->name = name;
			this->id = id;
			EventIdMap[name] = id;
			EventNameMap[id] = name;
		}

		~Event() {
			EventIdMap.erase(name);
			EventNameMap.erase(id);
		}
	};

	Event FirstRun("FirstRun","1000");


	enum class translateType  {ID,NAME};
	std::string translate(std::string value,translateType type) {
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

#endif