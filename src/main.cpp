#include "InternalDef.h"
#include "CommandFile.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalEvents.h"
#include "storage.h"
#include "Game.h"
#include "InternalSys.h"
#include "ExternalPlugins.h"
#include "Terminal.h"
#include "InternalSys.h"
#include "InternalErrorLogger.h"
#include "storage.h"
#include "SpeakBubbles.h"


//TODO: virtual.h
//TODO: delete the "Internal" prefix (and the "external")

void sleepFor(time_t seconds) { //for tests
    auto now = std::chrono::system_clock::now();

    while(true) {
        if(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) >= std::chrono::system_clock::to_time_t(now) + seconds) {
            break;
        }
    }
}


int main(/*int argc, char* argv[]*/) {
    /*
    StorageSys::mainId = std::this_thread::get_id();
    Game::start();
    InternalPCO::Hub Menue("Start Screen",{InternalPCO::HubChoice([](){

    },"Start","StartChoice__01"),InternalPCO::HubChoice([](){
        exit(0);
    },"Exit","ExitChoice__02")});
    Chars::init(100);
    try {
    SpeakBubbles::initPrint();
    SpeakBubbles::hello();
    SpeakBubbles::firstQuest();
    }
    catch(std::exception& err) {
        std::cout << "an Error was catched: " << err.what() << "\n";
    }*/
    Terminal nTer("NewTerminal");
    
    nTer.addFun([](tokenType tt, Terminal* ptr, Terminal::tstorage& dptr)->bool {
        for(size_t i = 0; i < dptr.Datas.size(); ++i) {
            std::cout << i << "\t\t\t" << dptr.Datas[i].string;
            std::cout << "\n";
        }
        dptr.add(tt[1],std::to_string(tt.size()));
    },"test")->run();
        
}