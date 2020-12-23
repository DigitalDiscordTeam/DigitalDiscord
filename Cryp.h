#ifndef CRYP_INTERNAL_H
#define CRYP_INTERNAL_H

#include "InternalDef.h"
#include <string>
#include <stdlib.h>
#include <map>

namespace Cryp {

	MDEF std::map<char, char> caeser1;
	MDEF std::map<char, char> caeser2;

	void fillMaps();

	void xor_crypt(const std::string& key, std::string& data);

	void caeser( std::string& data, bool re = false);

	bool caeserif(const std::string data, const std::string search);
}

#endif
