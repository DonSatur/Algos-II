#ifndef _SENSORNET_H_INCLUDED_
#define _SENSORNET_H_INCLUDED_

#include <iostream>
#include "sensor.h"
#include "array.h"
#include <cmath>

using namespace std;

class sensornet {
	array <sensor> s_arr_;	//Un vector con los valores del sensor
	
public:
	sensornet();
	sensornet(size_t n);
	sensornet( const sensornet & ); 
	~sensornet();

	size_t size();

	sensor &		operator[ ]( size_t pos);
	sensor const &	operator[ ]( size_t pos) const;

//	friend istream& read_file(std::istream&,sensornet&);
//	friend std::istream& operator>>(std::istream&,Array<TT>&);

};

sensornet::sensornet()
{
	this->s_arr_ = 0;
}

sensornet::sensornet(size_t n)
{
	array <sensor> aux(n);
	this->s_arr_ = aux;
}

sensornet::sensornet(const sensornet & S)
{
	this->s_arr_ = S.s_arr_;
}

sensornet::~sensornet()
{
}

size_t
sensornet::size(){
	return this->s_arr_.size();
}

sensor &
sensornet::operator[ ](size_t pos){
	return this->s_arr_[pos];
}


sensor const&
sensornet::operator[ ](size_t pos) const{
	return this->s_arr_[pos];
}

//istream& read_file(istream &is, sensornet &s)
//{
//	string str_st;
//	string aux;
//	string str;
//	double aux2;
//	size_t i = 0, j = 0;
//
//
//	getline(is,aux);
//	while (aux[j]){
//		if(aux[j] == ','){
//			s.sArray.push_back(sensor(str));	//se puede hacer esto??
//			i=0;
//		}
//		else{
//			str[i] = aux[j];
//			i++;
//		}
//		j++;
//	}
//	s.sArray.push_back(sensor(str));
//
//	while(getline(is, aux)){
//		i=0;
//		stringstream str_st(str); 
//		if(!(str_st>>s.sArray[i].values)){ 
//			delete &s;
//			cerr<<"Error data read"<<endl;
//		}
//		//if(!(str_st>>sArray) || str_st==eof){		
//		}
//	}
//	return is;
//}

#endif
