#include "Terminal.h"

Terminal Terminal::mainTerminal("MainTerminal",">>>");

std::string Terminal::getName() const {
    return name;
}

std::string Terminal::getLayout() const {
    return layout;
}

Terminal* Terminal::addFun(bool(*fun)(tokenType,Terminal*),std::string com) {
    funs.push_back(std::pair<bool(*)(tokenType,Terminal*),std::string>(fun,com));
    return this;
}

void Terminal::run() {
    this->canRun = true;
    TerminalStartEvent::trigger(this);
    bool failed = false;
    std::string tmp;
    while(canRun) {
        std::cout << layout;
        std::getline(std::cin,tmp);
        if(tmp == "" || tmp == "\n") {
            TerminalExitEvent::trigger(this);
            break;
        }
        TerminalInputEvent::trigger(std::pair<std::string,Terminal*>(tmp,this));
        if(tmp == "exit") {
            TerminalExitEvent::trigger(this);
            break;
        }
        tokenType split = InternalFsys::splitTokens(" |",tmp);
        DEBUG_START_
            for(size_t i = 0; i < split.size(); ++i) {
                std::cout << split[i] << "\n";
            }
        DEBUG_END_
        for(size_t i = 0; i < funs.size(); ++i) {
            DEBUG_MESSAGE("keyword:" << funs[i].second << " | " << "split[0]:" << split[0])
            if(split[0] == funs[i].second) {
                failed = funs[i].first(split,this);
            }
        }

        if(failed) {
            TerminalFailEvent::trigger(std::pair<std::string,Terminal*>(tmp,this));
            //throw error and such stuff
        }
    }
}

void Terminal::stop() {
    this->canRun = false;
}

Terminal Terminal::new_(std::string name, std::string layout) {
    return Terminal(name,layout);
}

void Terminal::operator=(const Terminal& ter) {
    this->funs = ter.funs;
    this->name = ter.name;
    this->layout = ter.layout;
}

void Terminal::operator=(Terminal* ptr) {
    operator=(ptrToInst(ptr));
}

void Terminal::operator=(std::string name) {
    this->name = name;
    layout == "" ? ">>>" : layout; //set layout to ">>>" if there is no layout seted
}

Terminal Terminal::InitMain() {
    //add all std commands here
    mainTerminal = Terminal::new_("MainTerminal","<<<>").addFun(
        [](tokenType tokens,Terminal* ptr)->bool{
            if(tokens.size() < 2) {
                return true;
            }
            elif(tokens.size() < 4) {
                if(tokens[2] == ">") {
                    InternalFsys::writeNormal(tokens[3],tokens[1],true);
                }
                else {
                    return true;
                }
            }
            std::cout << tokens[1];
            return false;
        },
        "echo"
    )->addFun(
        [](tokenType tokens, Terminal* ptr)->bool {
            if(tokens.size() > 2) {
                return true;
            }
            std::cout << "name:\t\t" << ptr->getName() << "\nlayout:\t\t" << ptr->getLayout() << "\ncommands:\t\t" << ptr->funs.size() << "\n";
        },
        "whoami"
    );
    return mainTerminal;
}