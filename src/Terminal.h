#ifndef TERMINAL_DD_H
#define TERMINAL_DD_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"
#include "InternalPrettyConsoleOut.h"
#include "storage.h"

#include <string>

class Terminal {
private:
    std::string layout;
    std::string name;
    bool canRun = true;

    
    class TerminalStorage {
        
    public:
        struct Data {
        public:
            std::string string;
            std::string tag;

            Data(std::string string, std::string tag): string(string), tag(tag)
            {};

            Data* getPtr();
        };

        std::string tag;
        std::vector<Data> Datas;

        TerminalStorage* add(std::string str, std::string tag);

        Data get(std::string tag);

        Data get(size_t index);

        TerminalStorage(std::string tag): tag(tag) 
        {}
        TerminalStorage() {}

        MDEF void operator=(std::string tag) {
            this->tag = tag;
        }

        Terminal::TerminalStorage* getPtr();
    };

public:
    std::vector<TerminalStorage> storage;
    using tstorage = Terminal::TerminalStorage;

    static Terminal ptrToInst(Terminal* ptr) {
        Terminal ret(ptr->getName(),ptr->getLayout()); 
        ret.funs = ptr->funs;
        return ret;
    }

    std::vector<std::pair<bool(*)(tokenType,Terminal* /*this*/, TerminalStorage&),std::string>> funs; //pair of the function and the command to execute it

    Terminal(std::string name, std::string layout = ">>>")
        : name(name), layout(layout) 
        {}
    
    std::string getName() const;

    std::string getLayout() const;

    Terminal* addFun(bool(*fun)(tokenType,Terminal*,TerminalStorage&),std::string com);  

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