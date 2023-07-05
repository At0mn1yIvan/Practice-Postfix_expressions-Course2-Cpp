#pragma once
#include <iostream>
#define DEFAULTSIZE 10;

template <typename T>
class TStack
{
private:
	T* data;
	size_t size;
	size_t top;
	bool isEmpty;
	void resize() {
		T* newData = new T[size * 2];
		std::copy(data, data + size, newData);
		size *= 2;
		delete[] data;
		data = newData;
	}
public:


	TStack(size_t _size = 0) : size(_size), isEmpty(true), top(0) {
		if (size == 0)
			size = DEFAULTSIZE;
		data = new T[size];
		if (data == nullptr)
			throw "No memory";
	}

	TStack(const TStack& s): size(s.size), top(s.top), isEmpty(s.isEmpty) {
		data = new T[size];
		for (size_t i = 0; i < size; i++) {
			data[i] = s.data[i];
		}
	}

	//Перемещающий конструктор
	TStack(TStack&& s): size(s.size), top(s.top), isEmpty(s.isEmpty), data(nullptr) {
		data = s.data;
		s.data = nullptr;
		s.size = 0;
		s.top = 0;
		s.isEmpty = true;
		
	}

	void Push(const T& obj){
		if (top + 1 == size) {
			resize();
		}
		if (!isEmpty) {
			top++;
		}
		data[top] = obj;
		isEmpty = false;
	}

	bool CheckEmpty() {
		return isEmpty;
	}

	T Pop() {
		if (isEmpty) throw "Stack is empty";
		if (top == 0) {
			isEmpty = true;
			return data[top];
		}
		else{
			return data[top--];
		}
	}

	T Top(){
		if (isEmpty) throw "Stack is empty";
		return data[top];
	
	}

	~TStack(){
		delete[] data;
		data = nullptr;
	}
};	

