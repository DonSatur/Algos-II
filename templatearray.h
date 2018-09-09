#ifndef _TEMPLATEARRAY_H_INCLUDED_
#define _TEMPLATEARRAY_H_INCLUDED_

#include <iostream>


template<typename T>

class tArr
{
	int cap;	//Capacidad maxima
	int nrelem;	//Numero de elementos totales
	T **arr;	//Arreglo
public:
	tArr(int size = 1);
	~tArr();
	tArr(const tArr& obj);

	T& operator[] (const int index);

	void initialize(int from);
	void expand();
	void push(const T& obj);
	void pop(int index);
	
}

