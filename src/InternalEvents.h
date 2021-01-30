#ifndef INTERNAL_EVENTS_H
#define INTERNAL_EVENTS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalLib.h"

#include <string>
#include <vector>
#include <map>

namespace InternalPCO { //because InternalPrettyConsoleOut.h have to include this file, we have to do this workaround to use the stuff we need
	class Hub;
	class HubChoice;
	class LoadingScreen;
	class SlowPrintc;
}
class Terminal;

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

	MDEF static void trigger(para par = para{0}) {
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
			trigger();
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

class TerminalInputEvent
	: public Event<FunPoint<std::pair<std::string,Terminal*>>,std::pair<std::string,Terminal*>> 	//the input
{

};

class TerminalFailEvent
	: public Event<FunPoint<std::pair<std::string,Terminal*>>,std::pair<std::string,Terminal*>>	//the input
{

};

class TerminalExitEvent
	: public Event<FunPoint<Terminal*>,Terminal*>
{

};

class TerminalStartEvent
	: public Event<FunPoint<Terminal*>,Terminal*>
{

};

class SlowPrintClassPrintEvent
	: public Event<FunPoint<std::pair<std::string, InternalPCO::SlowPrintc*>>,std::pair<std::string, InternalPCO::SlowPrintc*>>
{

};

#endif