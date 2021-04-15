#include "InternalVirtual.h"
size_t InternalVirtual::Storage::Dir::count = 0;
size_t InternalVirtual::Storage::File::count = 0;

void InternalVirtual::rmDir(InternalVirtual::Storage::Dir* dir) {
    dir->~Dir();
    delete dir;
    dir = nullptr;
}

size_t InternalVirtual::Storage::Dir::getId() const {
    return id;
}
size_t InternalVirtual::Storage::File::getId() const {
    return id;
}

InternalVirtual::Storage::Dir* InternalVirtual::createFile(Storage::File* file, Storage::Dir* dir) {
    for(size_t i = 0; i < dir->files.size(); ++i) {
        if(dir->files[i]->name == file->name) {

        }
    }
    file->HomeDir = dir;
    dir->files.push_back(file);
    return dir;
}

bool hasMember_helpFun_Dir(const InternalVirtual::Storage::Dir* dir, const InternalVirtual::Storage::Dir* toFind) {
    for(size_t i = 0; i < dir->bottomDirs.size(); ++i) {
        DEBUG_MESSAGE("call hasMember_helpFun_Dir() with " << dir->name << " and " << toFind->name << "  (ids:" << dir->getId() << "|" << toFind->getId() << ")")
        if(hasMember_helpFun_Dir(dir->bottomDirs[i],toFind)) {
            DEBUG_MESSAGE("returned true! (" << dir->getId() << "|" << toFind->getId() << ")")
            return true;
        }
    }
    DEBUG_MESSAGE("check " << dir->getId() << " with " << toFind->getId())
    return dir->getId() == toFind->getId();
}
bool InternalVirtual::Storage::Dir::hasMember(const Dir* dir) {
    return hasMember_helpFun_Dir(this,dir);
}

bool hasMember_helpFun_File(InternalVirtual::Storage::Dir* dir, const InternalVirtual::Storage::File* toFind) {
    for(size_t i = 0; i < dir->bottomDirs.size(); ++i) {
        hasMember_helpFun_File(dir,toFind);
    }
    for(size_t i = 0; i < dir->files.size(); ++i) {
        if(dir->files[i]->getId() == toFind->getId()) {
            return true;
        }
    }
    return false;
}
bool InternalVirtual::Storage::Dir::hasMember(File* file) {
    return hasMember_helpFun_File(this,file);
}

void getDirPathsAsString_RecusionFun(InternalVirtual::Storage::Dir* dir, std::string& str, const InternalVirtual::Storage::Dir* root) {
    for(size_t i = 0; i < dir->bottomDirs.size(); ++i) {
        DEBUG_MESSAGE("called recursion fun in detDirPathsAsString_RecursionFun with " << dir->bottomDirs[i]->name << "!")
        getDirPathsAsString_RecusionFun(dir->bottomDirs[i],str,root);
    }
    std::vector<std::string> tmpStrs;
    for(InternalVirtual::Storage::Dir* ldir = dir;; ldir = ldir->topDir) {
        DEBUG_MESSAGE("loop of getDirPathsAsString_RecursionFun is now at " << ldir->name);
        if(ldir == root) {
            str += root->name + "/";
            DEBUG_MESSAGE("ldir is the root! (name:" << ldir->name << ")")
            for(size_t i = 0; i < tmpStrs.size(); ++i) {
                str += tmpStrs[i] + "/";
                DEBUG_MESSAGE("add \"" << tmpStrs[i] << "\" to the dir list")
            }
            str += "\n";
            std::string tmp;
            for(size_t i = 0; i < tmpStrs.size(); ++i) {
                tmp += tmpStrs[i] + "/";
                DEBUG_MESSAGE("add " << tmpStrs[i] << "/ to tmp")
            }
            DEBUG_MESSAGE("tmp is now: " << tmp)
            for(size_t i = 0; i < dir->files.size(); ++i) {
                str += root->name + "/" + tmp + dir->files[i]->name + "\n";
                DEBUG_MESSAGE("add \"" << tmp << dir->files[i]->name << "\" to str")
            }
            DEBUG_MESSAGE("finished!")
            tmp = "";
            break;
        }
        
        tmpStrs.push_back(ldir->name);
        DEBUG_MESSAGE("pushed " << ldir->name << " back in tmpStrs (size:" << tmpStrs.size() << ")")

    }
    
    DEBUG_MESSAGE("function \"getDirPathsAsString_RecursionFun\" returnd!")
}

