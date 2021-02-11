#include "InternalLib.h"

InternalLib::Parser* InternalLib::Parser::addPlaceHolder(std::string to_replace, std::string replace) {
	args[to_replace] = replace;

	return this;
}
InternalLib::Parser* InternalLib::Parser::setIdents(char identStart, char identEnd) {
	this->identEnd = identEnd;
	this->identStart = identStart;

	return this;
}
std::string InternalLib::Parser::parse(std::string str) {
	std::string ret;
	std::string tmpStr;
	bool in;
	str += " ";
	for(size_t i = 0; i < str.length(); ++i) {
		if(str[i] == this->identStart) {
			in = true;
			++i; //skips the start
		}
		else if(str[i] == this->identEnd) {
			in = false;

			ret += this->args[tmpStr] != "" ? this->args[tmpStr] : this->identStart + tmpStr + this->identEnd; //if there is no known arg called tmpStr, tmpStr will be added for later parsers or other works
			tmpStr = "";
			++i; //skips the end
		}

		if(in) {
			tmpStr += str[i];
		}
		else {
			ret += str[i];
		}
	}
	return ret;
}

std::string InternalLib::sb(bool bool_) { //bool to string
	return bool_ ? "true" : "false";
}

bool InternalLib::between(float num, float min, float max) {
	return (num > min && num < max);
}

size_t InternalLib::searchForVal_i(tokenType str, std::string key) { //return the index in the str
	for(size_t i = 0; i < str.size(); ++i) {
		if(str[i] == key) {
			return i+2;
		}
	}
	throw ValueNotFoundError{};
	return -1;
}

std::string InternalLib::searchForVal(tokenType str, std::string key) {
	for(size_t i = 0; i < str.size(); ++i) {
		if(str[i] == key) {
			return str[i+2];
		}
	}
	throw ValueNotFoundError{};
	return "";
}

int InternalLib::random::randomint() {
	srand(time(NULL)%rand());
	return rand();
}