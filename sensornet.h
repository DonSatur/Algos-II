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
	bool stree_mode_;
	
public:
	sensornet();
	sensornet(bool stree_mode);
	sensornet(size_t n);
	sensornet( const sensornet & ); 
	~sensornet();

	size_t size();
	bool stree_mode();

	sensor &		operator[ ]( size_t pos);
	sensor const &	operator[ ]( size_t pos) const;

	friend bool read_file(istream&,sensornet&);

	void push(const sensor &new_sensor);

};

sensornet::sensornet()
{
	this->s_arr_ = ARRAY_DEFAULT_SIZE;
	this->stree_mode_ = false;
}

sensornet::sensornet(bool stree_mode)
{
	this->s_arr_ = ARRAY_DEFAULT_SIZE;
	this->stree_mode_ = stree_mode;
}

sensornet::sensornet(size_t n)
{
	Array <sensor> aux(n);
	this->s_arr_ = aux;
	this->stree_mode_ = false;
}

sensornet::sensornet(const sensornet & S)
{
	this->s_arr_ = S.s_arr_;
	this->stree_mode_ = S.stree_mode_;
}

sensornet::~sensornet()
{
}

size_t
sensornet::size(){
	return this->s_arr_.size();
}

bool
sensornet::stree_mode(){
	return this->stree_mode_;
}

sensor &
sensornet::operator[ ](size_t pos){
	return this->s_arr_[pos];
}


sensor const&
sensornet::operator[ ](size_t pos) const{
	return this->s_arr_[pos];
}

bool read_file(istream &is,sensornet &s){

	string str,str2;
	size_t i, m, j = 0;
	Array <bool> first;
	first[0] = true;
	double val_aux;
	bool k = true;
	sensor all_sensors("All sensors");

	getline(is,str2);
	stringstream str_st(str2);
	while(getline(str_st,str,',')){
		if(str.empty()){
			cout<<"BAD DATA"<<endl;
			return false;
		}
		if(str[str.size()-1] == '\r'){
			stringstream st_aux(str); // ESTA SOLUCION ES ALGO QUE PUSE DESPUES DE CANSARME DE PROBAR IGUALANDO EL ULTIMO CARACTER A \0
			getline(st_aux,str,'\r');
		}
		sensor s_aux(str);
		if (s.size() == 1 && k){
			s[0] = s_aux;
			k = false;
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
		if(str2[str2.size()-1] == '\r'){
			stringstream st_aux(str2); // ESTA SOLUCION ES ALGO QUE PUSE DESPUES DE CANSARME DE PROBAR IGUALANDO EL ULTIMO CARACTER A \0
			getline(st_aux,str2,'\r');
		}
		m=0;
		i=0;
		stringstream str_st(str2);
		while( getline(str_st,str,',')){ // str ahora tiene un valor
			m++;
			if(m>s.size()){
				cout << "BAD DATA" << endl;
				return false;
			}
			if(s[i].size() == 1 && first[i] == true){ //Evaluamos el caso en que sea el primer elemento del arreglo de datos
				data no_data(0);
				s[i][0] = no_data;					 
				first[i] = false;
			}
			else{
				data no_data(j);
				s[i].push(no_data);
			}
			if(!str.empty()){
				for (size_t r = 0; r<str.size(); r++){
					if(str[0] == '.'){
						cout<<"BAD DATA"<<endl;
						return false;
					}
					if(!isdigit(str[r]) && str[r] != '.'){
						cout<<"BAD DATA"<<endl;
						return false;
					}
					if(str[r] == '.' && !isdigit(str[r+1])){
						cout << "BAD DATA" <<endl;
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
		if(str.empty()){ 
			m++;
			data no_data(j);
			s[i].push(no_data);
		}
		j++;

		if(m != s.size()){
			cout << "BAD DATA" << endl;
			return false;
		}
	}
	for(i=0; i<s.size(); i++){
		if (s[i].size() != s[i].alloc_size()){
			for(j=s[i].size(); j<s[i].alloc_size(); j++){
				data no_data(j);
				s[i][j] = no_data;
			}
		}
	}

	for (i = 0 ; i<s.size()-1; i++){
		if(s[i].size() != s[i+1].size()){
			cout<<5;
			cout<<"BAD DATA"<<endl;
			return false;
		}
	}
	m = s[i].size();
	s.push(all_sensors);
	for(j = 0; j<m; j++){  // En este for j es el tiempo
		 data data_aux(0);
		for (i = 0 ; i<s.size()-1; i++){ // En este for i es el indice del i-esimo sensor
			data d_aux(data_aux,s[i][j]); 
			data_aux = d_aux;
		}
		val_aux = data_aux.sum()/data_aux.amount();
		data d_aux(val_aux,j);
		if (s[s.size()-1].size() == 1 && j == 0){
			s[s.size()-1][0] = d_aux;
		}
		else{
			s[s.size()-1].push(d_aux);
		}
	}
	if(s.stree_mode()){
		for(size_t i=0; i<s.size(); i++){
			s[i].create_segment_tree();	
		}	
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
