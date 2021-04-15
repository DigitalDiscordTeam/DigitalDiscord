#include "InternalDef.h"

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
#include "InternalVirtual.h"
#include "InternalStandardParserLibarary.h"

#include <vector>

void sleepFor(time_t seconds) { //for tests
    auto now = std::chrono::system_clock::now();

    while(true) {
        if(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) >= std::chrono::system_clock::to_time_t(now) + seconds) {
            break;
        }
    }
}

static InternalLib::LangParser test = InternalLib::LangParser()
                                .setArgPrefix('-')
                                ->include(STDParser::io)
                                ->include(STDParser::math)
                                ->include(STDParser::variables)
                                ->include(STDParser::system)
                                //->include(STDParser::external)
                                ->setFile("playground.txt")
                                ->setArgPrefix('-')
                                ->setVariableCall('$')
                                ->toInstance();


int main(int argc, char* argv[]) {
    if(argc > 1 && std::string(argv[1]) == "--debug") {
        mac::debuglevel = std::stoi(std::string(argv[2]));
    }
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
    }

    mac::pause();
    */
   
    try {
        test.addOperators({
            STDOperators::plus,
            STDOperators::minus,
            STDOperators::times,
            STDOperators::power,
            STDOperators::div,
            STDOperators::mod,
            InternalLib::Handlers::Operator("==",[](int left, int right)->int {
                return left == right;
            })
        });
        //auto x = InternalFsys::splitTokens(" ","Hello World, \"Hello, World\"");
        //InternalLib::PcompareStrings(x);
        //std::cout << InternalLib::vecToStr(x) << "\n";
        test.parse();
    }
    catch(std::exception& err) {
       std::cout << err.what() << "\n";
    }
    
    mac::pause();
        
}
