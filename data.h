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
	bool state_;

	
public:
	data();
	data(double value);
	data(bool state);
	data( const data & D); 
	~data( );

	bool		state();	//Devuelve el valor de state_
	double		value();	//Devuelve el valor de value_

	data &		operator=( const data & D); 
	bool 		operator==( const data & D) const; 
	bool 		operator!=( const data & D) const; 
	bool		operator>( const data & D) const;
	bool		operator>=( const data & D) const;
	bool		operator<( const data & D) const;
	bool		operator<=( const data & D) const;
	double		operator+( const data & D) const;
	friend istream& operator>>(istream &, data &new_data);

};

#endif