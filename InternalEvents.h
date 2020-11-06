#ifndef INTERNAL_EVENTS_H
#define INTERNAL_EVENTS_H

#include "InternalDef.h"
#include "InternalFsys.h"
#include "InternalErrorLogger.h"
#include <time.h>

namespace Event {
	typedef struct Events Events;
	struct Events {
	public:
		bool is = false;
		std::string id = "0000"; // 4 chars only!
		std::string name = name;

		Events(std::string name, std::string id) {
			this->name = name;
			this->id = id;
		}

		void operator=(Events& _event) {
			this->name = _event.name;
			this->is = false;
		}
	};

	Events FirstRun("FirstRun","1000");
}

#endif