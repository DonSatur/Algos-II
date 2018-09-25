#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "data.h"

using namespace std;

// Constructor por defecto
data::data(){
	this->value_ = 0;
	this->state_ = true;
}

// Constructor a partir del valor
data::data(double value){
	this->value_ = value;
	this->state_ = true;
}
	
// Constructor a partir del estado
data::data(bool state){
	this->value_= 0;
	this->state_ = state;
}
	
// Constructor por puntero
data::data( const data & D){
	this->value_ = D.value_;
	this->state_ = D.state_;
}
	

// Destructor
data::~data( ){
}
	
// Devuelve el valor del estado
bool
data::state(){
	return this->state_;
}

// Devuelve el valor de value
double		
data::value(){
	return this->value_;
}


data &
data::operator=( const data & D){
	if (this->value_ == D.value_ && this->state_ == D.state_){
		return *this;
	}
	if (this->value_ != D.value_){
		this->value_ = D.value_;
	}
	if (this->state_ != D.state_){
		this->state_ = D.state_;
	}
	return *this;
}
	

bool
data::operator==( const data & D) const{
	if ( this->value_ != D.value_){
		return false; 
	}
	else{
			if (this->state_ != D.state_){
				return false;
			}
		}

       	return true;

}
	

bool
data::operator!=( const data & D) const{
	if ( this->value_ == D.value_){
		return false; 
	}
	else{
			if (this->state_ == D.state_){
				return false;
			}
		}

       	return true;

}

	
bool
data::operator>( const data & D) const{
	if (this->value_<=D.value_){
		return false;
	}
	return true;
}
	

bool
data::operator>=( const data & D) const{
	if (this->value_<D.value_){
		return false;
	}
	return true;
}


bool
data::operator<( const data & D) const{
	if (this->value_>=D.value_){
		return false;
	}
	return true;
}


bool
data::operator<=( const data & D) const{
	if (this->value_>D.value_){
		return false;
	}
	return true;
}


double
data::operator+( const data & D) const{
	return this->value_+D.value_;
}

// Operador de lectura de una variable data a partir de un flujo de entrada
istream&
operator>>(istream &is, data &D){
	double value_aux;
	is >> value_aux;

	D.value_ = value_aux;
	D.state_ = true;
	return is;

}