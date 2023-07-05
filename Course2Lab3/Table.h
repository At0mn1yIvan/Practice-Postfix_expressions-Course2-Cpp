#pragma once
template <typename T1, typename T2>
class Table
{
private:
	T1* Key;
	T2* Value;
	size_t size, curInd;

public:
	Table(size_t _size = 5): size(_size), curInd(0) {
		Key = new T1[size];
		Value = new T2[size];
	}
	Table(const Table& t) :size(t.size), curInd(t.curInd) {
		Key = new T1[size];
		Value = new T2[size];
		for (size_t i = 0; i < size; i++) {
			Key[i] = t.Key[i];
			Value[i] = t.Value[i];
		}
	}

	~Table(){
		delete[] Key;
		delete[] Value;
		Key = nullptr;
		Value = nullptr;
	}
	void Append(const T1& key, const T2& value) {
		if (curInd >= size) {
			return;
		}
		Key[curInd] = key;
		Value[curInd++] = value;
	}

	void Change(const T1& key, const T2& value) {
		for (size_t i = 0; i < size; i++) {
			if (Key[i] == key) {
				Value[i] = value;
				break;
			}
		}
	}

	bool isKeyExist(const T1& key) const {
		for (size_t i = 0; i < size; i++) {
			if (Key[i] == key)
				return true;
		}
		return false;
	}

	T2 maxValue() const {
		T2 tmp = Value[0];
		for (size_t i = 0; i < size; i++) {
			if (Value[i] > tmp)
				tmp = Value[i];
		}
		return tmp;
	}
	

	T2 & operator[](const T1& key){
		for (size_t i = 0; i < curInd; i++) {
			if (Key[i] == key)
				return Value[i];
		}
		throw "Expression not found";
	}

	const T2 & operator[](const T1& key) const {
		for (size_t i = 0; i < curInd; i++) {
			if (Key[i] == key)
				return Value[i];
		}
		throw "Expression not found";
	}

	Table operator=(const Table& t) {
		if (this == &t)
			return *this;
		size = t.size;
		curInd = t.curInd;
		delete[] Key;
		delete[] Value;
		Key = new T1[size];
		Value = new T2[size];
		for (size_t i = 0; i < size; i++) {
			Key[i] = t.Key[i];
			Value[i] = t.Value[i];
		}
		return *this;
	}
};

