#include "Cryp.h"

void Cryp::fillMaps() {
	for (size_t i = 'A'; i < 'z'; ++i) { //no letters like "!,$,),..."!
		caeser1[i] = i > 'o' ? 'z' - i : i + ('z' - 'o');
	}

	for (size_t i = 'A'; i < 'z'; ++i) {
		caeser2[caeser1[i]] = i;
	}
}

void Cryp::xor_crypt(const std::string& key, std::string& data) {
	for (size_t i = 0; i != data.size(); i++)
		data[i] ^= key[i % key.size()];
}

void Cryp::caeser( std::string& data, bool re) {
	if (Cryp::caeser1.empty()) {
		fillMaps();
	}
	const std::string constTemp = data;
	for (size_t i = 0; i < constTemp.length(); ++i) {
		if (!re) { data[i] = caeser1[constTemp[i]]; }
		else { data[i] = caeser2[constTemp[i]]; }
	}
}

bool Cryp::caeserif(const std::string data, const std::string search) {
	std::string data1 = data;
	std::string data2 = search;
	Cryp::caeser(data1);
	Cryp::caeser(data2);
	Cryp::caeser(data2,true);
	if (data1 == data2) {
		return true;
	}
	else {
		return false;
	}
}