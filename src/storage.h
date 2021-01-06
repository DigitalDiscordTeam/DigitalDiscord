#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include <stdlib.h>

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalLib.h"
#include <thread>

namespace StorageSys {
	MDEF std::thread::id mainId;
	using InternalLib::c_VOID;
	

	template<typename T>
	class SimpleStorage {
	public:
		std::vector<T> interVec;

		SimpleStorage(const std::vector<T>& vec) {
			interVec = vec;
		}

		SimpleStorage() {} //nothing

		MDEF size_t find(T value) const {
			for(size_t i = 0; i < interVec.size(); ++i) {
				if(interVec[i] == value) {
					return i;
				}
			}
			InternalErrLog::LogMain.append(time(NULL),"VecIsNotStoragingError");
			throw VecIsNotStoragingError{};
			return 0;
		}

		MDEF T getType() const {
			return dynamic_cast<T>(1);
		}

		void clear() {
			interVec.clear();
		}

		void operator=(const std::vector<T>& vec) {
			this->interVec = vec;
		}

		void operator=(const SimpleStorage<T>& stor) {
			this->interVec = stor.interVec;
		}

		operator bool() {
			return interVec.empty();
		}

		bool operator==(const SimpleStorage<T>& stor) {
			return stor.interVec == this->interVec;
		}

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

		MDEF bool empty(MST type) const {
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

		bool allSize() const {
			return 
			stor1.interVec.size() + 
			stor2.interVec.size() + 
			stor3.interVec.size() + 
			stor4.interVec.size() + 
			stor5.interVec.size();
		}
	};

	template<typename T>
	class SmartStorage;

	template<typename T>
	struct SmartStorageNode {
		size_t index = 0;
		std::string name;
		std::string id;
		bool ZERO = false;
		T in;

		SmartStorageNode() {}
		SmartStorageNode(T value) {
			this->in = value;
		}

		std::vector <SmartStorage<T>*> inList;

		~SmartStorageNode() {
			for(size_t i = 0; i < inList.size(); ++i) {
				inList[i]->del(this);
			}
		}
	};

	template<typename T>
	class SmartStorage {
		std::vector<SmartStorageNode<T>> interVec;
	public:
		SmartStorage() {}

		void append(SmartStorageNode<T>& stor) {
			stor.id = std::to_string(time(NULL) % rand());
			stor.name = "Stor" + std::to_string(interVec.size());

			if(interVec.empty()) {
				interVec.push_back(stor);
				stor.inList.push_back(this);
				return;
			}
			for(size_t i = 0; i < interVec.size(); ++i) {
				DEBUG_MESSAGE("for loop of StorageSys::SmartStorage::append, i:" << i << "ZERO:" << interVec[i].ZERO)
				if(interVec[i].ZERO) {
					interVec[i] = stor;
					stor.index = i;
					for(size_t j = 0; j < interVec.size(); ++j) {
						interVec[j].index = j; //refresh index
					}
					break;
				}
				
			}
			if(stor.index == 0 && interVec[0].id != stor.id) {
				interVec.push_back(stor);
				stor.index = interVec.size()-1;
			}
			
			stor.inList.push_back(this);
		}

		void del(SmartStorageNode<T>& stor) {
			interVec[stor.index].ZERO = true;
			stor.ZERO = true;
		}

		void del(SmartStorageNode<T>* stor) {
			interVec[stor->index].ZERO = true;
			stor->ZERO = true;
		}
	};

	class LimitedStorage {
		int val;
	public:
		int max;
		int min;

		int get() const {
			return val;
		}

		void operator=(int val) {
			if(val >= min && val <= max) {
				this->val = val;
			}
			else {
				throw InvaildInputError{};
			}
		}

		bool operator==(int val) {
			return (this->val == val);
		}

#undef max
#undef min

		LimitedStorage(int min, int max, int val) : max(max), min(min), val(val <= max && val >= min ? val:0) {
			
		}
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
	};
}

#endif