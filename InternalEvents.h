#ifndef INTERNAL_EVENTS_H
#define INTERNAL_EVENTS_H

#include "InternalFsys.h"
#include <time.h>

namespace Event {
	class Testc {
	public:
		static const char* what() {
			return "Test";
		}

		static void trigger() {
			std::cout << "Test passed!\n";	
		}

	}Test;

	class Spamc {
	public:
		static const char* what() {
			return "A function to spam random things";
		}

		static void trigger() {
			srand(time(NULL));
			char assc[21] = { 'a','?','#','G','f',';','_','^','2','%',']','\\','=','ä','Ä','r','g','S','*','~','Ö' };
			for (int i = 0; i < sizeof(assc) * 3; ++i) {
				std::cout << assc[rand() % (sizeof(assc))];
				if (rand() % 12 == 5) {
					std::cout << "\n";
				}
			}
			std::cout << "\n";
			
		}

	}Spam;

	class CheckCorruptionc {
	public:
		static const char* what() {
			return "CheckCorruption";
		}

		static void trigger() {
			
		}

	}CheckCorruption;
}

#endif