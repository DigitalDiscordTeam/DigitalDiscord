#include "InternalSys.h"
#include "InternalLib.h"
#include "InternalFsys.h"
#include "Game.h"
#include "CommandFile.h"

int main(/*int argc, char* argv[]*/) {
	mac::pause();
	CommandFile cF("C:\\Users\\Fampu\\source\repos\\Gamehax0r\\test3.txt","test3.txt");
	DEBUG_START_
		std::cout << "cF there\n";
	DEBUG_END_
	if(!cF.run()) {
		std::cout << "Error, lol!\n";
	}
	DEBUG_START_
		std::cout << "next\n";
	DEBUG_END_
	cF.cclose();
	std::cout << "\n";
	mac::pause();
	return 0;
}