std::string InternalVirtual::getDirPathsAsString(InternalVirtual::Storage::Dir* dir) {
    std::string str;
    DEBUG_MESSAGE("start getDirPathAsString with " << dir->name)
    for(size_t i = 0; i < dir->bottomDirs.size(); ++i) {
        getDirPathsAsString_RecusionFun(dir->bottomDirs[i],str,dir);
    }
    str += dir->name + "/\n";
    return str; 
}

InternalVirtual::Storage::Dir* InternalVirtual::getHomeDir(InternalVirtual::Storage::Dir* dir) {
    InternalVirtual::Storage::Dir* hdir;
    for(Storage::Dir* dirp = dir; ;) {
        dirp = dirp->topDir;
        DEBUG_MESSAGE("loop in getHomeDir(): " << dir->topDir->getId() << " == " << dirp->getId() << " ?")
        if(dirp->topDir->getId() == dirp->getId()) {
            DEBUG_MESSAGE("Found! \"" << dirp->name << "\" is the root!")
            hdir = dirp;
            break;
        }
    }
    return hdir;
}

InternalVirtual::Storage::Dir::~Dir() { //TODO: fix segauft
    for(size_t i = 0; i < bottomDirs.size(); ++i) {
        bottomDirs[i]->~Dir();
        delete bottomDirs[i];
        bottomDirs[i] = nullptr;
    }
    for(size_t i = 0; i < files.size(); ++i) {
        files[i]->~File();
    }
}

InternalVirtual::Storage::File::~File() {
    for(size_t i = 0; i < HomeDir->files.size(); ++i) {
        if(HomeDir->files[i]->getId() == this->getId()) {
            HomeDir->files[i] = nullptr;
        }
    }
}

InternalVirtual::Path* InternalVirtual::Path::push_back(Storage::Dir* dir) {
    if(!this->end->hasMember(dir)) {
        throw NoMatchingVirtualPathError{};
        InternalErrLog::LogMain.append(time(NULL),NoMatchingVirtualPathError{}.toString());
    }
    else {
        end = dir;
    }
    return this;
}
void InternalVirtual::Path::setFile(Storage::File* file) {
    if(!this->end->hasMember(file)) {
        throw NoMatchingVirtualPathError{};
        InternalErrLog::LogMain.append(time(NULL),NoMatchingVirtualPathError{}.toString());
    }
    else {
        file = file;
    }
}

InternalVirtual::Storage::Dir* InternalVirtual::Storage::Dir::append(Dir* dir) {
    this->bottomDirs.push_back(dir);
    dir->topDir = this;

    return this;
}

InternalVirtual::Storage::Dir* InternalVirtual::Storage::Dir::append(File* file) {
    this->files.push_back(file);
    file->HomeDir->topDir = this;

    return this;    
}

void InternalVirtual::saveDir(const Storage::Dir* dir) {
    InternalFsys::sys::makeDir("InternalVirtual" ST + dir->name);
    for(size_t i = 0; i < dir->files.size(); ++i) {
        InternalFsys::sys::makeFile(dir->files[i]->name,System::pathtoDir,dir->files[i]->value);
    }
    for(size_t i = 0; i < dir->bottomDirs.size(); ++i) {
        saveDir(dir);
    }
}

void InternalVirtual::readIn(Storage::Dir* dir, std::string name) {
    auto dirs = InternalDirVec::get(System::pathtoDir + name);
    auto files = InternalFileVec::get(System::pathtoDir + name);
    for(size_t i = 0; i < dirs.size(); ++i) {
        dir->append(new InternalVirtual::Storage::Dir(dirs[i].string()));
    }
    for(size_t i = 0; i < files.size(); ++i) {
        dir->files.push_back(new InternalVirtual::Storage::File(files[i].string(),InternalFsys::readNormal(files[i].root_path().string()),dir));
    }
    for(size_t i = 0; i < dirs.size(); ++i) {
        readIn(dir,name + ST + dir[i].name);
    }
}