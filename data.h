#ifndef _DNFO_H_DNCLUDED_
#define _DNFO_H_DNCLUDED_

#include <iostream>
#include "Array.h"
#include <cmath>

using namespace std;

class data{
	size_t min_;
	size_t max_;
	size_t sum_;
	size_t amount_;
	Array size_t pos_;		// El arreglo es creciente
	bool state_;			// Si state es false, quiere decir que no se senso en ese instante


public:
	data();
	data(Array <size_t> pos);
	data(size_t min, size_t max, size_t sum, size_t amount, size_t Array pos);
	data (double value, size_t pos );
	data (data D1, data D2);
	data( const data & D);
	~data();

	double			calc_max (data D1, data D2);	// El primer objeto debe estar ubicado en una posicion
	double			calc_min (data D1, data D2);	// menor al segundo
	double			calc_sum (data D1, data D2);
	Array size_t	calc_pos (data D1, data D2);
	size_t			calc_amount (data D1, data D2);			

	data &		operator=( const data & D); 
};


// Constructor por defecto
data::data(){
	this->min_ = HUGE_VAL * (-1);
	this->max_ = HUGE_VAL;
	this->sum_ = 0;
	this->amount_ = 0;
	this->pos_[0] = 0;
	this->pos_[1] = 0;
	this->state_ = false;
}


data::data(Array <size_t> pos){
	this->min_ = HUGE_VAL * (-1);
	this->max_ = HUGE_VAL;
	this->sum_ = 0;
	this->amount_ = 0;
	this->pos_[0] = pos[0];
	this->pos_[1] = pos[1];
	this->state_ = false;
}


// Constructor por copia
data::data(size_t min, size_t max, size_t sum, size_t amount, size_t Array pos){
	this->min_ = min;
	this->max_ = max;
	this->sum_ = sum;
	this->amount_ = amount;
	this->pos_[0] = pos[0];
	this->pos_[1] = pos[1];
	this->state_ = true;
}


// Constructor a partir de un objeto data
data::data(double value, size_t pos){
	this->min_ = value;
	this->max_ = value;
	this->sum_ = value;
	this->amount_ = 1;
	this->pos_[0] = pos;
	this->pos_[1] = pos+1;
	this->state_ = true;
}


// Constructor a partir de dos objetos data
data::data(data D1, data D2){
	this->min_ = calc_min(D1,D2);
	this->max_ = calc_max(D1,D2);
	this->sum_ = calc_sum(D1,D2);
	this->amount_ = calc_amount(D1);
	this->pos_ = calc_pos(D1,D2);
	this->state_ = true;
}


// Constructor por puntero
data::data(const data & D)
{	
	this->min_ = D.min_;
	this->max_ = D.max_;
	this->sum_ = D.sum_;
	this->amount_ = D.amount_;
	this->pos_[0] = D.pos_[0];
	this->pos_[1] = D.pos_[1];
}


// Destructor
data::~data()
{
}


// Calculo del valor maximo
double
data::calc_max (data D1, data D2){
	if (D1.max_ > D2.max_){
		this->max_ = D1.max_;
	}
	else{
		this->max_ = D2.max_;
	}
}


// Calculo del valor minimo
double
data::calc_min (data D1, data D2){
	if (D1.min_ < D2.min_){
		this->min_ = D1.min_;
	}
	else{
		this->min_ = D2.min_;
	}
}


// Suma de los valores de dos objetos data
double
data::calc_sum (data D1, data D2){
	this->sum_= D1.sum_ + D2.sum_;
}


// Calculo de las posiciones asociadas al objeto data
Array size_t
data::calc_pos (data D1, data D2){
	this->pos[0] = D1.pos[0];
	this->pos[1] = D2.pos[1];
}

size_t
data::calc_amount(data D1, data D2){
	this->amount_ = D1.amount_ + D2.amount_;
}


data &
data::operator=( const data & D){
	if (this->min_ == D.min_ && this->max_ == D.max_ && this->sum_ == D.sum_ && this->amount_ == D.amount_ && this->state_ == D.state_){
		return *this;
	}
	if (this->min_ != D.min_){
		this->min_ = D.min_;
	}
	if (this->max_ != D.max_){
		this->max_ = D.max_;
	}
	if (this->sum_ != D.sum_){
		this->sum_ = D.sum_;
	}
	if (this->amount_ != D.amount_){
		this->amount_ = D.amount_;
	}
	if (this->state_ != D.state_){
		this->state_ = D.state_;
	}
	return *this;
}


#endif