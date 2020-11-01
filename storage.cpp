#include "storage.h"

Stor::newint::newint(int value) {
	this->value = value;
}
Stor::newfloat::newfloat(float value) {
	this->value = value;
}
Stor::newdouble::newdouble(double value) {
	this->value = value;
}
Stor::newccharp::newccharp(const char* value) {
	this->value = value;
}
Stor::newchar::newchar(char value) {
	this->value = value;
}
Stor::newbool::newbool(bool value) {
	this->value = value;
}

Stor::int_index Stor::append(int i) {
	Stor::newint* tpoint = new Stor::newint(i); //temp pointer

	Stor::new_int_vec.push_back(tpoint);

	return (std::vector<Stor::newint*>::size_type)Stor::new_int_vec.size() - 1;
}
Stor::float_index Stor::append(float i) {
	Stor::newfloat* tpoint = new Stor::newfloat(i); //temp pointer

	Stor::new_float_vec.push_back(tpoint);

	return (std::vector<Stor::newfloat*>::size_type)Stor::new_float_vec.size() - 1;
}
Stor::double_index Stor::append(double i) {
	Stor::newdouble* tpoint = new Stor::newdouble(i); //temp pointer

	Stor::new_double_vec.push_back(tpoint);

	return (std::vector<Stor::newdouble*>::size_type)Stor::new_double_vec.size() - 1;
}
Stor::ccp_index Stor::append(const char* i) {
	Stor::newccharp* tpoint = new Stor::newccharp(i); //temp pointer

	Stor::new_ccharp_vec.push_back(tpoint);

	return (std::vector<Stor::newccharp*>::size_type)Stor::new_ccharp_vec.size() - 1;
}
Stor::char_index Stor::append(char i) {
	Stor::newchar* tpoint = new Stor::newchar(i); //temp pointer

	Stor::new_char_vec.push_back(tpoint);

	return (std::vector<Stor::newchar*>::size_type)Stor::new_ccharp_vec.size() - 1;
}
Stor::bool_index Stor::append(bool i) {
	Stor::newbool* tpoint = new Stor::newbool(i); //temp pointer

	Stor::new_bool_vec.push_back(tpoint);

	return (std::vector<Stor::newbool*>::size_type)Stor::new_bool_vec.size() - 1;
}

std::vector<Stor::newint*> Stor::get(int i) {
	return new_int_vec;
}
std::vector<Stor::newfloat*> Stor::get(float i) {
	return new_float_vec;
}
std::vector<Stor::newdouble*> Stor::get(double i) {
	return new_double_vec;
}
std::vector<Stor::newccharp*> Stor::get(const char* i) {
	return new_ccharp_vec;
}
std::vector<Stor::newchar*> Stor::get(char i) {
	return new_char_vec;
}
std::vector<Stor::newbool*> Stor::get(bool i) {
	return new_bool_vec;
}

