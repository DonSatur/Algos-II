#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "data.h"

using namespace std;

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
	

bool
data::get_state(){
	return state_;
}


double		
data::get_value(){
	return value_;
}


data &
data::operator=( const data & D){
	if (value_ == D.value_ && state_ == D.state_){
		return *this;
	}
	if (value_ != D.value_){
		value_ = D.value_;
	}
	if (state_ != D.state_){
		state_ = D.state_;
	}
	return *this;
}
	

bool
data::operator==( const data & D) const{
	if ( value_ != D.value_){
		return false; 
	}
	else{
			if (state_ != D.state_){
				return false;
			}
		}

       	return true;

}
	

bool
data::operator!=( const data & D) const{
	if ( value_ == D.value_){
		return false; 
	}
	else{
			if (state_ == D.state_){
				return false;
			}
		}

       	return true;

}

	
bool
data::operator>( const data & D) const{
	if (value_<=D.value_){
		return false;
	}
	return true;
}
	

bool
data::operator>=( const data & D) const{
	if (value_<D.value_){
		return false;
	}
	return true;
}


bool
data::operator<( const data & D) const{
	if (value_>=D.value_){
		return false;
	}
	return true;
}


bool
data::operator<=( const data & D) const{
	if (value_>D.value_){
		return false;
	}
	return true;
}
