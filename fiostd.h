#ifndef FIOSTD_H
#define FIOSTD_H


namespace filem {
	std::map<std::ifstream*, std::string> stream_table;

	struct mem {
		std::streamsize len = 0;
		std::string storage = "";
		std::string name = "";
		bool empty = true;

		void clear() {
			len = 0;
			storage = "";
			name = "";
			empty = true;
		}
	};

	void update(mem& memory, std::ifstream& file, std::string filename, std::ios::openmode mode, bool debug = false);

	std::string open(std::ifstream& ifile, mem& memory, std::string file, std::ios_base::openmode mode, bool debug = false) {
		ifile.close();
		ifile.open(file, mode);
		stream_table[&ifile] = file;

		update(memory, ifile, file, mode, debug);

		return file;
	}

	bool close(std::ifstream& ifile, mem& memory) {
		if (!ifile.is_open()){
			return false;	 //file is already closed!
		}

		ifile.close();
		stream_table.erase(&ifile);

		memory.clear();

		return true;		//file closed!
	}

	std::streamsize get_flength(std::ifstream& file) {
		assert(file.is_open());
		std::streampos temp_1 = file.tellg();
		file.seekg(0, std::fstream::end);
		std::streampos temp_2 = file.tellg();
		file.seekg(temp_1, std::fstream::beg);
		
		return temp_2;
	}

	std::streamsize get_flength2(std::string filename) {
		std::ifstream tmp_file;
		tmp_file.open(filename, std::ios::ate);
		return tmp_file.tellg();
	}

	void msure(mem& memory, bool debug = false) { //make sure

		char blacklist[2] = {'\u2550','@'};
		assert(!memory.empty);
		assert(memory.len == memory.storage.length());
		assert(memory.name != "");

		for (size_t i = 0; i < memory.len; ++i) {
			for (size_t j = 0; j < sizeof(blacklist); ++j) {
				if (memory.storage[i] == blacklist[j]) {
					memory.storage.erase(i);
					if (debug) { std::cout << "filem::msure<" << memory.name << "> : erase num " << i << "\n"; }
				}
			}
		}
	}

	void msure(std::vector<std::string>& vec, bool debug = false) {
		assert(vec.size() != 0);
		char blacklist[2] = { '\u2550','@' };

		for (size_t i = 0; i < vec.size(); ++i) {
			for (size_t j = 0; j < vec[i].length(); ++j) {
				for (size_t ij = 0; ij < sizeof(blacklist); ++ij) {
					if (vec[i][j] == blacklist[ij]) {
						vec[i].erase(j);
						if (debug) { std::cout << "filem::msure<vec> : erase num " << i << "," << j << "\n"; }
					}
				}
			}
		}

	}

	void msure(std::string& str, bool debug = false) {
		assert(str.length() != 0);
		char blacklist[2] = { '\u2550','@' };

		for (size_t i = 0; i < str.length(); ++i) {
			for (size_t j = 0; j < sizeof(blacklist); ++j) {
				if (str[i] == blacklist[j]) {
					str.erase(j);
					if (debug) { std::cout << "filem::msure<str> : erase num " << i << "\n"; }
				}
			}
		}
	}

	void update(mem& memory, std::ifstream& file, std::string filename, std::ios::openmode mode, bool debugmode) {
		msure(filename);
		assert(file.is_open());
		//debugmode = true; //--------------------------
		memory.len = get_flength(file);
		if (debugmode) { std::cout << "memoy.len : " << memory.len << " | line : " << __LINE__ << "\n"; }
		assert(memory.len != 0 && memory.len > 0);
		char* buffer = new char[memory.len + 1];
		file.read(buffer, memory.len);
		memory.storage = "";
		buffer += '\0';
		memory.storage.assign(buffer, memory.len);

		memory.name = stream_table[&file];

		delete[] buffer;
		buffer = nullptr;

		memory.empty = false;

		msure(memory);
		

		if (debugmode) { std::cout << "filem::update<" << memory.name << "> : data: | open_mode: " << mode << " | memory.len: " << memory.len << " | memory.storage: \n" << memory.storage << "\nfilem::update<" << memory.name << "> : end of memory.storage!\n"; }
	}

}

#endif
