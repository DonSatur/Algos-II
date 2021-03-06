#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "Array.h"
#include "sensornet.h"


using namespace std;

class query {
	Array <data> d_arr_;	//El arreglo que se va a crear con todos los datos que se van a utilizar
	double mean_;
	double max_;
	double min_;
	size_t amount_;

	
public:
	query();
	query(Array <data> d_arr);
	query( const query & Q); 
	~query( );

	double		calc_max();			//Obtiene el valor maximo del arreglo
	double		calc_min();			//Obtiene el valor minimo del arreglo
	double		calc_mean();				//Obtiene el promedio del arreglo
	size_t		calc_amount();			//Obtiene la cantidad de lugares del arreglo

	double		max();			//Devuelve el valor maximo del arreglo
	double		min();			//Devuelve el valor minimo del arreglo
	double		mean();			//Devuelve el promedio del arreglo
	size_t		amount();		//Devuelve la cantidad de lugares del arreglo

	size_t		size();

	query&		operator=( const query & Q); 
	bool 		operator==( const query & Q) const; 
	bool 		operator!=( const query & Q) const; 
	data &		operator[ ]( size_t pos);
	data const &	operator[ ]( size_t pos) const;


	friend
	bool		check_id(string str, sensornet & S, Array <size_t> & id_arr,bool & first);
	friend
	bool		check_pos(sensornet & S, Array <size_t> id_arr, size_t & pos1, size_t & pos2);
	friend
	bool		read_query(istream & is,ostream & os, sensornet & S, Array <size_t> & id_arr, size_t & pos1, size_t & pos2, bool & end);
	
	void 		process_data(query & Q, sensornet & S, Array <size_t> id_arr, size_t &pos1, size_t & pos2);

	friend
	ostream& 	operator<<(ostream & os, query Q); 	

};

query::query(){
	this->d_arr_ = ARRAY_DEFAULT_SIZE;
	this->mean_ = 0;
	this->max_ = 0;
	this->min_ = 0;
	this->amount_ = 0;
}

query::query(Array <data> d_arr){
	this->d_arr_ = d_arr;
	this->amount_ = calc_amount();
	this->max_ = calc_max();
	this->min_ = calc_min();
	this->mean_= calc_mean();
	
}


query::query( const query & Q){
	this->d_arr_ = Q.d_arr_;
	this->mean_ = Q.mean_;
	this->max_ = Q.max_;
	this->min_ = Q.min_;
	this->amount_ = Q.amount_;
} 

query::~query( ){

}
	

double
query::calc_max(){
	size_t i, j = 0;
	size_t d_size = d_arr_.size();
	while(this->d_arr_[j].state() == false){
		j++;
	}
	double aux = this->d_arr_[j].value();

	for (i = 1; i < d_size-1; i++){
		if (this->d_arr_[i] > aux && this->d_arr_[i].state() == true){
			aux = this->d_arr_[i].value();
		}
	}
	return aux;
}
	

double
query::calc_min(){
	size_t i, j = 0;
	size_t d_size = d_arr_.size();
	while(this->d_arr_[j].state() == false){
		j++;
	}
	double aux = this->d_arr_[j].value();

	for (i = j+1; i < d_size-1 ; i++){
		if (this->d_arr_[i] < aux && this->d_arr_[i].state() == true){
			aux = d_arr_[i].value();	
		}
	}

	return aux;
}


size_t
query::calc_amount(){
	size_t i, aux = 0;
	size_t d_size = this->d_arr_.size();
	for (i = 0; i < d_size; i++){
		if (this->d_arr_[i].state() == true){
			aux++;
		}
	}
	return aux;
}


double
query::calc_mean(){
	size_t i;
	double aux = 0;
	size_t d_size = this->d_arr_.size();

	for (i = 0; i < d_size; i++){
		if (this->d_arr_[i].state( )== true){
			aux+=this->d_arr_[i].value();
		}
	}
	return aux/this->amount_;
}


double
query::max(){
	return this->max_;
}

double
query::min(){
	return this->min_;
}

double
query::mean(){
	return this->mean_;
}
	
size_t
query::amount(){
	return this->amount_;
}


size_t
query::size(){
	return d_arr_.size();
}

query&
query::operator=( const query & Q ){
	if (this->d_arr_ == Q. d_arr_ && this->mean_ == Q.mean_ && this->max_ == Q.max_ && this->min_ == Q.min_ && this->amount_ == Q.amount_){
		return *this;
	}
	if(this->d_arr_ != Q.d_arr_){
		this->d_arr_ = Q.d_arr_;
	}
	if(this->mean_ != Q.mean_){
		this->mean_ = Q.mean_;
	}
	if(this->max_ != Q.max_){
		this->max_ = Q.max_;
	}
	if(this->min_ != Q.min_){
		this->min_ = Q.min_;
	}
	if(this->amount_ != Q.amount_){
		this->amount_ = Q.amount_;
	}
	return *this;
} 
	

bool
query::operator==( const query & Q) const{
	if(this->d_arr_ != Q.d_arr_){
			return false;
	}
	else{
		if(this->mean_ != Q.mean_){
			return false;
		}
		else{
			if(this->max_ != Q.max_){
				return false;
			}
			else{
				if(this->min_ != Q.min_){
					return false;
				}
				else{
					if(this->amount_ != Q.amount_){
						return false;
					}
				}
			}
		}
	}
	return true;
} 



