#ifndef _DNFO_H_DNCLUDED_
#define _DNFO_H_DNCLUDED_

#include <iostream>
#include "Array.h"
#include <climits>
#include <cmath>
#include <cfloat>

using namespace std;

class data{
	double min_ = DBL_MAX;
	double max_ = DBL_MAX * (-1);
	double sum_ = 0;
	size_t amount_ = 0;
	size_t pos1_ = 0;
	size_t pos2_ = 0;
	bool state_ = false;			// Si state es false, quiere decir que no se senso en ese instante


public:
	data();
	data(size_t pos);
	data(size_t min, size_t max, size_t sum, size_t amount, size_t pos1, size_t pos2);
	data (double value, size_t pos);
	data (data & D1, data & D2);
	data( const data & D);
	~data();

	double			calc_max (data &D1, data &D2);	// El primer objeto debe estar ubicado en una posicion
	double			calc_min (data &D1, data &D2);	// menor al segundo
	double			calc_sum (data &D1, data &D2);
	size_t			calc_pos1 (data &D1, data &D2);
	size_t			calc_pos2 (data &D1, data &D2);
	size_t			calc_amount (data &D1, data &D2);	
	bool			calc_state(data &D1, data &D2);		

	double 			max() const;
	double			min() const;
	double			sum() const;
	size_t			amount() const;
	size_t			pos1() const;
	size_t			pos2() const;
	bool			state() const;


	data &		operator=( const data & D); 
	bool		operator==( const data & D);
	bool		operator!=( const data & D);
};


// Constructor por defecto
data::data(){
}


data::data(size_t pos){
	this->min_ = DBL_MAX;
	this->max_ = DBL_MAX * (-1);
	this->sum_ = 0;
	this->amount_ = 0;
	this->pos1_ = pos;
	this->pos2_ = pos+1;
	this->state_ = false;
}


// Constructor por copia
data::data(size_t min, size_t max, size_t sum, size_t amount, size_t pos1, size_t pos2){
	this->min_ = min;
	this->max_ = max;
	this->sum_ = sum;
	this->amount_ = amount;
	this->pos1_ = pos1;
	this->pos2_ = pos2;
	this->state_ = true;
}


// Constructor a partir de un objeto data
data::data(double value, size_t pos){
	this->min_ = value;
	this->max_ = value;
	this->sum_ = value;
	this->amount_ = 1;
	this->pos1_ = pos;
	this->pos2_ = pos+1;
	this->state_ = true;
}


// Constructor a partir de dos objetos data
data::data(data & D1, data & D2){
	this->min_ = calc_min(D1,D2);
	this->max_ = calc_max(D1,D2);
	this->sum_ = calc_sum(D1,D2);
	this->amount_ = calc_amount(D1,D2);
	this->pos1_ = calc_pos1(D1,D2);
	this->pos2_ = calc_pos2(D1,D2);
	this->state_ = calc_state(D1,D2);
}


// Constructor por puntero
data::data(const data & D)
{	
	this->min_ = D.min_;
	this->max_ = D.max_;
	this->sum_ = D.sum_;
	this->amount_ = D.amount_;
	this->pos1_ = D.pos1_;
	this->pos2_ = D.pos2_;
}


// Destructor
data::~data()
{
}


// Calculo del valor maximo
double
data::calc_max (data &D1, data &D2){
	if (D1.max_ > D2.max_){
		this->max_ = D1.max_;
	}
	else{
		this->max_ = D2.max_;
	}
	return this->max_;
}


// Calculo del valor minimo
double
data::calc_min (data &D1, data &D2){
	if (D1.min_ < D2.min_){
		this->min_ = D1.min_;
	}
	else{
		this->min_ = D2.min_;
	}
	return this->min_;
}


// Suma de los valores de dos objetos data
double
data::calc_sum (data &D1, data &D2){
	return this->sum_ = D1.sum_ + D2.sum_;
}


size_t
data::calc_pos1 (data &D1, data &D2){
	if(D1.pos1_ == 0 && D1.pos2_ == 0){
		this->pos1_ = D2.pos1_;
	}
	else if(D2.pos1_ == 0 && D2.pos2_ == 0){
		this->pos1_ = D1.pos1_;
	}
	else{
		this->pos1_ = D1.pos1_;
	}	
	return this->pos1_;
}


size_t
data::calc_pos2 (data &D1, data &D2){
	if(D1.pos1_ == 0 && D1.pos2_ == 0){
		this->pos2_ = D2.pos2_;
	}
	else if(D2.pos1_ == 0 && D2.pos2_ == 0){
		this->pos2_ = D1.pos2_;
	}
	else{
		this->pos2_ = D2.pos2_;
	}	
	return this->pos2_;
}

size_t
data::calc_amount(data &D1, data &D2){
	return this->amount_ = D1.amount_ + D2.amount_;
}


bool
data::calc_state(data &D1, data &D2){
	if(D1.state_ == true){
		return true;
	}
	else{
		return D2.state_;
	}
}


double 			
data::max() const{
	return this->max_;
}
	
double			
data::min() const{
	return this->min_;
}
	
double			
data::sum() const{
	return this->sum_;
}
	
size_t			
data::amount() const{
	return this->amount_;
}
	
size_t
data::pos1() const{
	return this->pos1_;
}

size_t
data::pos2() const{
	return this->pos2_;
}

bool
data::state() const{
	return this->state_;
}


data &
data::operator=( const data & D){
	if (this->min_ == D.min_ && this->max_ == D.max_ && this->sum_ == D.sum_ && this->amount_ == D.amount_ && this->state_ == D.state_ && this->pos1_ == D.pos1_ && this->pos2_ == D.pos2_){
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
	if (this->pos1_ != D.pos1_){
		this->pos1_ = D.pos1_;
	}
	if (this->pos2_ != D.pos2_){
		this->pos2_ = D.pos2_;
	}
	return *this;
}


bool
data::operator==( const data & D){
	if(this->min_ != D.min_){
		return false;
	}
	else{
		if(this->max_ != D.max_){
			return false;
		}
		else{
			if(this->sum_ != D.sum_){
				return false;
			}
			else{
				if(this->amount_ != D.amount_){
					return false;
				}
				else{
					if(this->state_ != D.state_){
						return false;
					}
					else{
						if(this->pos1_ != D.pos1_){
							return false;
						}
						else{
							if(this->pos2_ != D.pos2_){
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}


bool
data::operator!=( const data & D){
	if(this->min_ == D.min_){
		return false;
	}
	else{
		if(this->max_ == D.max_){
			return false;
		}
		else{
			if(this->sum_ == D.sum_){
				return false;
			}
			else{
				if(this->amount_ == D.amount_){
					return false;
				}
				else{
					if(this->state_ == D.state_){
						return false;
					}
					else{
						if(this->pos1_ == D.pos1_){
							return false;
						}
						else{
							if(this->pos2_ == D.pos2_){
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}

#endif