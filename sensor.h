#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "Array.h"
#include "data.h"

using namespace std;

class sensor {
	string id_;	//El nombre del sensor
	Array <data> v_arr_;	//Un vector con los valores del sensor
	
public:
	sensor();
	sensor(string id);
	sensor(string id, size_t n);
	sensor( const sensor & S); 
	~sensor( );

	string id();	//Devuelve el id_ del sensor
	size_t size();		//Devuelve la longitud del arreglo values_

	sensor&		operator=( const sensor & S); 
	bool 		operator==( const sensor & S) const; 
	bool 		operator!=( const sensor & S) const; 
	data &		operator[ ]( size_t pos);
	data const &	operator[ ]( size_t pos) const;
	void 		push(const data& new_data);

};


sensor::sensor()
{
	this->v_arr_ = ARRAY_DEFAULT_SIZE ;
	this->id_='\0';
}

sensor::sensor(string id)
{
	this->v_arr_ = ARRAY_DEFAULT_SIZE;
	this->id_=id;
}
 
sensor::sensor(string id, size_t n)
{
	Array <data> aux(n);
	this->v_arr_ = aux;
	this->id_=id;
}

sensor::sensor(const sensor & S)
{	
	this->v_arr_=S.v_arr_;
	this->id_=S.id_;
}

sensor::~sensor()
{
	
}

string
sensor::id(){
	return this->id_;
}

size_t
sensor::size(){
	return this->v_arr_.size();
}

sensor&
sensor::operator=( const sensor & S)
{
	if ( S.id_ == this->id_ && S.v_arr_==this->v_arr_) 
	{
		return *this;
	}
	// Después, cambiamos el tamaño del arreglo si es necesario y procedemos a copiar
	if(S.id_ != this->id_)
	{
		this->id_=S.id_;
	}

	if (S.v_arr_ != this->v_arr_)
	{
		this->v_arr_=S.v_arr_;
	}

	return *this;

} 

 
bool
sensor::operator==( const sensor & S) const
{
	if ( this->id_ != S.id_)
		return false; 
	else{
			if (this->v_arr_ != S.v_arr_){
				return false;
			}
		}

       	return true;
}
 
bool
sensor::operator!=( const sensor & S) const
{
	if ( this->id_ == S.id_)
		return false; 
	else{
			if (this->v_arr_ == S.v_arr_){
				return false;
			}
		}

       	return true;
}


data &
sensor::operator[ ](size_t pos)
{
	return this->v_arr_[pos];
}


data const &
sensor::operator[ ](size_t pos) const
{
	return this->v_arr_[pos];
}

void 
sensor::push(const data &new_data)
{
	this->v_arr_.push(new_data);
}


#endif