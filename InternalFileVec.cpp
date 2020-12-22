#include "InternalFileVec.h"

void InternalFileVec::update(const filesystemPath path) {
	lastPath = path;
	std::string ret;
	for (const auto& entry : fs::directory_iterator(path))
		fileVec.push_back(std::pair<filesystemPath,std::string>(System::wstring2string(entry.path()), System::wstring2string(entry.path().filename())));
}

filesystemPath InternalFileVec::get(std::string value, gT type) {
	if (type == gT::FILENAMETYPE) {
		for (size_t i = 0; i < fileVec.size(); ++i) {
			if (fileVec[i].second == value) {
				return fileVec[i].first;
			}
		}
	}
	else {
		for (size_t i = 0; i < fileVec.size(); ++i) {
    		if (fileVec[i].first == value) {
				return fileVec[i].second;
			}
		}
	}
	throw VecIsNotStoragingError{};
}

filesystemPath InternalFileVec::get(size_t index, gT type) {
	if (type == gT::PATHTYPE) {
		return fileVec[index].first;
	}
	else {
		return fileVec[index].second;
	}
}