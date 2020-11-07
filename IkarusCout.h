#ifndef IKARUS_COUT_H
#define IKARUS_COUT_H

#include "InternalPrettyConsoleOut.h"

namespace IkarusCout {

	InternalPCO::SlowPrintc IkarusSP;

	void say(std::string message, bool back = false) {
		std::cout << "[Ikarus] ";
		IkarusSP << message;

		if (back) { std::cout << "\n"; }
	}
}

#endif
