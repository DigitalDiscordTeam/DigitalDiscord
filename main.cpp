#include "InternalDef.h"
#include "CommandFile.h"


int main() {
	Events::Event tmpEvent("tmpEvent", "tmpE");
	//InternalFsys::FEvents::writeIdInEventFile("test2.txt", tmpEvent.id);
	Setup::checkIfPaths();
	//std::cout << InternalFsys::readNormal("test.txt") << "\n";
	CommandFile cF("test3.txt", "test3.txt");
	
	cF.run();
	system("pause");
}