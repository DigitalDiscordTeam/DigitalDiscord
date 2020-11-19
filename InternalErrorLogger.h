#ifndef INTERNAL_ERROR_LOGGER_H
#define INTERNAL_ERROR_LOGGER_H

#include "InternalDef.h"

#include <time.h>
#include <vector>
#include <string>
#include <iostream>

#include "InternalErrors.h"

namespace InternalErrLog {
	
	class ErrLog {
	public:
		std::vector<int> Err_time;
		std::vector<std::string> Err_type;

		void append(int time, std::string err) {
			Err_time.push_back(time);
			Err_type.push_back(err);
		}

		std::vector<int> get(std::string Err) {
			std::vector<int> ret_vec;

			for (size_t i = 0; i < Err_type.size(); ++i) {
				if (Err_type[i] == Err) {
					ret_vec.push_back(Err_time[i]);
				}
			}

			return ret_vec;
		}

		std::vector<std::string> get(int time) {
			std::vector<std::string> ret_vec;

			for (size_t i = 0; i < Err_time.size(); ++i) {
				if (Err_time[i] == time) {
					ret_vec.push_back(Err_type[i]);
				}
			}

			return ret_vec;
		}

		void printErr() {
			for (size_t i = 0; i < Err_type.size(); ++i) {
				std::cout << Err_type[i] << " : " << Err_time[i] << "\n";
			}
		}
	};

	ErrLog LogMain;
}

#endif
