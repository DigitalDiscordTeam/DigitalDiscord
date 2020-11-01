#ifndef INTERNAL_PRETTY_CONSOLE_OUT_H
#define INTERNAL_PRETTY_CONSOLE_OUT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <Windows.h>

namespace InternalPCO { //PCO = pretty console out
	class slowPrintc {
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
			for (size_t i = 0; i < inp; ++i) {
				std::cout << ((const char*)inp)[i];
				Sleep(sleeptime);
			}
		}
		void operator<<(char inp) {
			std::cout << inp;
			Sleep(sleeptime);
		}
		void operator<<(long long inp) {
			for (size_t i = 0; i < inp; ++i) {
				std::cout << ((const char*)inp)[i];
				Sleep(sleeptime);
			}
		}

		void operator=(int time) {
			this->sleeptime = time;
		}

		void setSleeptime(int newsleeptime) {
			sleeptime = newsleeptime;
		}
	};

}

#endif
