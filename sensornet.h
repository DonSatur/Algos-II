#ifndef _SENSORNET_H_INCLUDED_
#define _SENSORNET_H_INCLUDED_

#include <iostream>
#include "sensor.h"
#include "Array.h"
#include <cmath>

using namespace std;

class sensornet {
	Array <sensor> s_arr_;	//Un vector con los valores del sensor
	
public:
	sensornet();
	sensornet(size_t n);
	sensornet( const sensornet & ); 
	~sensornet();

	size_t size();

	sensor &		operator[ ]( size_t pos);
	sensor const &	operator[ ]( size_t pos) const;

	friend bool read_file(istream&,sensornet&);
//	friend std::istream& operator>>(std::istream&,Array<TT>&);

};

sensornet::sensornet()
{
	this->s_arr_ = 0;
}

sensornet::sensornet(size_t n)
{
	Array <sensor> aux(n);
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

bool read_file(istream &is, sensornet &s){
	string str_st;
	string str,str2;
	data no_data(false);
	size_t i = 0, j = 0;


	getline(is,str2);
	while (str2[j]){
		if(str2[j] == ','){
			s.s_arr_.push(sensor(str));	//se puede hacer esto??
			i=0;
		}
		else{
			str[i] = str2[j];
			i++;
		}
		j++;
	}
	s.s_arr_.push(sensor(str));
	j=0;
	while(getline(is, str2)){
		i=0;
		stringstream str_st(str2);
		while( getline(str_st,str2,',')){
			if(!str2.empty())
				stringstream str_st2(str2);
				
				str_st >> s[i][j];
				if(s[i][j].state() == false){
					cout<<"Bad data"<<endl;
					return false;
				}
			}
			i++;
		}
		j++;
	}
	return true;
}

#endif
