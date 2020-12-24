#ifndef INTERNAL_PRETTY_CONSOLE_OUT_H
#define INTERNAL_PRETTY_CONSOLE_OUT_H

#include "InternalDef.h"
#include "InternalFsys.h"
#include "InternalLib.h"
#include "InternalSys.h"

#include <time.h>
#include <iostream>
#include <string>
#include <stdio.h>

namespace InternalPCO { //PCO = pretty console out
	class SlowPrintc {
	private:
		int sleeptime = 0;
	public:
		void operator<<(const char* inp);

		void operator<<(std::string inp);

		void operator<<(int inp);

		void operator<<(char inp);

		void operator<<(long long inp);

		void operator=(int time);

		void operator++();

		void operator--();

		void setSleeptime(int newsleeptime);

	};

	class LoadingScreen {
	private:
		long tmp_len = 0;
	public:
		long length = 0;
		bool clearS = false;
		int clearWaitTime = 0;

		char logo = '#';

		LoadingScreen(long length, int clearWaitTime, bool clearS, char logo);

		bool next(std::string message = "");

		void clear(bool cls);

	};

	class VisualCounter {
		long tmp_len = 0;
	public:
		long hight = 0;

		VisualCounter(long hight);

		bool next(std::string message = "");

		void clear();
	};

	typedef class VisualTimer VisualTimer;
	class VisualTimer {
	private:
		long tmp_long = 0;
	public:
		long time = 0;
		float delay = 0;

		VisualTimer(long time, float delay);

		void operator=(VisualTimer& timer);

		void operator+=(VisualTimer& timer);

		void operator++();

		void operator--();

		void start();

		bool is_end();

		void reset();
	};

	void corruptedLine(long length);

	void errorMessage(std::string message, int stime = 5000);

	class HubChoice {
	public:
		void (*func)();
		std::string id;
		std::string name;
		
		HubChoice(void (*func)(),std::string name, std::string id);

		void run();
	};

	class Hub {
	public:
		bool hiding = true;
		std::vector<HubChoice> choices;
		std::string layout;
		std::string name;

		Hub(std::string name, std::vector<HubChoice> choices, std::string customLayout = "STD");

		void show();
	};

	
}

#endif