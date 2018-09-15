#ifndef _SENSORNET_H_INCLUDED_
#define _SENSORNET_H_INCLUDED_

#include <iostream>
#include "sensor.h"
using namespace std

class sensornet {
	Array <sensor> sensors;	//Un vector con los valores del sensor
	
public:
	sensornet();
	sensornet(size_t n);
	sensornet( const sensornet & ); 
	~sensornet( );
//	sensor&	operator=( const sensornet & ); 
//	bool 		operator==( const sensornet & ) const; 
//	bool 		operator!=( const sensornet & ) const; 
	sensornet &		operator[ ]( int );
	sensornet const &	operator[ ]( int ) const;

	double	mean(&sensornet,string,int, int) const;	//Hace el promedio entre la posicion int y la posicion int
	double	max(&sensornet,string,int, int) const;	//Hace el maximo entre la posicion int y la posicion int
	double	min(&sensornet,string,int, int) const;	//Hace el minimo entre la posicion int y la posicion int
	double	subsize(&sensornet,string,int, int) const;	//Calcula la cantidad de valores que se usaron para las operaciones anteriores

	friend std::istream& read_file(std::istream&,sensornet&);

};



#endif