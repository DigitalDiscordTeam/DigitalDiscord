#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include "setup.h"

class Stor {
private:

	class newint {
	public:
		newint(int value);

		int value = 0;
	};
	class newfloat {
	public:
		newfloat(float value);

		float value = 0;
	};
	class newdouble {
	public:
		newdouble(double value);

		double value = 0;
	};
	class newccharp { //const char*
	public:
		newccharp(const char* value);

		const char* value = "0";
	};
	class newchar {
	public:
		newchar(char value);

		char value = '0';
	};
	class newbool {
	public:
		newbool(bool value);

		bool value = false;
	};

	std::vector<newint*> new_int_vec;
	std::vector<newfloat*> new_float_vec;
	std::vector<newdouble*> new_double_vec;
	std::vector <newccharp*> new_ccharp_vec;
	std::vector <newchar*> new_char_vec;
	std::vector <newbool*> new_bool_vec;

public:
	typedef std::vector<newint*>::size_type int_index;
	typedef std::vector<newfloat*>::size_type float_index;
	typedef std::vector<newdouble*>::size_type double_index;
	typedef std::vector<newccharp*>::size_type ccp_index;
	typedef std::vector<newchar*>::size_type char_index;
	typedef std::vector<newbool*>::size_type bool_index;

	~Stor();

	int_index append(int value);
	float_index append(float value);
	double_index append(double value);
	ccp_index append(const char* value);
	char_index append(char value);
	bool_index append(bool value);

	std::vector<newint*> get(int i);
	std::vector<newfloat*> get(float i);
	std::vector<newdouble*> get(double i);
	std::vector <newccharp*> get(const char* i);
	std::vector <newchar*> get(char i);
	std::vector <newbool*> get(bool i);

	bool del(const char* todel);
	bool del(const char* todel, size_t index);
	bool clear(const char* toclear, bool boolean, size_t count_to_clear = NULL);
	int clear(const char* toclear, size_t count_to_clear = NULL);

	int getwa(int x, int_index index);
	float getwa(float x, float_index index);
	double getwa(double x, double_index index);
	const char* getwa(const char* x, ccp_index index);
	char getwa(char x, char_index index);
	bool getwa(bool x, bool_index index);

	bool empty(std::string what);
};

#endif