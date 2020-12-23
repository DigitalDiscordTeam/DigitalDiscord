#include <stdlib.h>
int main() {
    #ifdef _WIN32
    system("g++ -o DigitalDiscord.exe main.cpp Memory.cpp -std=c++17");
    #else
    system("g++ -o DigitalDiscord main.cpp Memory.cpp -std=c++17");
    #endif
}