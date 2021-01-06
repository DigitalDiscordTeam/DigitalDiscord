#define DEBUG_LEVEL 0
#include "CommandFile.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalEvents.h"
#include "storage.h"
#include "Game.h"

#include <thread>



int main(/*int argc, char* argv[]*/) {
    StorageSys::mainId = std::this_thread::get_id();

}