#ifndef _SENSORNET_H_INCLUDED_
#define _SENSORNET_H_INCLUDED_

#include <iostream>
#include "sensor.h"
#include "Array.h"
#include "segment_tree.h"
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

	friend bool read_file(istream&,sensornet&, Array segment_tree &S_TREE);

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

bool read_file(istream &is,sensornet &s, Array segment_tree &S_TREE){
//	string str_st;
	string str,str2;
	data no_data();
	size_t i = 0, j = 0, k = 0;
	Array <bool> first;
	first[0] = true;
	double val_aux;


	getline(is,str2);
	stringstream str_st(str2);
	while(getline(str_st,str,',')){
		if(str.empty()){
			cout<<"Error Data"<<endl;
			return false;
		}
		sensor s_aux(str);
		if (s.size() == 1 && k == 0){
			s[0] = s_aux;
			k++;
		}
		else{
			s.push(s_aux);
		}
	}
	for (size_t i = 0; i < s.size(); i++)
	{
		first.push(true);
	}
	while(getline(is, str2)){ // str2 se queda con los valores separados por coma
		i=0;
		stringstream str_st(str2);
		while( getline(str_st,str,',')){ // str ahora tiene un valor
			if(s[i].size() == 1 && first[i] == true){ //Evaluamos el caso en que sea el primer elemento del arreglo de datos
				data no_data(0);
				s[i][0] = no_data;					 
				first[i] = false;
			}
			else
				data no_data(j);
				s[i].push(no_data);
			if(!str.empty()){
				for (size_t r = 0; r<str.size(); r++){
					if(!isdigit(str[r]) && str[r]!='.'){
						cout << str[r] << endl;
						cout<<"Error Data"<<endl;
						return false;
					}
				}
				stringstream str_st2(str);
				str_st2 >> val_aux;
				data d_aux(val_aux, j);
				s[i][j] = d_aux;
			}
			i++;
		}
		j++;
	}
	for(i=0; i<s.size(); i++){
		if (s[i].size() != s[i].alloc_size()){
			for(j=s[i].size(); j<s[i].alloc_size(); j++){
				data no_data(j);
				s[i][j].push(no_data);
			}
		}
	}
	for (i=0; i<s.size(); i++){
		segment_tree s_tree_aux(s[i].arr());
		s[i] = s_tree_aux;
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
