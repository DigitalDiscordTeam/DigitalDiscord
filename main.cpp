#include "InternalDef.h"
#include "Memory.h"
#include "InternalPrettyConsoleOut.h"

int main(/*int argc, char* argv[]*/) {
	InternalPCO::HubChoice myCH1([](void) {
		std::cout << "success!!!\n";
	},"myCH1","100x010001x01001001000");
	InternalPCO::HubChoice myCH2([](void) {
		std::cout << "success2!!!\n";
	},"myCH2","100x010001x01001001000");

	InternalPCO::Hub OwnHub("OwnHub",{myCH1,myCH2});

	OwnHub.show();

}