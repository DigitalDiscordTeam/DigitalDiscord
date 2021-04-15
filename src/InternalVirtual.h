#ifndef INTERNAL_VIRTUAL_H_
#define INTERNAL_VIRTUAL_H_

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalFsys.h"

namespace InternalVirtual {
    namespace Storage {
        class Dir;
        struct File;
    }

    void rmDir(Storage::Dir* dir);

    namespace Storage {
        class Dir {
            static size_t count;
            size_t id;
        public:
            Dir(std::string name, Dir* topDir): name(name), topDir(topDir) { ++count; id=count;}
            Dir(std::string name): name(name) { topDir = this; ++count; id=count;} //root directory
            std::string name;
            Dir* topDir;
            std::vector<Dir*> bottomDirs;
            std::vector<File*> files;

            size_t getId() const;

            ~Dir();

            bool hasMember(const Dir* dir);
            bool hasMember(File* file);

            Dir* append(Dir* dir);
            Dir* append(File* file);

        };
        struct File {
        private:
            static size_t count;
            size_t id;
        public:
            size_t getId() const;

            std::string name;
            Dir* HomeDir;

            std::string value;

            File(std::string name, Dir* HomeDir): name(name), HomeDir(HomeDir) {HomeDir->files.push_back(this); ++count; id=count;}
            File(std::string name, std::string value, Dir* HomeDir): name(name), HomeDir(HomeDir), value(value) { HomeDir->files.push_back(this); ++count; id=count;}

            ~File();
        };
        
    }

    Storage::Dir* createFile(Storage::File* file, Storage::Dir* dir);

    std::string getDirPathsAsString(Storage::Dir* dir);

    Storage::Dir* getHomeDir(Storage::Dir* dir);

    struct Path {
        Storage::Dir* root;
        Storage::Dir* end;
        Storage::File* endFile = nullptr;

        Path(Storage::Dir* root, Storage::Dir* end): root(root) {
            if(root->hasMember(end)) {
                throw NoMatchingVirtualPathError{};
                InternalErrLog::LogMain.append(time(NULL),NoMatchingVirtualPathError{}.toString());
            }
            this->end = end;
        }
        Path(Storage::Dir* root, Storage::Dir* end, Storage::File* file): root(root) {
            if(!root->hasMember(end) || !end->hasMember(file)) {
                throw NoMatchingVirtualPathError{};
                InternalErrLog::LogMain.append(time(NULL),NoMatchingVirtualPathError{}.toString());
            }
            endFile = file;
            this->end = end;
        }

        void setFile(Storage::File* file);
        Path* push_back(Storage::Dir* dir);
    };

    void saveDir(const Storage::Dir* dir);
    void readIn(Storage::Dir* dir, std::string name);
} 


#endif