#ifndef _SENSORNET_H_INCLUDED_
#define _SENSORNET_H_INCLUDED_

#include <iostream>
#include "sensor.h"
#include "Array.h"
#include <cmath>
using namespace std;

class sensornet {
	Array <sensor> sArray;	//Un vector con los valores del sensor
	
public:
	sensornet();
	sensornet(size_t n);
	sensornet( const sensornet & ); 
	~sensornet();
	sensor &		operator[ ]( size_t pos);
	sensor const &	operator[ ]( size_t pos) const;

	friend istream& read_file(std::istream&,sensornet&);
//	friend std::istream& operator>>(std::istream&,Array<TT>&);

};

sensornet::sensornet()
{
	sArray = 0;
}

sensornet::sensornet(size_t n)
{
	Array <sensor> aux(n);
	sArray = aux;
}

sensornet::sensornet(const sensornet & S)
{
	sArray = S.sArray;
}

sensornet::~sensornet()
{
	sArray.~Array();
}

sensor &
sensornet::operator[ ](size_t pos){
	return sArray[pos];
}


sensor const&
sensornet::operator[ ](size_t pos) const{
	return sArray[pos];
}

istream& read_file(istream &is, sensornet &s)
{
	string str_st;
	string aux;
	string str;
	double aux2;
	size_t i = 0, j = 0;


	getline(is,aux);
	while (aux[j]){
		if(aux[j] == ','){
			s.sArray.push_back(sensor(str));	//se puede hacer esto??
			i=0;
		}
		else{
			str[i] = aux[j];
			i++;
		}
		j++;
	}
	s.sArray.push_back(sensor(str));

	while(getline(is, aux)){
		stringstream str_st(str); 
		if(!(str_st>>s.sArray)){ 
			delete &s;
			cerr<<"Error data read"<<endl;
		}
		//if(!(str_st>>sArray) || str_st==eof){		
//		}
	}
	return is;
}

#endif
