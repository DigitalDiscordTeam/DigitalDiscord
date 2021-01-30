#include "InternalDef.h"
#include <thread>

void mac::tsleep(unsigned time) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(time));
}

#ifdef USE_WIN_
#include <windows.h>

void mac::sleep(unsigned milliseconds) {
    Sleep(milliseconds);
}

void mac::clearScreen() {
    system("cls");
}

#elif defined(USE_LINUX_)
#include <unistd.h>

void mac::sleep(unsigned milliseconds) {
    usleep(milliseconds * 1000); // takes microseconds
}

void mac::clearSrceen() {
    system("clear");
}

#else // USE_UNKNOWN_
void mac::sleep(unsigned milliseconds) {
        
}

void mac::clearScreen() {
        
}

#endif

void mac::pause() {
    std::cout << "Please press any button...";
    if(!getchar() == '\n') {
        std::cout << "\n";
    }
}