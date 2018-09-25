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

	void push(const sensor &new_sensor);

};

sensornet::sensornet()
{
	this->s_arr_ = ARRAY_DEFAULT_SIZE;
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
//	string str_st;
	string str,str2;
	data no_data(false);
	size_t i = 0, j = 0, k = 0;
	Array <bool> first;
	first[0] = true;


	getline(is,str2);
	stringstream str_st(str2);
	while(getline(str_st,str,',')){
		if(str.empty()){
			cout<<"Error Data"<<endl;
		}
		sensor s_aux(str);
		if (s.size() == 1 && k == 0){
			s[0] = s_aux;
			k++;
		}
		else{
			s.push(s_aux);
		}
	//	cout<<str<<endl;
	}
	for (size_t i = 0; i < s.size(); i++)
	{
		first.push(true);
	}
	while(getline(is, str2)){ // str2 se queda con los valores separados por coma
		i=0;
		stringstream str_st(str2);
		while( getline(str_st,str,',')){ // str ahora tiene un valor
			//cout<<str<<',';
			if(s[i].size() == 1 && first[i] == true){ //Evaluamos el caso en que sea el primer elemento del arreglo de datos
				s[i][0] = no_data;					 //Ya que push 
				first[i] = false;
			//	cout<<"i es "<<i<<endl;
			}
			else
				s[i].push(no_data);
			if(!str.empty()){
				stringstream str_st2(str);
				str_st2 >> s[i][j];
			}
			cout<<s[i][j].value()<<',';
			i++;
		}
		cout<<endl;
		j++;
	}
	return true;
}

void 
sensornet::push(const sensor &new_sensor)
{
	sensor S(new_sensor);
	this->s_arr_.push(S);
}


#endif