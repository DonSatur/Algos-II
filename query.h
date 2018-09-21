#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "Array.h"
#include "sensornet.h"


using namespace std;

class query {
	Array <data> d_arr_;	//El arreglo que se va a crear con todos los datos que se van a utilizar
	double mean_;
	double max_;
	double min_;
	size_t amount_;

	
public:
	query();
	query(Array <data> d_arr);
	query(Array <data> d_arr, double mean, double max, double min, size_t amount);
	query( const query & Q); 
	~query( );

	double		maximum();
	double		minimum();
	double		mean();
	size_t		amount();

	double		get_max();
	double		get_min();
	double		get_mean();
	size_t		get_amount();

	query&		operator=( const query & Q); 
	bool 		operator==( const query & Q) const; 
	bool 		operator!=( const query & Q) const; 
	data &		operator[ ]( size_t pos);
	data const &	operator[ ]( size_t pos) const;

//	friend
//	bool		readquery(istream & iss, sensornet & S);
//	friend
//	bool		checkdata(sensornet & S, string q_ids, size_t pos1, size_t pos2);

};

query::query(){
	mean_ = 0;
	max_ = 0;
	min_ = 0;
	amount_ = 0;
}

query::query(Array <data> d_arr){
	d_arr_ = d_arr;
	amount_ = d_arr.size();
	max_ = maximum();
	min_ = minimum();
	mean_= mean();
}


query::query(Array <data> d_arr, double mean, double max, double min, size_t amount){
	d_arr_ = d_arr;
	mean_ = mean;
	max_ = max;
	min_ = min;
	amount_ = amount;
}


query::query( const query & Q){
	d_arr_ = Q.d_arr_;
	mean_ = Q.mean_;
	max_ = Q.max_;
	min_ = Q.min_;
	amount_ = Q.amount_;
} 

query::~query( ){

}
	

double
query::maximum(){
	size_t i;
	size_t d_size = d_arr_.size();
	double aux = d_arr_[0].get_value();

	for (i = 1; i < d_size; i++){
		if (d_arr_[i] > aux){
			aux = d_arr_[i].get_value();
		}
	}
	return aux;
}
	

double
query::minimum(){
	size_t i;
	size_t d_size = d_arr_.size();
	double aux = d_arr_[0].get_value();

	for (i = 1; i < d_size; i++){
		if (d_arr_[i] < aux){
			aux = d_arr_[i].get_value();
		}
	}
	return aux;
}


size_t
query::amount(){
	size_t i, aux = 0;
	size_t d_size = d_arr_.size();

	for (i = 0; i < d_size; i++){
		if (d_arr_[i].get_state() == true){
			aux++;
		}
	}
	return aux;
}


double
query::mean(){
	size_t i;
	double aux = 0;
	size_t d_size = d_arr_.size();

	for (i = 0; i < d_size; i++){
		if (d_arr_[i].get_state( )== true){
			aux+=d_arr_[i].get_value();
		}
	}
	return aux/amount_;
}


double
query::get_max(){
	return max_;
}

double
query::get_min(){
	return min_;
}

double
query::get_mean(){
	return mean_;
}
	
size_t
query::get_amount(){
	return amount_;
}


query&
query::operator=( const query & Q ){
	if (d_arr_ == Q. d_arr_ && mean_ == Q.mean_ && max_ == Q.max_ && min_ == Q.min_ && amount_ == Q.amount_){
		return *this;
	}
	if(d_arr_ != Q.d_arr_){
		d_arr_ = Q.d_arr_;
	}
	if(mean_ != Q.mean_){
		mean_ = Q.mean_;
	}
	if(max_ != Q.max_){
		max_ = Q.max_;
	}
	if(min_ != Q.min_){
		min_ = Q.min_;
	}
	if(amount_ != Q.amount_){
		amount_ = Q.amount_;
	}
	return *this;
} 
	

bool
query::operator==( const query & Q) const{
	if(d_arr_ != Q.d_arr_){
			return false;
	}
	else{
		if(mean_ != Q.mean_){
			return false;
		}
		else{
			if(max_ != Q.max_){
				return false;
			}
			else{
				if(min_ != Q.min_){
					return false;
				}
				else{
					if(amount_ != Q.amount_){
						return false;
					}
				}
			}
		}
	}
	return true;
} 



bool
query::operator!=( const query & Q) const{
	if(d_arr_ == Q.d_arr_){
			return false;
	}
	else{
		if(mean_ == Q.mean_){
			return false;
		}
		else{
			if(max_ == Q.max_){
				return false;
			}
			else{
				if(min_ == Q.min_){
					return false;
				}
				else{
					if(amount_ == Q.amount_){
						return false;
					}
				}
			}
		}
	}
	return true;
} 

	
data &
query::operator[ ]( size_t pos){
	return d_arr_[pos];
}


data const &
query::operator[ ]( size_t pos) const{
	return d_arr_[pos];
}



//	friend
//	bool		readquery(istream & iss, sensornet & S);
//	friend
//	bool		checkdata(sensornet & S, string q_ids, size_t pos1, size_t pos2);

#endif