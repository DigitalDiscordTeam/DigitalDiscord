#ifndef GAME_CHARS_H
#define GAME_CHARS_H
//game-characters

#include "InternalFsys.h"
#include "InternalPrettyConsoleOut.h"
#include "Memory.h"
#include "InternalLib.h"
#include "storage.h"

#include <iostream>
#include <string>

namespace Chars {
    ///
    /// how to use this namespace:
    ///
    /// when you use this namespace in a function or class, do this:
    /// - using namespace <namespace-part>
    ///
    /// why?
    /// if you do this, you dont need to type very::long::shit::you::dont::need
    ///

    int globalInitSleeptime = 300;
    
    namespace Custom {
        InternalPCO::SlowPrintc ikarus_SP;
        InternalPCO::SlowPrintc sys_SP;
        InternalPCO::SlowPrintc rand_SP;
    }
    namespace Sayas{
        void sys(std::string message, std::string ext = "") {
            std::cout << "[SYSTEM] "; std::cout.flush();
            Custom::sys_SP << message;
            std::cout << ext; //print something without slowPrint (for example: \n)
        }
        void ikarus(std::string message, std::string ext = "") {
            std::cout << "[Ikarus] "; std::cout.flush();
		    Custom::ikarus_SP << message;
            std::cout << ext;
        }
        void random(std::string message, long length, std::string ext = "") {
            std::cout << "[";
            InternalPCO::corruptedLine(length);
            std::cout << "] ";
            Custom::rand_SP << message;
            std::cout << ext;

        }
    }

    namespace Special {
        namespace Ikarus {
            namespace Memory {
                
                std::map<std::string, int> IkarusOwnMap; //Ikarus is a name so you write it big
                StorageSys::MultiStorage<int,char,std::string,float,uint32_t> IkarusStor;

                bool IkarusRememberMap(Events::Event Event) {
                    return IkarusOwnMap[Event.id] == 0 ? false : true;
                }

                void mapUpdate() {
                    IkarusOwnMap = InternalEventMap::EventMap;
                }
            }

            namespace Do {
                auto say = Sayas::ikarus; //sorry, bu i cant add the default value for ext here...


            }
        }

        namespace Player2 {
            //later ;)
        }
    }

    void init(int customTime = globalInitSleeptime) {
        Custom::ikarus_SP = customTime;
        Custom::ikarus_SP = customTime;
        Custom::rand_SP = customTime;
    }
}

#endif