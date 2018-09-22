#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "data.h"

using namespace std;

data::data(){
	this->value_ = 0;
	this->state_ = true;
}


data::data(double value){
	this->value_ = value;
	this->state_ = true;
}
	

data::data(bool state){
	this->value_= 0;
	this->state_ = state;
}
	

data::data( const data & D){
	this->value_ = D.value_;
	this->state_ = D.state_;
}
	

data::~data( ){
}
	

bool
data::state(){
	return this->state_;
}


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
