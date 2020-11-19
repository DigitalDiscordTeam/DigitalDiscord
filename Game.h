#ifndef INTRO_H
#define INTRO_H

#include "InternalDef.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalErrors.h"
#include "InternalSys.h"
#include "InternalFsys.h"
#include "InternalEventMap.h"
#include "IkarusStd.h"
#include "InternalFileVec.h"


namespace Game {
	void update() {
		Setup::checkIfPaths();
		InternalEventMap::update();

		Ikarus::Memory::mapUpdate();
	}

	void start(bool showcase = false) {
		if (showcase) {
			InternalPCO::LoadingScreen screen(10, 10, true, '#');

			screen.next("Check paths and gernerate them..."); //step 1
			Setup::checkIfPaths();
			if (!Setup::dirPathExits) {
				Setup::createPath();
			}

			screen.next("Look if all sys-Files are here...."); //step 2
			if (!std::experimental::filesystem::exists(Setup::pathtoDir + "DD_Cryp.txt")) {
				InternalFsys::makeFile(Setup::pathtoDir + "DD_Eve.txt", "");
			}
			
			screen.next("Check if all files are here...");

			InternalFileVec::update(Setup::pathtoDir);


		}
	}
}
#endif