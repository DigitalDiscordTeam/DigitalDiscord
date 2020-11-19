#ifndef INTERNAL_EVENT_MAP_H
#define INTERNAL_EVENT_MAP_H

#include "InternalDef.h"
//#include "InternalSys.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"

#include <map>
#include <assert.h>

namespace InternalEventMap {
	std::map<std::string, int> EventMap;
	
	void set(Events::Event& _event, bool setstate = true) {
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

	void set(const Events::Event _event, bool setstate = true) { //if you use Events::compact
		assert(_event.state == Events::eventType::NOEVENT); //only true events!
		if (EventMap[_event.id] == 0 && !setstate) {
			InternalErrLog::LogMain.append(time(NULL), "MapIsAlreadyStoragingError");
			throw MapIsAlreadyStoragingError;
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

	bool get(std::string id) {
		if (EventMap[id] == 0) {
			return false;
		}
		else {
			return true;
		}
	}

	void updateEvent(Events::Event& _event) {
		if (EventMap[_event.id] == 1) {
			_event.is = true;
		}
		else {
			_event.is = false;
		}
	}

}


#endif
