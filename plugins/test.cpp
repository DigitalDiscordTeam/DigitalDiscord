#include "../src/ExternalPlugins.h"

class myPlugin : public Plugin {
public:
    using Plugin::Plugin;

    int test() {
        return 0;
    }
    void update() override {
        std::cout << test() << "\n";
    }
};
inline myPlugin go;