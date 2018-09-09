#include <templatearray.h>
#include <iostream>
#include <cmath>

using namespace std;


//Constructor por defecto
template<typename T>
tArr<T>::tArr(int size =1)
{
	this->cap=size;
	this->nrelem=0;
	this/>arr=new T*[this->cap];
} 


//Destructor
template<typename T>
tArr<T>::~tArr()
{
	for int i = 0, i < this->nrelem, i+
		delete this->arr[i];
	delete[] this->arr;

}


//Construcor por referencia
template<typename T>
tArr<T>::tArr(const tArr& obj)
{
	this->cap=obj.cap;
	this->nrelem=obj.nrelem;
	this/>arr=new T*[this->cap];

	for int i =0, i<this->nrelem, i++	//Copia la data desde obj
		this->arr[i]=new T(*obj.arr[i]);

	initialize(0);

}


//Devuelve el valor de la posicion index de arr
template<typename T>
tArr<T>::operator[](const int index)
{
	if index<0 || index >= this->nrelem
		throw("OUT OF BOUND");

	return *this->arr[index]:
}


// Inicializacion del arreglo
template<typename T>
void tArr<T>::initialize(int from)
{
	for int i = from, i < this->cap, i++
		this->arr[i]=nullptr:

}


// 
template<typename T>
void tArr<T>::expand()
{
	this->cap += 1;
	T **tempArr = new T*(this->cap);

	for int i = 0, i < this->nrelem, i++
		tempArr[i] = this->arr[i];

	delete[]this->arr;

	this->arr = tempArr;

	initialize(this->nrelem);
}