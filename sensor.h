#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "Array.h"

using namespace std;

class sensor {
	string ID;	//El nombre del sensor
	Array <double> values;	//Un vector con los valores del sensor
	
public:
	sensor();
	sensor(string a);
	sensor(string a, size_t n);
	sensor( const sensor & S); 
	~sensor( );
	sensor&		operator=( const sensor & S); 
	bool 		operator==( const sensor & S) const; 
	bool 		operator!=( const sensor & S) const; 
	double &		operator[ ]( int pos);
	double const &	operator[ ]( int pos) const;

};


sensor::sensor()
{
	values=0;
	ID='\0';
}

sensor::sensor(string a)
{
	values=0;
	ID=a;
}
 
sensor::sensor(string a, size_t n)
{
	Array <double> aux(n);
	values = aux;
	ID=a;
}

sensor::sensor(const sensor & S)
{	
	values=S.values;
	ID=S.ID;
}

sensor::~sensor()
{
	values.~Array();
}

sensor&
sensor::operator=( const sensor & S)
{
	if ( S.ID == this->ID && S.values==this->values) 
	{
		return *this;
	}
	// Después, cambiamos el tamaño del arreglo si es necesario y procedemos a copiar
	if(S.ID != this->ID)
	{
		ID=S.ID;
	}

	if (S.values != this->values)
	{
		values=S.values;
	}

	return *this;

} 

 
bool
sensor::operator==( const sensor & S) const
{
	if ( ID != S.ID)
		return false; 
	else{
			if (values != S.values){
				return false;
			}
		}

       	return true;
}
 
bool
sensor::operator!=( const sensor & S) const
{
	if ( ID == S.ID)
		return false; 
	else{
			if (values == S.values){
				return false;
			}
		}

       	return true;
}


double &
sensor::operator[ ](int pos)
{
	return this->values[pos];
}


double const &
sensor::operator[ ](int pos) const
{
	return this->values[pos];
}


#endif
