#ifndef EXTERNAL_PLUGINS_H
#define EXTERNAL_PLUGINS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalFsys.h"
#include "InternalSys.h"
#include "InternalPrettyConsoleOut.h"
#include "Terminal.h"
#include "Cryp.h"

namespace ExternalPlugins {

    MDEF void update() {
        //add includes here
        #include "../plugins/testPlugin.h"
    }

    MDEF void start() {
        //add includes here
        
    }

    MDEF void reset() {
        //add includes here
        #include "../plugins/testPlugin.h"
    }
}

#endif