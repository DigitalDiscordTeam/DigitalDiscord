#ifndef INTERNAL_ERROR_LOGGER_H
#define INTERNAL_ERROR_LOGGER_H

#include "InternalDef.h"
#include "InternalErrors.h"

#include <time.h>
#include <vector>
#include <string>
#include <iostream>

namespace InternalErrLog {
	
	class ErrLog {
	public:
		std::vector<int> Err_time;
		std::vector<std::string> Err_type;

		void append(int time, std::string err);

		std::vector<int> get(std::string Err);

		std::vector<std::string> get(int time);

		void printErr();
	};

	MDEF ErrLog LogMain;
}

#endif
