#include "Game.h"

void Game::update() {
	using namespace Chars::Special;
	System::checkIfPaths();
	InternalEventMap::update();

	Ikarus::Memory::mapUpdate();
	/*
	if(std::this_thread::get_id() != StorageSys::mainId) {
		std::this_thread::sleep_for(std::chrono::duration<int>(10));
		DEBUG_WITH_FLUSH("update_wait with id:" << std::this_thread::get_id())
	}
	*/

	//ExternalPlugins::update();
}

void Game::start(bool showcase) {
	if (showcase) {
		InternalPCO::LoadingScreen screen(10, 10, true, '#');

		screen.next("Check paths and gernerate them..."); //step 1
		System::checkIfPaths();
		if (!System::dirPathExits) {
			System::createPath();
		}
		mac::sleep(500);

		screen.next("Look if all sys-Files are here...."); //step 2
		for(size_t i = 0; i < mac::allStdDirs.size(); ++i) {
			if(fs::exists(System::pathtoDir + mac::allStdDirs[i])) {
				InternalFsys::sys::makeDir(mac::allStdDirs[i]);
			}
		}
		mac::sleep(500);
			
		screen.next("Check if all files are here...");
		InternalFileVec::update(System::pathtoDir);
		mac::sleep(500);

		screen.next("Set up plugins...");
		//ExternalPlugins::start();
		mac::sleep(500);

		screen.clear(false);

	}
}