bool
query::operator!=( const query & Q) const{
	if(this->d_arr_ == Q.d_arr_){
			return false;
	}
	else{
		if(this->mean_ == Q.mean_){
			return false;
		}
		else{
			if(this->max_ == Q.max_){
				return false;
			}
			else{
				if(this->min_ == Q.min_){
					return false;
				}
				else{
					if(this->amount_ == Q.amount_){
						return false;
					}
				}
			}
		}
	}
	return true;
} 

	
data &
query::operator[ ]( size_t pos){
	return this->d_arr_[pos];
}


data const &
query::operator[ ]( size_t pos) const{
	return this->d_arr_[pos];
}



bool
check_id(string str, sensornet & S, Array <size_t> & id_arr,bool &first){

	size_t S_size = S.size();
	size_t i;

	for (i = 0; i < S_size; i++){
		while (str[i] = '\0'){
			str[i] = str[i+1];
		}
		if (str == S[i].id()){		//Si encuentra el sensor que pide el query, agrega su posicion
			if (id_arr.size() == 1 && first == true){
				id_arr[0] = i;
				first = false;
			}
			else{
				id_arr.push(i);	
			}

			return true;
		}
	}

	return false;
}



bool
check_pos(sensornet & S, Array <size_t> id_arr, size_t & pos1, size_t & pos2){
	size_t i;

	for (i = 0; i < id_arr.size(); i++){
		if(pos1 > S[id_arr[i]].size() || pos1 > pos2 || pos1<0){	//Chequea que la posicion mas baja no sobrepase
			return false;						//la cantidad de lugares del arreglo	
		}
		else{
			if (pos2 > S[id_arr[i]].size()){	//Chequea si la posicion mas alta sobrepaso la
				pos2= S[id_arr[i]].size();	//cantidad de lugares del arreglo y de ser asi,
			}										//coloca como posicion mas alta la cantidad de 
		}											//lugares del arreglo
	}
	return true;
}



bool
read_query(istream & is,ostream & os, sensornet & S, Array <size_t> & id_arr, size_t & pos1, size_t & pos2,bool & q_state){
	string str,str2,str3;
	Array <size_t> id_number;		//Aca se guarda la posicion (dentro de sensornet) de cada sensor
	char ch;
	bool first = true;
	bool first1 = true;
	size_t i;

	id_arr.clear();
	q_state = true;


	if (!getline(is, str)){					//Se lee por linea
		return false;
	}
	else{
		stringstream str_st(str);				
		if (!getline(str_st, str2, ',')){			//Se leen solo los q_ids
			os << "BAD QUERY" << endl;
			q_state	= false;
			return true;
		}
		else{
			if(str2.empty()){				//Si no hay q_id y hay un guion, significa que se hacen los calculos
				for (i = 0; i < S.size(); i++){	//con todos los sensores
					if (id_arr.size() == 1 && first1 == true){
						i=0;
						id_arr[0] = i;
						first1 = false;
					}
					else{
						id_arr.push(i);	

					}
					
				}
			}
			else{
				stringstream str_st2(str2);
				while (getline(str_st2, str3, ';')){	//Se lee cada q_id por separado
					if(!check_id(str3, S, id_arr,first)){	//Se chequea que los q_id sean correctos
						os << "UNKNOWN ID" << endl;
						q_state = false;
						return true;
					}
				}
			}	
		}
		if(!str_st >> pos1){
			os << "BAD QUERY" << endl;
			q_state	= false;
			return true;
		}
		if(str_st >> ch && ch != ','){
			os << "BAD QUERY" << endl;
			q_state	= false;
			return true;
		}
		if(!str_st >> pos2){
			os << "BAD QUERY" << endl;
			q_state	= false;
			return true;
		}

		if(!check_pos(S, id_arr, pos1, pos2)){	//Se chequea que las posiciones sean correctas
			os << "NO DATA" << endl;
			q_state = false;
			return true;
		}
	
	}
	return true;

}


void
query::process_data(query & Q, sensornet & S, Array <size_t> id_arr, size_t & pos1, size_t & pos2){

	Array <data> aux_arr = 1;
	size_t i, j = 0, k = 0;
	bool first = true;
	data aux(0.0);
	double q = 0;
	
	
	if (id_arr.size() == 1){
		for (i = pos1; i <= pos2; i++){
			if (aux_arr.size() == 1 && first == true){
				aux_arr[j] = S[id_arr[j]][i];
				first = false;
			}
			else{
				aux_arr.push(S[id_arr[0]][i]);
			}
			j++;
		}
	}

	else{
		first = true;
		for (i = pos1; i <= pos2; i++){
			aux = 0.0;
			q = 0;
			for (j = 0; j < id_arr.size(); j++){
				aux = aux + S[id_arr[j]][i];
				q++;
			}			if (aux_arr.size() == 1 && first == true){
				aux_arr[k] = aux.value()/q;
				first = false;
			}
			else{
				aux_arr.push(aux.value()/q);
			}
			k++;
		} 
	}

	query Q_aux(aux_arr);
	Q = Q_aux;



}

//Esta funcion devuelve los resultados obtenidos
ostream& operator<<(ostream & os, query Q){

	char ch = ',';
	
	os << Q.mean();
	os << ch;
	os << Q.min();
	os << ch;
	os << Q.max();
	os << ch;
	os << Q.amount();
	os << endl;
	
	return os;
}	



#endif