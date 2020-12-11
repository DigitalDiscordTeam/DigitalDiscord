#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include <stdlib.h>

#include "InternalErrorLogger.h"

namespace StorageSys {
	class c_VOID {
		//void
	};

	template<typename T>
	class SimpleStorage {
	public:
		std::vector<T> interVec;

		SimpleStorage(const std::vector<T>& vec) {
			interVec = vec;
		}

		SimpleStorage() {} //nothing

		size_t find(T value) const;
		T getType() const;
		void clear();

		void operator=(const SimpleStorage<T>&);
		void operator=(const std::vector<T>&);
		operator bool();
		bool operator==(const SimpleStorage<T>&);

	private:

	};

	enum class MultiStorageType {
		STOR1,
		STOR2,
		STOR3,
		STOR4,
		STOR5
	};
	using MST = MultiStorageType;

	template<
			typename Type1,
			typename Type2 = c_VOID, //I used here c_VOID instead of void because
			typename Type3 = c_VOID, //you cant make an vector with void.
			typename Type4 = c_VOID, //But c_VOID is the same as void
			typename Type5 = c_VOID
	>
	class MultiStorage {
	public:
		SimpleStorage<Type1> stor1;
		SimpleStorage<Type2> stor2;
		SimpleStorage<Type3> stor3;
		SimpleStorage<Type4> stor4;
		SimpleStorage<Type5> stor5;

		bool empty(MST type) const;
		bool allSize() const;
	};
}



//defs - SimpleStorage
template<typename T>
size_t StorageSys::SimpleStorage<T>::find(T value) const {
	for(size_t i = 0; i < interVec.size(); ++i) {
		if(interVec[i] == value) {
			return i;
		}
	}
	InternalErrLog::LogMain.append(time(NULL),"VecIsNotStoragingError");
	throw VecIsNotStoragingError;
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

#endif