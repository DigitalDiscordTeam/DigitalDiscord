#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include <stdlib.h>

#include "InternalDef.h"
#include "InternalErrorLogger.h"
//#include <thread>

namespace StorageSys {
	//std::thread::id mainId;

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

template<typename T>
class smartStorage;

template<typename T>
struct smartStorageNode {
	size_t index = 0;
	std::string name;
	std::string id;
	bool ZERO = false;
	T in = false;

	std::vector <smartStorage<T>*> inList;
	~smartStorageNode();
};

template<typename T>
class smartStorage {
	std::vector<smartStorageNode<T>> interVec;
public:
	void append(smartStorageNode<T>& stor);

	void del(smartStorageNode<T>& stor);
	void del(smartStorageNode<T>* stor);
};

#endif