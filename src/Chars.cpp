#include "Chars.h"

void Chars::Sayas::sys(std::string message, std::string ext) {
    std::cout << "[SYSTEM] "; std::cout.flush();
    Custom::sys_SP << message;
    std::cout << ext; //print something without slowPrint (for example: \n)
}

void Chars::Sayas::ikarus(std::string message, std::string ext) {
    std::cout << "[Ikarus] " << std::flush;
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


void Chars::Special::Ikarus::Do::say(std::string message, std::string ext) {
    Chars::Sayas::ikarus(message,ext);
}

void Chars::init(int customTime) {
    Custom::ikarus_SP = customTime;
    Custom::ikarus_SP.getID() = "Ikarus_sayCHARS0";
    Custom::ikarus_SP = customTime;
    Custom::rand_SP = customTime;
}