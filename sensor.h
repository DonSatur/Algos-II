#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <iostream>
#include "Array.h"
using namespace std

class sensor {
	string ID;	//El nombre del sensor
	Array <double> values;	//Un vector con los valores del sensor
	
public:
	sensor();
	sensor(size_t n);
	sensor(string a);
	sensor(string a, size_t n);
	sensor( const sensor & ); 
	~sensor( );
	sensor&		operator=( const sensor & ); 
	bool 		operator==( const sensor & ) const; 
	bool 		operator!=( const sensor & ) const; 
	sensor &		operator[ ]( int );
	sensor const &	operator[ ]( int ) const;

	double	mean(&sensor,int, int) const;	//Hace el promedio entre la posicion int y la posicion int
	double	max(&sensor,int, int) const;	//Hace el maximo entre la posicion int y la posicion int
	double	min(&sensor,int, int) const;	//Hace el minimo entre la posicion int y la posicion int
	double	subsize(&sensor,int, int) const;	//Calcula la cantidad de valores que se usaron para las operaciones anteriores

	//friend std::istream& operator>>(std::istream&,sensor&);

};



#endif
