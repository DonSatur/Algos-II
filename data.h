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

	bool		get_state();
	double		get_value();

	data &		operator=( const data & D); 
	bool 		operator==( const data & D) const; 
	bool 		operator!=( const data & D) const; 
	bool		operator>( const data & D) const;
	bool		operator>=( const data & D) const;
	bool		operator<( const data & D) const;
	bool		operator<=( const data & D) const;

};

#endif
