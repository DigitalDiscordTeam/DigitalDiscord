#include "storage.h"

//defs - SimpleStorage
template<typename T>
size_t StorageSys::SimpleStorage<T>::find(T value) const {
	for(size_t i = 0; i < interVec.size(); ++i) {
		if(interVec[i] == value) {
			return i;
		}
	}
	InternalErrLog::LogMain.append(time(NULL),"VecIsNotStoragingError");
	throw VecIsNotStoragingError{};
	return 0;
}

template<typename T>
T StorageSys::SimpleStorage<T>::getType() const {
	return dynamic_cast<T>(1);
}

template<typename T>
void StorageSys::SimpleStorage<T>::clear() {
	interVec.clear();
}

template<typename T>
StorageSys::SimpleStorage<T>::operator bool() {
	return interVec.empty();
}

template<typename T>
void StorageSys::SimpleStorage<T>::operator=(const SimpleStorage<T>& stor) {
	this->interVec = stor.interVec;
}

template<typename T>
void StorageSys::SimpleStorage<T>::operator=(const std::vector<T>& vec) {
	this->interVec = vec;
}


//defs - SimpleStorage
template<typename T1, typename T2, typename T3, typename T4, typename T5>
bool StorageSys::MultiStorage<T1,T2,T3,T4,T5>::empty(MST type) const {
	if(type == MST::STOR1) {
		return stor1.empty();
	}
	else if(type == MST::STOR2) {
		return stor2.empty();
	}
	else if(type == MST::STOR3) {
		return stor3.empty();
	}
	else if(type == MST::STOR4) {
		return stor4.empty();
	}
	else if(type == MST::STOR5) {
		return stor5.empty();
	}
	else {
		return true;
	}
}

template<typename T1, typename T2, typename T3, typename T4, typename T5>
bool StorageSys::MultiStorage<T1,T2,T3,T4,T5>::allSize() const {
	return 
	stor1.interVec.size() + 
	stor2.interVec.size() + 
	stor3.interVec.size() + 
	stor4.interVec.size() + 
	stor5.interVec.size();
}


//defs switchManager
void switchManager::append(switchManagerStor& stor) {
	M_ASSERT(!stor.in);
	if(stor.in) {
		return;
	}
	stor.id = std::to_string(time(NULL) & rand());
	stor.name = "Stor" + std::to_string(interVec.size());
	for(size_t i = 0; i < interVec.size(); ++i) {
		if(interVec[i].ZERO) {
			interVec[i] = stor;
			stor.index = i;
			stor.in = true;
			for(size_t j = 0; j < interVec.size(); ++j) {
				interVec[j].index = j; //refresh index
			}
		}
	}
	if(!stor.in) {
		stor.index = interVec.size() +1;
		interVec.push_back(stor);
		stor.in = true;
	}
	stor.inList.push_back(this);
}

void switchManager::del(switchManagerStor& stor) {
	M_ASSERT(stor.in);
	if(!stor.in) {
		return;
	}
	interVec[stor.index].ZERO = true;
	stor.in = false;
}

void switchManager::del(switchManagerStor* stor) {
	M_ASSERT(stor->in);
	if(!stor->in) {
		return;
	}
	interVec[stor->index].ZERO = true;
	stor->in = false;
}


//defs switchManagerStor
switchManagerStor::~switchManagerStor() {
	for(size_t i = 0; i < inList.size(); ++i) {
		inList[i]->del(this);
	}
}