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
#include "segment_tree.h"

using namespace std;

class sensor {
	string id_;	//El nombre del sensor
	Array <data> v_arr_;	//Un vector con los valores del sensor
	segment_tree s_tree_;
	
public:
	sensor();
	sensor(string id);
	sensor(string id, size_t n);
	sensor( const sensor & S); 
	~sensor( );

	string id() const;		//Devuelve el ID del sensor
	size_t size() const;		//Devuelve la longitud del arreglo values_
	size_t alloc_size() const;
	Array <data> arr() const;
	segment_tree& s_tree();

	sensor&		operator=( const sensor & S); 
	sensor&		operator=( const segment_tree s_tree);
	bool 		operator==( const sensor & S) const; 
	bool 		operator!=( const sensor & S) const; 
	data &		operator[ ]( size_t pos);
	data const &	operator[ ]( size_t pos) const;

	void 		push(const data& new_data);
	void		create_segment_tree();
};

// Constructor por defecto
sensor::sensor()
{
	this->v_arr_ = ARRAY_DEFAULT_SIZE ;
	this->id_="\0";
}

// Constructor a partir del ID
sensor::sensor(string id)
{
	this->v_arr_ = ARRAY_DEFAULT_SIZE;
	this->id_=id;
}
 
// Constructor a partir del ID y la longitud del arreglo
sensor::sensor(string id, size_t n)
{
	Array <data> aux(n);
	this->v_arr_ = aux;
	this->id_=id;
}

// Constructor por puntero
sensor::sensor(const sensor & S)
{	
	this->v_arr_=S.v_arr_;
	this->id_=S.id_;
}

// Destructor
sensor::~sensor()
{
}

// Devuelve el ID del sensor
string
sensor::id() const{
	return this->id_;
}

// Devuelve el tamano del arreglo de valores
size_t
sensor::size() const{
	return this->v_arr_.size();
}

size_t
sensor::alloc_size() const{
	return this->v_arr_.alloc_size();
}

Array <data>
sensor::arr() const{
	return this->v_arr_;
}

segment_tree&
sensor::s_tree(){
	return this->s_tree_;
}

sensor&
sensor::operator=( const sensor & S)
{
	if ( S.id_ == this->id_ && S.v_arr_ == this->v_arr_ && S.s_tree_ == this->s_tree_) 
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

	if (S.s_tree_ != this->s_tree_)
	{
		this->s_tree_=S.s_tree_;
	}

	return *this;

} 


sensor&
sensor::operator=( const segment_tree s_tree){
	if(this->s_tree_ == s_tree){
		return *this;
	}
	else{
		this->s_tree_ = s_tree;
	}
	return *this;
}
 
bool
sensor::operator==( const sensor & S) const{
	if ( this->id_ != S.id_){
		return false;
	} 
	else{
			if (this->v_arr_ != S.v_arr_){
				return false;
			}
			else{
				if(this->s_tree_ != S.s_tree_){
					return false;
				}
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
			else{
				if(this->s_tree_ == S.s_tree_){
					return false;
				}
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


void
sensor::create_segment_tree(){

	segment_tree s_tree_aux(this->v_arr_);
	
	this->s_tree_ = s_tree_aux;
}


#endif