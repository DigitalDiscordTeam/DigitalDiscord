#ifndef INTERNAL_PRETTY_CONSOLE_OUT_H
#define INTERNAL_PRETTY_CONSOLE_OUT_H

#include "InternalDef.h"

#include <time.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <functional>

namespace InternalPCO { //PCO = pretty console out
	class SlowPrintc {
	private:
		int sleeptime = 0;
	public:
		void operator<<(const char* inp) {
			for (size_t i = 0; i < strlen(inp); ++i) {
				std::cout << inp[i];
				mac::sleep(sleeptime);
			}
		}
		void operator<<(std::string inp) {
			for (size_t i = 0; i < inp.length(); ++i) {
				std::cout << inp[i];
				mac::sleep(sleeptime);
			}
		}
		void operator<<(int inp) {
			for (long i = 0; i < inp; ++i) {
				std::cout << ((const char*)inp)[i];
				mac::sleep(sleeptime);
			}
		}
		void operator<<(char inp) {
			std::cout << inp;
			mac::sleep(sleeptime);
		}
		void operator<<(long long inp) {
			for (long i = 0; i < inp; ++i) {
				std::cout << ((const char*)inp)[i];
				mac::sleep(sleeptime);
			}
		}

		void operator=(int time) {
			this->sleeptime = time;
		}

		void operator++() {
			this->sleeptime += 1;
		}

		void operator--() {
			this->sleeptime -= 1;
		}

		void setSleeptime(int newsleeptime) {
			sleeptime = newsleeptime;
		}
	}slowPrint;

	class LoadingScreen {
	private:
		long tmp_len = 0;
	public:
		long length = 0;
		bool clear = false;
		int clearWaitTime = 0;

		char logo = '#';

		LoadingScreen(long length, int clearWaitTime, bool clear, char logo) {
			this->length = length;
			this->clear = clear;
			this->clearWaitTime = clearWaitTime;
			this->logo = logo;
		}

		bool next(std::string message = "") {
			tmp_len += 1;
			std::cout << "\r[";
			for (long i = 0; i < length; ++i) {
				if (i > tmp_len) {
					std::cout << " ";
				}
				else {
					std::cout << logo;
				}
			}
			std::cout << "] " << message << "                      "; //to clear all rest of the last message

			if (tmp_len == length) {
				length = 0;
				tmp_len = 0;

				if (clear) {
					mac::sleep(clearWaitTime); // TODO: Linux compatibility and such stuff
					mac::clearScreen();
				}
				return true;
			}

			return false;
		}
	}loadingScreen(10, 0, false, '#');

	class VisualCounter {
		long tmp_len = 0;
	public:
		long hight = 0;

		VisualCounter(long hight) {
			this->hight = hight;
		}

		bool next(std::string message = "") {
			tmp_len += 1;
			std::cout << "\r" << tmp_len << "/" << hight << "  " << message;

			if (tmp_len >= hight) {
				std::cout << "\n";
				hight = 0;
				tmp_len = 0;
				return true;
			}
			return false;
		}
	};

	typedef class VisualTimer VisualTimer;
	class VisualTimer {
	private:
		long tmp_long = 0;
	public:
		long time = 0;
		float delay = 0;

		VisualTimer(long time, float delay) { //delay in seconds
			this->time = time;
			this->delay = 100 * delay;
		}

		void operator=(VisualTimer& timer) {
			this->delay = timer.delay;
			this->time = timer.time;
			this->tmp_long = 0;
		}

		void operator+=(VisualTimer& timer) {
			this->delay += timer.delay;
			this->time += timer.time;
			this->tmp_long = 0;
		}

		void operator++() {
			time += 1;
		}
		void operator--() {
			time -= 1;
		}

		void start() {
			tmp_long = 0;
			for (; tmp_long < time + 1; ++tmp_long) {
				//std::cout << time << " " << tmp_long << " " << (time - tmp_long) / 100 << "\n";
				std::cout << "\rT - " << (time - tmp_long) << " ";
				mac::sleep(delay);
			}
			std::cout << "\n";
		}

		bool is_end() {
			return tmp_long == time ? true : false;
		}

		void reset() {
			tmp_long = 0;
		}
	};

	void corruptedLine(long length) {
		for (long i = 0; i < length; ++i) {
			srand(time(NULL) + i);
			std::cout << ((char)(rand() - i / 5));
		}
	}

	class HubChoice {
	public:
		void (*func)(void);
		std::string id;
		std::string name;

		HubChoice(void (*func)(void),std::string name, std::string id) {
			this->id = id;
			this->name = name;
			this->func = func;
		}

		void run() {
			func();
		}
	};

	class Hub {
	public:
		InternalPCO::SlowPrintc printer;
		bool hiding = true;
		std::vector<HubChoice> choices;
		std::string layout; //comming soon
		std::string name;

		Hub(std::string name, std::vector<HubChoice> choices, std::string customLayout = "STD") {
			printer = 500;
			this->name = name;
			layout = customLayout;
			this->choices = choices;
		}

		void show() {
			hiding = false;
			mac::clearScreen();

			if(layout == "STD") {
				std::cout << "-------------# Wellcome to " << name << " #-------------\n";
				
				for(size_t i = 0; i < choices.size(); ++i) {
					std::cout << "        " << i+1 << ".)  " << choices[i].name << "\n";
				}

				std::cout << "\n\n"
						  << "Your choice:";
				std::string inp;
				std::getline(std::cin,inp);
				mac::sleep(100);
				mac::clearScreen();
				try {
					choices[std::stoi(inp)-1].run();
				}
				catch(...) {
					show();
				}
				hiding = true;
						  
			}
		}
	};
}

#endif