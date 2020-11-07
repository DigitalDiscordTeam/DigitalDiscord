#ifndef INTERNAL_EVENT_MAP_H
#define INTERNAL_EVENT_MAP_H

#include <map>
#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"

namespace InternalEventMap {
	std::map<std::string, int> EventMap;
	
	void set(Event::Events& _event, bool setstate = true) {
		if (EventMap[_event.id] == 0 && !setstate) {
			InternalErrLog::LogMain.append(time(NULL), "MapIsAlreadyStoragingError");
			throw MapIsAlreadyStoragingError;
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

	bool get(Event::Events _event) {
		if (EventMap[_event.id] == 0) {
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
