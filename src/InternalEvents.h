#ifndef INTERNAL_EVENTS_H
#define INTERNAL_EVENTS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalLib.h"

#include <string>
#include <vector>
#include <map>

namespace InternalPCO { //because InternalPrettyConsoleOut.h have to include this file, we have to do this workaround to use the stuff we need
	class Hub;
	class HubChoice;
	class LoadingScreen;
}

using VOIDc = InternalLib::c_VOID;



template<typename para = VOIDc,typename ret = VOIDc>
struct FunPoint {
	ret (*fun)(para);
	std::string id;

	MDEF void operator=(ret(*fun)(para)) {
		this->fun = fun;
		id = std::to_string(time(NULL)/(rand()%100)) + "||ID";
	}
	FunPoint(ret(*fun)(para)) {
		this->fun = fun;
		id = std::to_string(time(NULL)/(rand()%100)) + "||ID";
	}

};




template<typename funType = FunPoint<>, typename para = VOIDc>
class Event {
public:
	MDEF static std::vector<funType> funs;

	MDEF static bool request() {return NONE;}

	MDEF static void trigger(para par = para{NULL}) {
		for(size_t i = 0; i < funs.size(); ++i) {
			funs[i].fun(par);
		}
	}
};



class NothingEvent
	: public Event<>
{
public:
	MDEF static bool request() {
		if(false /*add your statement here*/ ) {
			trigger(NULL);
			return true;
		}
		return false;
	}
};

class HubOpenEvent 
	: public Event<FunPoint<InternalPCO::Hub*>,InternalPCO::Hub*>
{
public:

};

class HubChoiceChooseEvent
	: public Event<FunPoint<InternalPCO::HubChoice*>,InternalPCO::HubChoice*>
{
public:

};

class HubChoiceFailEvent
	: public Event<FunPoint<InternalPCO::Hub*>,InternalPCO::Hub*>
{

};

class LoadingScreenUpdateEvent
	: public Event<FunPoint<InternalPCO::LoadingScreen*>,InternalPCO::LoadingScreen*>
{
public:
	
};

class GameStartEvent
	: public Event<>
{

};

class GameUpdateEvent
	: public Event<>
{

};

class GameExitEvent
	: public Event<>
{

};


#endif