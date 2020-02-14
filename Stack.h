/* Copyright 2018 Margineanu Nicolae-Vladut */

#ifndef STACK_H__
#define STACK_H__

template <typename T, int N>
class Stack {
 private:
	int topLevel;  // capul stivei
	int defaultCapacity = N;
	int expandFactor = 40;

	int maxCapacity;
	T *data;

 public:
	// Constructor
	Stack(){
		topLevel = 0;
		maxCapacity = defaultCapacity;

		data = new T[maxCapacity];
	}

	// Alt constructor
    explicit Stack(int initialCapacity) {
		topLevel = 0;
		maxCapacity = initialCapacity;
		data = new T[maxCapacity];
	}

    // Copy-constructor
    // Stiva mea nu trebuie sa copieze o alta stiva
     Stack(const Stack &object) {}

    // Destructorul
	~Stack() {
		if (!this->isEmpty()) {
			delete[] data;
		}
	}

	// Copy-assignement
	// Stiva mea nu trebuie sa i se atribuie unei alte stive
	Stack& operator=(const Stack& obj) {}

    // adaugam un element in capul stivei
	void push(T element) {
		if (topLevel == maxCapacity) {
			maxCapacity *= expandFactor;
			T *aux = new T[maxCapacity];
			for (int i = 0; i < topLevel; i++) {
				aux[i] = data[i];
			}
			delete[] data;
			data = aux;
		}

		data[topLevel++] = element;
	}

	// sterge capul stivei
	void pop(){
		if(!this->isEmpty()){
			topLevel--;
		}
	}

    // returneaza capul stivei
	T& peek(){
		return data[topLevel-1];
	}

	bool isEmpty(){
		return (!topLevel) ? true : false;
	}

	int size(){
		return topLevel;
	}
};
#endif  // STACK_H__
