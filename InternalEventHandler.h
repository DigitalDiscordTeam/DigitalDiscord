#ifndef INTERNAL_EVENT_HANDLER_H
#define INTERNAL_EVENT_HANDLER_H

#include "InternalErrorLogger.h"

namespace InternalEventHandler {
	template<class C>
	void trigger(C Event) {
		try {
			C::what();
		}
		catch (...) {
			InternalErrLog::LogMain.append(time(NULL), "EventTriggerError");
			throw EventTriggerError;
		}

		C::trigger();
	}
}

#endif
