#define DEBUG_LEVEL 0
#include "CommandFile.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalEvents.h"
#include "storage.h"
#include "Game.h"
#include "ExternalPlugins.h"

#include <thread>

#include "Terminal.h"

int main(/*int argc, char* argv[]*/) {
    //TerminalFailEvent::funs.push_back(FunPoint<std::string>([](std::string str){
    //    std::cout << "command: \"" << str << "\" failed!\n";
    //    return IL::c_VOID();
    //}));
    ExternalPlugins::start();
    StorageSys::mainId = std::this_thread::get_id();
    Terminal::InitMain();

    Terminal::mainTerminal.addFun([](tokenType tokens,Terminal* ptr)->bool {
        if(tokens.size() == 1) {
            return true;
        }
        std::cout << tokens[1] << "\n";
        std::cout << InternalFsys::readNormal(tokens[1]) << "\n";
    },"read");
    
        
    Terminal::mainTerminal.run();
    
}