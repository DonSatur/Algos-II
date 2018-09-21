#ifndef _DATA_H_INCLUDED_
#define _DATA_H_INCLUDED_

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

class data {
	
	double value_;
	bool state_;		//Si state es true, hay un valor; si state es false, no hay valor.


data::data(){
	value_ = 0;
	state_ = true;
}


data::data(double value){
	value_ = value;
	state_ = true;
}
	

data::data(bool state){
	value_= 0;
	state_ = state;
}
	

data::data( const data & D){
	value_ = D.value_;
	state_ = D.state_;
}
	

data::~data( ){
}
	

data &
data::operator=( const data & D){
	if (value_ == D.value && state_ == D.state){
		return *this;
	}
	if (value_ != D.value){
		value_ = D.value;
	}
	if (state_ != D.state){
		state_ = D.state;
	}
	return *this;
}
	

bool
data::operator==( const data & D) const{
	if ( value_ != D.value){
		return false; 
	}
	else{
			if (state_ != D.state){
				return false;
			}
		}

       	return true;

}
	

bool
data::operator!=( const data & D) const{
	if ( value_ == D.value){
		return false; 
	}
	else{
			if (state_ == D.state){
				return false;
			}
		}

       	return true;

}

