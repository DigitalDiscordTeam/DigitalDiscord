#ifndef SPEAK_BUBBLES_H_
#define SPEAK_BUBBLES_H_

#include "InternalDef.h"
#include "Chars.h"
#include "InternalFsys.h"
#include "InternalPrettyConsoleOut.h"
#include "Terminal.h"


namespace SpeakBubbles {
    MDEF InternalPCO::SlowPrintc print;
    MDEF void initPrint() {
        print.setSleeptime(100);
        print.getID() = "SpBu_PRINT01";

        SlowPrintClassPrintEvent::funs.push_back(FunPoint<std::pair<std::string,InternalPCO::SlowPrintc*>>([](std::pair<std::string,InternalPCO::SlowPrintc*> inp)->VOIDc {
            if(inp.second->getID() == "SpBu_PRINT01" || inp.second->getID() == "Ikarus_sayCHARS0") {
                mac::sleep(1000);
            }
        }));
    }

    MDEF void hello() {
        using namespace Chars::Special;
        
        print << "Booting system...";
        
        mac::clearScreen();

        print << "Setting up...";
        
        mac::clearScreen();

        print << "Searching for updates...";
        
        mac::clearScreen();

        print << "Finished! No errors or exceptions found!";
        
        mac::clearScreen();

        Ikarus::Do::say("Hello, ");
        
        print << "I'm Ikarus!\n";

        Ikarus::Do::say("Welcome to DigitalDiscord!\n");
        
        Ikarus::Do::say("A product of the Digital.inc to test the humanity!\n");
        
        Ikarus::Do::say("You installed this programm, so you must be one of the few people I've to test.\n");

        Ikarus::Do::say("So, Mr. " + System::getSysUsername_s() + ", Lets do our first test ^^\n");

        Ikarus::Do::say("First thing: please try to type in \"echo Hello World\"\n");
    }

    MDEF void firstQuest() {
        using namespace Chars::Special;
        Terminal ter("Terminal0","$ ");
        TerminalInputEvent::funs.push_back(FunPoint<std::pair<std::string,Terminal*>>([](std::pair<std::string,Terminal*> inp)->IL::c_VOID {
            if(inp.first == "echo Hello World" || inp.first == "echo hello world") {
                inp.second->stop();
            }
            return {};
        }));
        ter.addFun([](tokenType tokens, Terminal* terminal, Terminal::tstorage& dptr)->bool {
            for(size_t i = 1; i < tokens.size(); ++i) {
                std::cout << tokens[i] << " ";
            }
            return false;
        },"echo");
        ter.run();
        
        ter.funs.pop_back(); //TODO: more savety
        Ikarus::Do::say("Well done. The command \"echo\" prints out any text you want on the console\n");
        Ikarus::Do::say("Now try to open a Hub, \"hopen main\" should do that!\n");
        

        
        
    }

    
}

#endif