bool Stor::del(const char* todel) {

	if (todel == "int")
	{
		if (new_int_vec.empty()) { return false; }
		for (size_t i = 0; i < Stor::new_int_vec.size(); ++i)
		{
			delete Stor::new_int_vec[i];
			Stor::new_int_vec[i] = nullptr;
		}
		return true;
	}
	else if (todel == "float")
	{
		if (new_float_vec.empty()) { return false; }
		for (size_t i = 0; i < Stor::new_float_vec.size(); ++i)
		{
			delete Stor::new_float_vec[i];
			Stor::new_float_vec[i] = nullptr;
		}
		return true;
	}
	else if (todel == "double")
	{
		if (new_double_vec.empty()) { return false; }
		for (size_t i = 0; i < Stor::new_double_vec.size(); ++i)
		{
			delete Stor::new_double_vec[i];
			Stor::new_double_vec[i] = nullptr;
		}
		return true;
	}
	else if (todel == "ccharp")
	{
		if (new_ccharp_vec.empty()) { return false; }
		for (size_t i = 0; i < Stor::new_ccharp_vec.size(); ++i)
		{
			delete Stor::new_ccharp_vec[i];
			Stor::new_ccharp_vec[i] = nullptr;
		}
		return true;
	}
	else if (todel == "char")
	{
		if (new_char_vec.empty()) { return false; }
		for (size_t i = 0; i < Stor::new_char_vec.size(); ++i)
		{
			delete Stor::new_char_vec[i];
			Stor::new_char_vec[i] = nullptr;
		}
		return true;
	}
	else if (todel == "bool")
	{
		if (new_bool_vec.empty()) { return false; }
		for (size_t i = 0; i < Stor::new_bool_vec.size(); ++i)
		{
			delete Stor::new_bool_vec[i];
			Stor::new_bool_vec[i] = nullptr;
		}
		return true;
	}
	else
	{
		return false;
	}

}
bool Stor::del(const char* todel, size_t index) {

	if (todel == "int")
	{
		if (new_int_vec.empty()) { return false; }

		delete Stor::new_int_vec[index];
		Stor::new_int_vec[index] = nullptr;

		return true;
	}
	else if (todel == "float")
	{
		if (new_float_vec.empty()) { return false; }

		delete Stor::new_float_vec[index];
		Stor::new_float_vec[index] = nullptr;

		return true;
	}
	else if (todel == "double")
	{
		if (new_double_vec.empty()) { return false; }

		delete Stor::new_double_vec[index];
		Stor::new_double_vec[index] = nullptr;

		return true;
	}
	else if (todel == "ccharp")
	{
		if (new_ccharp_vec.empty()) { return false; }

		delete Stor::new_ccharp_vec[index];
		Stor::new_ccharp_vec[index] = nullptr;

		return true;
	}
	else if (todel == "char")
	{
		if (new_char_vec.empty()) { return false; }

		delete Stor::new_char_vec[index];
		Stor::new_char_vec[index] = nullptr;

		return true;
	}
	else if (todel == "bool")
	{
		if (new_bool_vec.empty()) { return false; }

		delete Stor::new_bool_vec[index];
		Stor::new_bool_vec[index] = nullptr;

		return true;
	}
	else
	{
		return false;
	}

}

