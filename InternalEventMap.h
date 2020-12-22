#ifndef INTERNAL_EVENT_MAP_H
#define INTERNAL_EVENT_MAP_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"

#include <map>
#include <assert.h>

namespace InternalEventMap {
	std::map<std::string, int> EventMap;
	
	void set(Events::Event& _event, bool setstate = true);

	void set(const Events::Event _event, bool conpact, bool setstate = true);

	bool get(std::string id);

	void updateEvent(Events::Event& _event);

}


#endif
