#include "Chars.h"

void Chars::Sayas::sys(std::string message, std::string ext) {
    std::cout << "[SYSTEM] "; std::cout.flush();
    Custom::sys_SP << message;
    std::cout << ext; //print something without slowPrint (for example: \n)
}

void Chars::Sayas::ikarus(std::string message, std::string ext) {
    std::cout << "[Ikarus] "; std::cout.flush();
	Custom::ikarus_SP << message;
    std::cout << ext;
}

void Chars::Sayas::random(std::string message, long length, std::string ext) {
    std::cout << "[";
    InternalPCO::corruptedLine(length);
    std::cout << "] ";
    Custom::rand_SP << message;
    std::cout << ext;

}

bool Chars::Special::Ikarus::Memory::IkarusRememberMap(Events::Event Event) {
    return IkarusOwnMap[Event.id] == 0 ? false : true;
}

void Chars::Special::Ikarus::Memory::mapUpdate() {
    IkarusOwnMap = InternalEventMap::EventMap;
}

void Chars::init(int customTime) {
    Custom::ikarus_SP = customTime;
    Custom::ikarus_SP = customTime;
    Custom::rand_SP = customTime;
}