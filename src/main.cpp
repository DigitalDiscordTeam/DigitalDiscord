#define DEBUG_LEVEL 1
#include "CommandFile.h"
#include "Memory.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalEvents.h"

class onNothing
    : public EventHandler
{
public:
    onNothing(nothingEve& event) {
        onFun.fun = []()->void {
            std::cout << "handler is here lol\n";
        };
        eve = &event;
        onFun.id = "onFun" + std::to_string(time(NULL)/(rand()%100)) + "id";
        eve->funs.push_back(onFun);
    }
    
};
MDEF onNothing handler(nothingEvent);
int main(/*int argc, char* argv[]*/) {
    handler.eve->trigger();
    
}