#ifndef INTERNAL_EVENTS_H
#define INTERNAL_EVENTS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"

#include <string>
#include <vector>
#include <map>

struct funPoint {
	void (*fun)();
	std::string id;
};

class Event {
public:
	std::vector<funPoint> funs;

	MDEF virtual bool request() {return NONE;}

	MDEF virtual void trigger() {
		for(size_t i = 0; i < funs.size(); ++i) {
			funs[i].fun();
		}
	}
};

class EventHandler {
public:
	Event* eve;
	funPoint onFun;

	EventHandler(Event& event) {
		eve = &event;
	}
	EventHandler() {}

	~EventHandler() {
        for(size_t i = 0; i < eve->funs.size(); ++i) {
            if(eve->funs[i].id == this->onFun.id) {
                eve->funs.erase(eve->funs.begin() + i);
                break;
            }
        }
        delete eve;
        eve = nullptr;
        onFun.fun = nullptr;
    }

};

class nothingEve
	: public Event
{
public:
	MDEF bool request() override {return true;}

	MDEF void trigger() override {
		for(size_t i = 0; i < funs.size(); ++i) {
			funs[i].fun();
		}
	}
};
MDEF nothingEve nothingEvent;




#endif