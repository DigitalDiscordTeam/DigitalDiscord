#ifndef INTERNAL_PRETTY_CONSOLE_OUT_H
#define INTERNAL_PRETTY_CONSOLE_OUT_H

#include "InternalDef.h"

#include <time.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <Windows.h>

namespace InternalPCO { //PCO = pretty console out
	class SlowPrintc {
	private:
		int sleeptime = 0;
	public:
		void operator<<(const char* inp) {
			for (size_t i = 0; i < strlen(inp); ++i) {
				std::cout << inp[i];
				Sleep(sleeptime);
			}
		}
		void operator<<(std::string inp) {
			for (size_t i = 0; i < inp.length(); ++i) {
				std::cout << inp[i];
				Sleep(sleeptime);
			}
		}
		void operator<<(int inp) {
			for (long i = 0; i < inp; ++i) {
				std::cout << ((const char*)inp)[i];
				Sleep(sleeptime);
			}
		}
		void operator<<(char inp) {
			std::cout << inp;
			Sleep(sleeptime);
		}
		void operator<<(long long inp) {
			for (long i = 0; i < inp; ++i) {
				std::cout << ((const char*)inp)[i];
				Sleep(sleeptime);
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
					Sleep(clearWaitTime); // TODO: Linux compatibility and such stuff
					system("cls");
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
				Sleep(delay);
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



}

#endif