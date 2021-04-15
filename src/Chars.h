#ifndef GAME_CHARS_H
#define GAME_CHARS_H
//game-characters

#include "InternalDef.h"
#include "InternalFsys.h"
#include "Memory.h"
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
    /// if you do this, you wont have to type very::long::shit::you::dont::need
    ///

    MDEF int globalInitSleeptime = 300;
    
    namespace Custom {
        MDEF InternalPCO::SlowPrintc ikarus_SP;
        MDEF InternalPCO::SlowPrintc sys_SP;
        MDEF InternalPCO::SlowPrintc rand_SP;
    }
    namespace Sayas{
        void sys(std::string message, std::string ext = "");

        void ikarus(std::string message, std::string ext = "");

        void random(std::string message, long length, std::string ext = "");
    }

    namespace Special {
        namespace Ikarus {
            namespace IMemory {
                MDEF StorageSys::MultiStorage<int,char,std::string,float,uint32_t> IkarusStor;

                MDEF StorageSys::LimitedStorage PowerCernal(0,5,0); //between 1 and 5 (0 = off)
            }

            namespace Do {
                void say(std::string message, std::string ext = "");
            }
        }

        namespace Player2 {
            //later ;)
        }

        namespace sys {

        }
    }

    void init(int customTime = globalInitSleeptime);
}

#endif