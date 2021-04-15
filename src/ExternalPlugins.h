#ifndef EXTERNAL_PLUGINS_H
#define EXTERNAL_PLUGINS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalLib.h"
class Plugin;
namespace PluginL {
    inline std::vector<Plugin*> plugins;
}
class Plugin {
private:
    std::string id;
public:
    //static std::vector<Plugin*> plugins;
    inline const std::string getId() const { return id; }
    virtual void update() {}
    virtual void start() {}
    virtual void reset() {}

    Plugin() {
        PluginL::plugins.push_back(this);
        this->id = InternalLib::makeUUID();
    }
    ~Plugin() {
        for(size_t i = 0; i < PluginL::plugins.size(); ++i) {
            if(PluginL::plugins[i]->getId() == this->id) {
                PluginL::plugins.erase(PluginL::plugins.begin()+i);
                break;
            }
        }
    }

};

namespace ExternalPlugins {

    MDEF void update() {
        for(size_t i = 0; i < PluginL::plugins.size(); ++i) {
            PluginL::plugins[i]->update();
        }
    }

    MDEF void start() {
        //for(size_t i = 0; i < PluginL::plugins.size(); ++i) {
            //PluginL::plugins[i]->start();
        //}
    }

    MDEF void reset() {
        //for(size_t i = 0; i < Plugin::plugins.size(); ++i) {
        //    PluginL::plugins[i]->reset();
        //}
    }
}

#endif