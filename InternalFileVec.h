#ifndef INTERNAL_FILE_VEC_H
#define INTERNAL_FILE_VEC_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalSys.h"
#include "InternalErrors.h"

#include <experimental/filesystem>
#include <stdlib.h>
#include <string>
#include <vector>

namespace InternalFileVec {
	std::vector<std::pair<filesystemPath, std::string>> fileVec; // path : filename
	filesystemPath lastPath;

	void update(const filesystemPath path) {
		lastPath = path;
		std::string ret;
		for (const auto& entry : fs::directory_iterator(path))
			fileVec.push_back(std::pair<fs::v1::path,std::string>(Setup::wstring2string(entry.path()), Setup::wstring2string(entry.path().filename())));
	}

	enum class getType { PATHTYPE, FILENAMETYPE };
	using gT = getType;
	filesystemPath get(std::string value, gT type) {
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
		throw VecIsNotStoragingError;
	}

	filesystemPath get(size_t index, gT type) {
		if (type == gT::PATHTYPE) {
			return fileVec[index].first;
		}
		else {
			return fileVec[index].second;
		}
	}
}

#endif