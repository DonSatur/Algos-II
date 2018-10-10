#ifndef _INFO_H_INCLUDED_
#define _INFO_H_INCLUDED_

#include <iostream>
#include "data.h"
#include "Array.h"
#include <cmath>

using namespace std;

class info{
	size_t min_;
	size_t max_;
	size_t sum_;
	size_t amount_;
	Array size_t pos_;		// El arreglo es creciente


public:
	info();
	info(size_t min, size_t max, size_t sum, size_t amount, size_t Array pos);
	info (data D, size_t data_pos);
	info (info I1, info I2);
	info( const info & I);
	~info();

	double			calc_max (info I1, info I2);	// El primer objeto debe estar ubicado en una posicion
	double			calc_min (info I1, info I2);	// menor al segundo
	double			calc_sum (info I1, info I2);
	Array size_t	calc_pos (info I1, info I2);
	size_t			calc_amount (info I1, info I2);			

};


// Constructor por defecto
info::info(){
	this->min_ = HUGE_VAL * (-1);
	this->max_ = HUGE_VAL;
	this->sum_ = 0;
	this->amount_ = 0;
	this->pos_[0] = 0;
	this->pos_[1] = 0;
}


// Constructor por copia
info::info(size_t min, size_t max, size_t sum, size_t amount, size_t Array pos){
	this->min_ = min;
	this->max_ = max;
	this->sum_ = sum;
	this->amount_ = amount;
	this->pos_[0] = pos[0];
	this->pos_[1] = pos[1];
}


// Constructor a partir de un objeto data
info::info(data D, size_t data_pos){
	if(D.state() == false){
		this->min_ = HUGE_VAL * (-1);
		this->max_ = HUGE_VAL;
		this->sum_ = 0;
		this->amount_ = 0;
	}
	else{
		this->min_ = D.value();
		this->max_ = D.value();
		this->sum_ = D.value();
		this->amount_ = 1;
	}

	this->pos_[0] = pos;
	this->pos_[1] = pos+1;
}


// Constructor a partir de dos objetos info
info::info(info I1, info I2){
	this->min_ = calc_min(I1,I2);
	this->max_ = calc_max(I1,I2);
	this->sum_ = calc_sum(I1,I2);
	this->amount_ = calc_amount(I1);
	this->pos_ = calc_pos(I1,I2);
}


// Constructor por puntero
info::info(const info & I)
{	
	this->min_ = I.min_;
	this->max_ = I.max_;
	this->sum_ = I.sum_;
	this->amount_ = I.amount_;
	this->pos_[0] = I.pos_[0];
	this->pos_[1] = I.pos_[1];
}


// Destructor
info::~info()
{
}


// Calculo del valor maximo
double
info::calc_max (info I1, info I2){
	if (I1.max_ > I2.max_){
		this->max_ = I1.max_;
	}
	else{
		this->max_ = I2.max_;
	}
}


// Calculo del valor minimo
double
info::calc_min (info I1, info I2){
	if (I1.min_ < I2.min_){
		this->min_ = I1.min_;
	}
	else{
		this->min_ = I2.min_;
	}
}


// Suma de los valores de dos objetos info
double
info::calc_sum (info I1, info I2){
	this->sum_= I1.sum_ + I2.sum_;
}


// Calculo de las posiciones asociadas al objeto info
Array size_t
info::calc_pos (info I1, info I2){
	this->pos[0] = I1.pos[0];
	this->pos[1] = I2.pos[1];
}

size_t
info::calc_amount(info I1, info I2){
	if(I1.amount_ == 0){
		this->amount_= 2 * I2.amount_;
	}
	else{
		this->amount_ = 2 * I1.amount_;
	}
}

#endif