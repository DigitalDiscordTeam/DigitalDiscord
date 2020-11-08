#ifndef INTERNAL_EVENT_MAP_H
#define INTERNAL_EVENT_MAP_H

#include <map>
#include "InternalDef.h"
#include "StdSetup.h"
#include "InternalFsys.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"

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

	bool get(Events::Event _event) {
		if (EventMap[_event.id] == 0) {
			return false;
		}
		else {
			return true;
		}
	}

	void update() {
		std::vector<std::string> vec = InternalFsys::readEventFile(Setup::pathtoDir + "DD_Eve.txt"); //DigitalDiscord Events .txt
		EventMap.clear();

		std::string name = "";

		for (size_t i = 0; i < vec.size(); ++i) {
			name = Events::translate(vec[i], Events::translateType::ID);
			set(Events::compact(name,vec[i]));
			name = "";
		}
	}

}


#endif
