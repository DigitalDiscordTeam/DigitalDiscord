#ifndef INTERNAL_EVENT_MAP_H
#define INTERNAL_EVENT_MAP_H

#include <map>
#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"

namespace InternalEventMap {
	std::map<std::string, int> EventMap;
	
	void set(Event::Events aclass, bool setstate = true) {
		if (EventMap[aclass.id] != 0 && !setstate) {
			InternalErrLog::LogMain.append(time(NULL), "MapIsAlreadyStoragingError");
			throw MapIsAlreadyStoragingError;
		}
		else {
			if (setstate) {
				EventMap[aclass.id] = 1;
			}
			else {
				EventMap[aclass.id] = 0;
			}
		}
	}

	bool get(Event::Events aclass) {
		if (EventMap[aclass.id] == 0) {
			return false;
		}
		else {
			return true;
		}
	}

	void update() {
		//search in a file to find the event triggers
	}

}


#endif
