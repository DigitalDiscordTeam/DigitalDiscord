#ifndef INTERNAL_EVENTS_H
#define INTERNAL_EVENTS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"

#include <string>
#include <vector>
#include <map>

namespace Events {
	MDEF std::map<std::string, std::string> EventIdMap; // name : id
	MDEF std::map<std::string, std::string> EventNameMap; // id : name

	enum class eventType { TRUEEVENT, NOEVENT, UNKNOWN};
	enum class translateType { ID, NAME };
	using tT = translateType;
	using eT = eventType;

	class Event {
	public:
		eT state = eT::UNKNOWN;
		bool is = false;
		std::string id = ""; // 8 chars only!
		std::string name = "";

		Event(std::string name, std::string id);

		Event();

		//Event(Event&) = delete;

		~Event();

		bool operator==(Event& _event);

		bool operator!=(Event& _event);

		operator bool();

		eventType getState();
	};

	MDEF Event FirstRun("FirstRun", "10000000");

	namespace trans {
		std::string ttypetovar(std::string value, translateType type);

		std::string etypeToString(Events::eT type);

		Event compact(std::string name, std::string id);

		Event compact(const Event* _event);

	}
}

namespace InternalEventVec {
	MDEF std::vector<Events::Event> eventVec;

	bool isIn(const std::string id);

	void append(Events::Event& Event);

	void append(const Events::Event Event);

	void del(const Events::Event& Event);

	void del(std::string id);

	size_t getIndex(std::string id);
}

#endif