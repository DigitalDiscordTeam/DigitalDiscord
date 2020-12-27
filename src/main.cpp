#define DEBUG_LEVEL 0
#include "CommandFile.h"
#include "Memory.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalEvents.h"

int main(/*int argc, char* argv[]*/) {
    Memory::Data myData("Hello, Worlld!");

    while(INFINITY_LOOP) {
        Memory::compre(myData);
        std::cout << "c: " <<myData.data << "\n";
        Memory::recompre(myData);
        std::cout << "rc: " << myData.data << "\n";
        mac::sleep(3000);
    }

    
}