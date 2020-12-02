#include "InternalSys.h"
#include "InternalLib.h"
#include "InternalFsys.h"
#include "Game.h"
#include "CommandFile.h"

int main(int argc, char* argv[]) {
	CommandFile cF(argv[0], argv[1]);

	cF.run();
	return 0;
}