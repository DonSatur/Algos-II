#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
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

	query&		operator=( const query & Q); 
	bool 		operator==( const query & Q) const; 
	bool 		operator!=( const query & Q) const; 
	data &		operator[ ]( size_t pos);
	data const &	operator[ ]( size_t pos) const;


	friend
	bool		check_id(string str, sensornet & S, Array <size_t> & id_arr);
	friend
	bool		check_pos(sensornet & S, Array <size_t> id_arr, Array <size_t> & pos_arr);
	friend
	bool		read_query(istream & is,ostream & os, sensornet & S, Array <size_t> & id_arr, Array <size_t> & pos_arr, bool end);
	
	void 		process_data(query & Q, sensornet & S, Array <size_t> id_arr, Array <size_t> pos_arr);

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
	size_t i;
	size_t d_size = d_arr_.size();
	double aux = this->d_arr_[0].value();

	for (i = 1; i < d_size; i++){
		if (this->d_arr_[i] > aux){
			aux = this->d_arr_[i].value();
		}
	}
	return aux;
}
	

double
query::calc_min(){
	size_t i;
	size_t d_size = d_arr_.size();
	double aux = this->d_arr_[0].value();

	for (i = 1; i < d_size; i++){
		if (this->d_arr_[i] < aux){
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
check_id(string str, sensornet & S, Array <size_t> id_arr){

	size_t S_size = S.size();
	size_t i;

	cout<<"Chequeando que este el sensor:"<<str<<endl;
	for (i = 0; i < S_size; i++){
		cout<<S[i].id()<<endl;
		if (str == S[i].id()){			//Si encuentra el sensor que pide el query, agrega su posicion
			id_arr.push(i);		//a id_arr y afirma que el query fue inicialmente correcto
			cout<<"Lo encontro"<<endl;
			return true;
		}
	}
	cout<<"No lo encontro :"<<i<<endl;
	return false;
}



bool
check_pos(sensornet & S, Array <size_t> id_arr, Array <size_t> & pos_arr){
	size_t i;

	for (i = 0; i < id_arr.size(); i++){
		if(pos_arr[0] > S[id_arr[i]].size()){	//Chequea que la posicion mas baja no sobrepase
			return false;						//la cantidad de lugares del arreglo	
		}
		else{
			if (pos_arr[1] > S[id_arr[i]].size()){	//Chequea si la posicion mas alta sobrepaso la
				pos_arr[1]= S[id_arr[i]].size();	//cantidad de lugares del arreglo y de ser asi,
			}										//coloca como posicion mas alta la cantidad de 
		}											//lugares del arreglo
	}
	return true;
}



bool
read_query(istream & is,ostream & os, sensornet & S, Array <size_t> & id_arr, Array <size_t> & pos_arr,bool q_state){
	string str,str2,str3;
	Array <size_t> id_number;		//Aca se guarda la posicion (dentro de sensornet) de cada sensor

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
			stringstream str_st2(str2);
			while (getline(str_st2, str3, ';')){	//Se lee cada q_id por separado
				if(str3.empty()){					//Si no hay q_id y hay un guion, significa que se hacen los calculos
					for (size_t i = 0; i < S.size(); i++){	//con todos los sensores
					id_arr[i] = i;
					}
				}
				else if(!check_id(str3, S, id_arr)){	//Se chequea que los q_id sean correctos
					os << "UNKNOWN ID" << endl;
					q_state = false;
					return true;
				}
			}	
		}
	}
	stringstream str_st3(str2);		//Se convierte a flujo de entrada las posiciones
	if (!str_st3 >> pos_arr[0]){	
		os << "BAD QUERY" << endl;
		q_state = false;
		return true;
	}
	else{
		if (!str_st3 >> pos_arr[1]){
			os << "BAD QUERY" << endl;
			q_state = false;
			return true;
		}
		else{
			if(!check_pos(S, id_arr, pos_arr)){	//Se chequea que las posiciones sean correctas
				os << "NO DATA" << endl;
				q_state = false;
				return true;
			}
		}
	}
	return true;

}


void
query::process_data(query & Q, sensornet & S, Array <size_t> id_arr, Array <size_t> pos_arr){
	size_t j, i;
	double k = 0;
	Array <data> aux_arr;
	data aux(0.0);

	for (j = pos_arr[0] ; j <= pos_arr[1]; j++){
		for (i = 0; i < id_arr.size(); i++){
			if(S[id_arr[i]][j].state() == true){	
				aux = aux + S[id_arr[i]][j];	//Se suman todos los valores de la i-esima posicion
				k++;						//de cada sensor y se cuentan cuantos valores se sumaron
			}
		}
		aux_arr[j] = aux.value()/k;		//Se guarda en un vector el promedio de esos valores
	}
	query Q_aux(aux_arr);	//Se crea un query a partir del arreglo obtenido
	Q = Q_aux;
}

//Esta funcion devuelve los resultados obtenidos
ostream& operator<<(ostream & os, query Q){

	char ch = ',';

//	if (Q.d_arr_.size() == 0){
//		return os;
//	}
	
	os << Q.mean();
	os << ch;
	os << Q.min();
	os << ch;
	os << Q.max();
	os << ch;
	os << Q.amount();
	
	return os;
}	



#endif
