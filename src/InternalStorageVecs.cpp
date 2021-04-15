#include "InternalStorageVecs.h"

std::vector<fs::path> InternalFileVec::get(fs::path path) {
	std::vector<fs::path> ret;
	for(auto& file : fs::directory_iterator(path)) {
		if(!file.is_directory()) {
			ret.push_back(file.path());
		}
	}
	return ret;
}

std::vector<fs::path> InternalDirVec::get(fs::path path) {
	std::vector<fs::path> ret;
	for(auto& file : fs::directory_iterator(path)) {
		if(file.is_directory()) {
			ret.push_back(file.path());
		}
	}
	return ret;
}