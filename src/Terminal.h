#ifndef TERMINAL_DD_H
#define TERMINAL_DD_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"
#include "InternalPrettyConsoleOut.h"
#include "storage.h"

#include <string>
class Terminal
{
private:
    std::string layout;
    std::string name;
    bool canRun = true;
public:
    static Terminal ptrToInst(Terminal* ptr) {
        Terminal ret(ptr->getName(),ptr->getLayout()); 
        ret.funs = ptr->funs;
        return ret;
    }

    std::vector<std::pair<bool(*)(tokenType,Terminal* /*this*/),std::string>> funs; //pair of the function and the command to execute it

    Terminal(std::string name, std::string layout = ">>>")
        : name(name),layout(layout) {}
    
    std::string getName() const;

    std::string getLayout() const;

    Terminal* addFun(bool(*fun)(tokenType,Terminal*),std::string com);  

    void run();

    void stop();

    static Terminal new_(std::string name, std::string layout = ">>>");

    void operator=(const Terminal& ter);

    void operator=(Terminal* ptr);

    void operator=(std::string name);
    
    static Terminal mainTerminal;

    static Terminal InitMain();
    
};
#endif