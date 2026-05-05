#pragma once
#include <iostream>

using namespace std;

namespace Vector
{
	template <typename T> class vector {
	private:
		size_t sz;
		T* elem;
		size_t space;
	public:
		vector() : sz{ 0 }, elem{ 0 }, space{ 0 } {}
		vector(size_t s) : sz{ s }, elem{ new T[s] }, space{ s } {}
		
		//big 3
		vector(const vector&);					//vector<int> v2 = v1; //copy constructor
		vector& operator=(const vector&);       //v2 = v1; //copy assignment
		~vector() { delete[] elem; cout << "destructor called" << endl; }

		//access operators at and []
		T& at(size_t n);
		const T& at(size_t n) const;

		T& operator[](size_t n);
		const T& operator[](size_t n) const;

		size_t size() const { return sz; }

		void resize(size_t newsize);
		void push_back(T d);

		void reserve(size_t newalloc); // get more memory, array is growing
		int capacity() const { return space; }

		

	};

	struct out_of_range_ {};

	template <typename T>
	T& vector<T>::at(size_t n) {
		if (n < 0 || n >= sz) {
			throw out_of_range_();
		}
		return elem[n];
	}
	
	template <typename T>
	const T& vector<T>::at(size_t n) const {
		if (n < 0 || n >= sz) {
			throw out_of_range_();
		}
		return elem[n];
	}

	template <typename T>
	T& vector<T>::operator[](size_t n) {
		return elem[n];
	}

	template <typename T>
	const T& vector<T>::operator[](size_t n) const{
		return elem[n];
	}

	//copy constructor
	template<typename T>
	vector<T>::vector(const vector& a) : sz{ a.sz }, elem{ new T[a.sz] }, space{a.sz}
	{
		cout << "Copy constructor called" << endl;
		for (size_t i = 0; i < sz; i++) {
			elem[i] = a.elem[i];
		}
	}

	//copy assignment
	template<typename T>
	vector<T>& vector<T>::operator=(const vector& a) {
		cout << "Copy assignment" << endl;
		if (this == &a) return *this; //if it's a self assignment we're done
		if (a.sz <= space) {// do we have space for a's things
			for (size_t i = 0; i < sz; i++) {
				elem[i] = a.elem[i];
			}
			sz = a.sz;
			return *this;
		}

		// if we got to this point we didnt have enough space. must reallocate--
		T* p = new T[a.sz]; //allocate more memory if not enough space
		for (size_t i = 0; i < a.sz; i++) p[i] = a.elem[i];
		// delete old array from the heap
		delete[] elem;
		sz = a.sz;
		space = a.sz;
		elem = p;
		return *this;
	}
	
	// "get a new house, move all the stuff in, delete the old house
	template<typename T>
	void vector<T>::reserve(size_t newalloc) {
		if (newalloc <= space) return;
		T* p = new T[newalloc];
		for (size_t i = 0; i < sz; i++) {
			p[i] = elem[i];
		}
		delete[] elem;
		elem = p;
		space = newalloc;
	}

	template<typename T>
	void vector<T>::push_back(T d){
		if (space == 0) {
			reserve(8);
		}
		else if (sz == space) {
			reserve(2 * space);
		}
		elem[sz] = d;
		++sz;

	}

	template<typename T>
	void vector<T>::resize(size_t newsize) {
		reserve(newsize);
		for (size_t i = sz; i < newsize; i++) {
			elem[i] = T();
			sz = newsize;
		}

	}

	template<typename T>
	ostream& operator<<(ostream& os, const vector<T>& v){
		for (size_t i = 0; i < v.size(); i++) {
			os << v[i] << " ";
		}
		return os;
	}


}