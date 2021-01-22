#include "Game.h"

#include <thread>

void Game::update() {
	ExternalPlugins::update();
	using namespace Chars::Special;
	System::doPaths();
	GameUpdateEvent::trigger();

	
	if(std::this_thread::get_id() != StorageSys::mainId) {
		std::this_thread::sleep_for(std::chrono::duration<int>(10));
		DEBUG_WITH_FLUSH("update_wait with id:" << std::this_thread::get_id())
	}
	
}

void onExit();

void Game::start(bool showcase, int sleepTime) {
	if (showcase) {
		InternalPCO::LoadingScreen screen(10, 10, true, '#');

		screen.next("Check paths and gernerate them..."); //step 1
		System::doPaths();
		mac::sleep(sleepTime);

		screen.next("Look if all sys-Files are here...."); //step 2
		for(size_t i = 0; i < mac::allStdFiles.size(); ++i) {
			if(!fs::exists(System::pathtoDir + mac::allStdFiles[i])) {
				InternalFsys::sys::makeFile(mac::allStdFiles[i],System::pathtoDir);
			}
		}
		mac::sleep(sleepTime);
		
		screen.next("Check if all files are here..."); //step 3
		InternalFileVec::update(System::pathtoDir);
		mac::sleep(sleepTime);

		screen.next("Set up plugins..."); //step 4
		ExternalPlugins::start();
		mac::sleep(sleepTime);

		screen.next("Start GameStartEvent...");	//step 5
		GameStartEvent::trigger();
		mac::sleep(sleepTime);

		screen.next("setup at-exit functions..."); //step 6
		std::atexit([](){
			onExit();
		});
		mac::sleep(sleepTime);

		screen.next("Init main-terminal..."); //step 7
		Terminal::InitMain();
		mac::sleep(sleepTime);

		screen.clear(false);
	}
}

void onExit() {
	GameExitEvent::trigger();
	//soon
	/*
	std::string path = System::pathtoDir + "DD_Config.txt";
	InternalFsys::write(
		path,
		"LastErrorCount",
		std::to_string(InternalErrLog::LogMain.Err_type.size())
	);
	InternalFsys::write(
		path,
		"RoadValue",
		std::to_string(InternalRV::RoadValue)
	);

	
	path = System::pathtoDir + "IkarusBuild.txt";
	InternalFsys::write(
		path,
		"PowerKernel", //work here looool
		std::to_string(Chars::Special::Ikarus::Memory::PowerCernal.get())
	);
	InternalFsys::write(
		path,
		"RoadValue",
		std::to_string(InternalRV::RoadValue)
	);
	InternalFsys::write(
		path,
		"RoadValue",
		std::to_string(InternalRV::RoadValue)
	);

	*/
}