bool Stor::clear(const char* toclear, bool bolean, size_t count_to_clear) {
	//checks if the input is ok
	if (count_to_clear != 0 && toclear == "int" && Stor::new_int_vec.size() < count_to_clear) { return false; }
	else if (count_to_clear != 0 && toclear == "float" && Stor::new_float_vec.size() < count_to_clear) { return false; }
	else if (count_to_clear != 0 && toclear == "double" && Stor::new_double_vec.size() < count_to_clear) { return false; }
	else if (count_to_clear != 0 && toclear == "ccharp" && Stor::new_ccharp_vec.size() < count_to_clear) { return false; }
	else if (count_to_clear != 0 && toclear == "char" && Stor::new_char_vec.size() < count_to_clear) { return false; }
	else if (count_to_clear != 0 && toclear == "bool" && Stor::new_bool_vec.size() < count_to_clear) { return false; }
	//do stuff
	if (count_to_clear != 0 || count_to_clear < 0)
	{
		for (size_t i = 0; i < count_to_clear; ++i)
		{
			if (toclear == "int") {
				Stor::new_int_vec[i] = 0;
			}
			if (toclear == "float") {
				Stor::new_float_vec[i] = 0;
			}
			if (toclear == "double") {
				Stor::new_double_vec[i] = 0;
			}
			if (toclear == "ccharp") {
				Stor::new_ccharp_vec[i] = 0;
			}
			if (toclear == "char") {
				Stor::new_char_vec[i] = 0;
			}
			if (toclear == "bool") {
				Stor::new_bool_vec[i] = 0;
			}
		}

		return true;
	}
	else
	{
		if (toclear == "int") {
			Stor::new_int_vec.clear();
		}
		if (toclear == "float") {
			Stor::new_float_vec.clear();
		}
		if (toclear == "double") {
			Stor::new_double_vec.clear();
		}
		if (toclear == "ccharp") {
			Stor::new_ccharp_vec.clear();
		}
		if (toclear == "char") {
			Stor::new_char_vec.clear();
		}
		if (toclear == "bool") {
			Stor::new_bool_vec.clear();
		}
		return true;
	}

}
int Stor::clear(const char* toclear, size_t count_to_clear) {
	//checks if the input is ok
	if (count_to_clear != 0 && toclear == "int" && Stor::new_int_vec.size() < count_to_clear) { return -1; }
	else if (count_to_clear != 0 && toclear == "float" && Stor::new_float_vec.size() < count_to_clear) { return -1; }
	else if (count_to_clear != 0 && toclear == "double" && Stor::new_double_vec.size() < count_to_clear) { return -1; }
	else if (count_to_clear != 0 && toclear == "ccharp" && Stor::new_ccharp_vec.size() < count_to_clear) { return -1; }
	else if (count_to_clear != 0 && toclear == "char" && Stor::new_char_vec.size() < count_to_clear) { return -1; }
	else if (count_to_clear != 0 && toclear == "bool" && Stor::new_bool_vec.size() < count_to_clear) { return -1; }
	//do stuff
	if (count_to_clear != 0 || count_to_clear < 0)
	{
		for (size_t i = 0; i < count_to_clear; ++i)
		{
			if (toclear == "int") {
				Stor::new_int_vec[i] = 0;
			}
			if (toclear == "float") {
				Stor::new_float_vec[i] = 0;
			}
			if (toclear == "double") {
				Stor::new_double_vec[i] = 0;
			}
			if (toclear == "ccharp") {
				Stor::new_ccharp_vec[i] = 0;
			}
			if (toclear == "char") {
				Stor::new_char_vec[i] = 0;
			}
			if (toclear == "bool") {
				Stor::new_bool_vec[i] = 0;
			}
		}

		if (toclear == "int") {
			return Stor::new_int_vec.size();
		}
		if (toclear == "float") {
			return Stor::new_float_vec.size();
		}
		if (toclear == "double") {
			return Stor::new_double_vec.size();
		}
		if (toclear == "ccharp") {
			return Stor::new_ccharp_vec.size();
		}
		if (toclear == "char") {
			return Stor::new_char_vec.size();
		}
		if (toclear == "bool") {
			return Stor::new_bool_vec.size();
		}

	}
	else
	{
		if (toclear == "int") {
			Stor::new_int_vec.clear();
		}
		if (toclear == "float") {
			Stor::new_float_vec.clear();
		}
		if (toclear == "double") {
			Stor::new_double_vec.clear();
		}
		if (toclear == "ccharp") {
			Stor::new_ccharp_vec.clear();
		}
		if (toclear == "char") {
			Stor::new_char_vec.clear();
		}
		if (toclear == "bool") {
			Stor::new_bool_vec.clear();
		}
		return 0;
	}

}

Stor::~Stor() {
	del("int");
	del("float");
	del("double");
	del("ccharp");
	del("char");
	del("bool");
}

int Stor::getwa(int x, int_index index) {
	return get(x)[index]->value;
}
float Stor::getwa(float x, float_index index) {
	return get(x)[index]->value;
}
double Stor::getwa(double x, double_index index) {
	return get(x)[index]->value;
}
const char* Stor::getwa(const char* x, ccp_index index) {
	return get(x)[index]->value;
}
char Stor::getwa(char x, char_index index) {
	return get(x)[index]->value;
}
bool Stor::getwa(bool x, bool_index index) {
	return get(x)[index]->value;
}


bool Stor::empty(std::string what) {
	try
	{
		if (what == "int")
		{
			return Stor::new_int_vec.empty();
		}
		else if (what == "float")
		{
			return Stor::new_float_vec.empty();
		}
		else if (what == "double")
		{
			return Stor::new_double_vec.empty();
		}
		else if (what == "ccharp")
		{
			return Stor::new_ccharp_vec.empty();
		}
		else if (what == "char")
		{
			return Stor::new_char_vec.empty();
		}
		else if (what == "bool")
		{
			return Stor::new_bool_vec.empty();
		}
		else
		{
			std::perror("Error in Stor::empty: wrong input!\n");
			return 0;
		}
	}
	catch (...)
	{
		std::perror("Error in Stor::empty: wrong input!\n");
		return 0;
	}
}