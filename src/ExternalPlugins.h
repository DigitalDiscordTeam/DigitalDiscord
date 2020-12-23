#ifndef EXTERNAL_PLUGINS_H
#define EXTERNAL_PLUGINS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalFsys.h"
#include "InternalSys.h"
#include "InternalPrettyConsoleOut.h"

namespace ExternalPlugins {

    MDEF void inline update() {
        //add includes here
        #include "..\plugins\testPlugin.h"
    }

    MDEF void inline start() {
        //add includes here
        #include "..\plugins\testPlugin.h"
    }

    MDEF void inline reset() {
        //add includes here
        #include "..\plugins\testPlugin.h"
    }
}

#endif