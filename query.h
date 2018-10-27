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
	double mean_ = 0;
	double max_ = 0;
	double min_ = 0;
	size_t amount_ = 0;

	
public:
	query();
	query(data & D);
	query( const query & Q); 
	~query( );

	double		max() const;			//Devuelve el valor maximo del arreglo
	double		min() const;			//Devuelve el valor minimo del arreglo
	double		mean() const;			//Devuelve el promedio del arreglo
	size_t		amount() const;		//Devuelve la cantidad de lugares del arreglo

	query&		operator=( const query & Q); 
	bool 		operator==( const query & Q) const; 
	bool 		operator!=( const query & Q) const; 


	friend
	bool		check_id(string str, sensornet & S, size_t & id,bool & first);
	friend
	bool		check_pos(sensornet & S, size_t id, size_t & pos1, size_t & pos2);
	friend
	bool		read_query(istream & is,ostream & os, sensornet & S, size_t & id, size_t & pos1, size_t & pos2, bool & end);

	bool		process_data(sensornet & S, size_t id, size_t & pos1, size_t & pos2);
	
	void 		process_data_std(sensornet & S, size_t id, size_t & pos1, size_t & pos2);

	void 		process_data_stree(sensornet & S, size_t id, size_t & pos1, size_t & pos2);

	data 		find_data(size_t pos1, size_t pos2, size_t index, segment_tree & s_tree);

	friend
	ostream& 	operator<<(ostream & os, query Q); 	

};

query::query(){
}

query::query(data & D){
	this->mean_ = D.sum()/D.amount();
	this->max_ = D.max();
	this->min_ = D.min();
	this->amount_ = D.amount();
}


query::query( const query & Q){
	this->mean_ = Q.mean_;
	this->max_ = Q.max_;
	this->min_ = Q.min_;
	this->amount_ = Q.amount_;
} 

query::~query( ){

}

double
query::max() const{
	return this->max_;
}

double
query::min() const{
	return this->min_;
}

double
query::mean() const{
	return this->mean_;
}
	
size_t
query::amount() const{
	return this->amount_;
}


query&
query::operator=( const query & Q ){
	if (this->mean_ == Q.mean_ && this->max_ == Q.max_ && this->min_ == Q.min_ && this->amount_ == Q.amount_){
		return *this;
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
	return true;
} 



bool
query::operator!=( const query & Q) const{
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
	return true;
} 



bool
check_id(string str, sensornet & S, size_t & id, bool &first){

	size_t S_size = S.size();
	size_t i;

	for (i = 0; i < S_size; i++){
		if (str == S[i].id()){		//Si encuentra el sensor que pide el query, agrega su posicion
			id = i;
			return true;
		}
	}

	return false;
}



bool
check_pos(sensornet & S, size_t id, size_t & pos1, size_t & pos2){

	if(pos1 > S[id].size() || pos1 >= pos2 || pos1 < 0){	//Chequea que la posicion mas baja no sobrepase
		return false;						//la cantidad de lugares del arreglo	
	}
	else{
		if (pos2 > S[id].size()){	//Chequea si la posicion mas alta sobrepaso la
			pos2= S[id].size();	//cantidad de lugares del arreglo y de ser asi,
		}										//coloca como posicion mas alta la cantidad de 
	}											//lugares del arreglo
	return true;
}

// Se interpreta la consulta y chequea que este bien. Se guardan los valores del flujo de entrada en distintas variables para poder ser utilizadas posteriormente.
bool
read_query(istream & is,ostream & os, sensornet & S, size_t & id, size_t & pos1, size_t & pos2,bool & q_state){
	string str,str2,str3, str4;
	Array <size_t> id_number;		//Aca se guarda la posicion (dentro de sensornet) de cada sensor
	bool first = true;
	size_t j,k ;
	q_state = true;

	getline(is,str2); // Se queda con la primera linea del archivo. Si el archivo es valido contiene los IDs de los sensores a agregar separados por coma
	if(str2[str2.size()-1] == '\r'){ // Chequeo en caso de que el archivo haya sido creado en Windows, por lo cual el ultimo caracter previo al \n es el caracter de retorno \r
		stringstream st_aux(str2);
		getline(st_aux,str2,'\r');
	}
	stringstream str_s(str2);
	
	if(!getline(str_s, str)){
		return false;
	}



	if(str.empty()){ //Si la consulta esta vacia es un error.
		q_state = false;
		return true;
	}
	stringstream str_st(str);
	if (!getline(str_st, str2, ',')){//Se lee solo el ID y se guarda en str2
		os << "BAD QUERY"<<endl;
		q_state	= false;
		return true;
	}
	else{
		if(str2.empty() || str2 == "-"){ // Se pidieron todos los sensores. Como en el ultimo lugar de sensornet hay un SensorTotal, se cambia el id al del mismo.
			id = S.size()-1;
		}
		else{
			if(!check_id(str2, S, id, first)){	//Se chequea que el ID pedido este dentro de los que venian en el archivo de data
				os << "UNKNOWN ID" << endl;
				q_state = false;
				return true;
		
			}
		}	
	}

	if (!getline(str_st, str2, ',')){			//Se lee la primera posicion pedida
		os << "BAD QUERY"<< endl;
		q_state	= false;
		return true;
	}

	if(str2.empty()){ // Si no se pidio una posicion inicial es un error
		os << "BAD QUERY"<< endl;
		q_state	= false;
		return true;		
	}

	j=0;
	while(str2[j] == ' '){ // Se limpian los espacios antes del valor.
		j++;
	}
	k=str2.size();
	while(str2[k-1] == ' '){ // Se limpian los espacios despues del valor
		k--;
	}
	if(str2[j] == '-'){
		if(!isdigit(str2[j+1])){
			os << "BAD QUERY"<<endl;
			q_state	= false;
			return true;
		}
		else{
			j=0;
			k=1;
			str2 = "0";
		}
	}

 	for (size_t i = j; i < k; i++){ // Se chequea que entre las posiciones j y k solo hayan numeros y no simbolos o letras.
   		if (isdigit(str2[i]) == 0){
    		os << "BAD QUERY"<<  endl;
			q_state	= false;
			return true;
    	}
  	}


	stringstream str_st1(str2);
	str_st1 >> pos1;

	if (!getline(str_st, str2, ',')){// Se lee la segunda posicion pedida y se repite el procedimiento anterior
		os << "BAD QUERY"<<endl;
		q_state	= false;
		return true;
	}
	if(str2.empty()){
		os << "BAD QUERY"<<endl;
		q_state	= false;
		return true;		
	}
		
	j=0;
	while(str2[j] == ' '){
  		j++;
 	}
	
	k=str2.size();
	while(str2[k-1] == ' '){
		k--;
	}
	if(str2[j] == '-'){
		if(!isdigit(str2[j+1])){
			os << "BAD QUERY"<< endl;
			q_state	= false;
			return true;
		}
		else{
			j=0;
			k=1;
			str2 = "0";
		}
	}
 	for (size_t i = j; i < k; i++){
   		if (isdigit(str2[i]) == 0){
    		os << "BAD QUERY"<< endl;
			q_state	= false;
			return true;
    	}
  	}

	stringstream str_st2(str2);
	str_st2 >> pos2;

	if(!check_pos(S, id, pos1, pos2)){	//Se chequea que las posiciones sean correctas
		os << "NO DATA" << endl;
		q_state = false;
		return true;
	}
	getline(str_st,str4); // Se chequea que no haya nada mas escrito despues de la segunda posicion pedida. Lo cual resultaria en un error.
	if(!str4.empty()){
		os<< "BAD QUERY"<< endl;
		q_state = false;
		return true;
	}

	return true;
}


// Dependiendo de si se pidio el segment tree se procesa la informacion pedida de una u otra forma. 
bool
query::process_data(sensornet & S, size_t id, size_t & pos1, size_t & pos2){ 
	if (!S.stree_mode()){
		process_data_std(S, id, pos1, pos2);
	}
	else{
		process_data_stree(S, id, pos1, pos2);
	}
	if(this->amount_ == 0){
		return false;
	}
	return true;
}

// En caso de no aclarar que se use segment tree se analiza la informacion buscando las posiciones inicial y final para el sensor pedido y se crea un data a partir de todos los datas.
void
query::process_data_std(sensornet & S, size_t id, size_t & pos1, size_t & pos2){

	Array <data> aux_arr = 1;
	size_t i, j = 0;
	bool first = true;
	data aux2, d;
	
	
	for (i = pos1; i < pos2; i++){ // Se crea un sensor auxiliar que contiene solo la informacion pedida.
		if (aux_arr.size() == 1 && first == true){
			aux_arr[j] = S[id][i];
			first = false;
		}
		else{
			aux_arr.push(S[id][i]);
		}
		j++;
	}
	for(i=0; i<aux_arr.size(); i++){ // Se crea un data a partir del data actual y el siguiente, modificando el actual. De forma de comparar todos los datas del arreglo auxiliar.
		data aux(aux2, aux_arr[i]);
		aux2 = aux;
	}
	// Finalmente se devuelve el data que contiene la informacion resumida de todos los datas pedidos.
	this-> min_ = aux2.min();
	this-> max_ = aux2.max();
	this-> mean_ = aux2.sum()/aux2.amount();
	this-> amount_ = aux2.amount();

}

// En caso de utilizar el segment tree se llama la funcion find_data
void
query::process_data_stree(sensornet & S, size_t id, size_t & pos1, size_t & pos2){
	data aux;
	double tot_am = S[id].size();
	double part_am = pos2-pos1;
	size_t i = ceil(log2(tot_am/part_am));
	size_t index = pow(2, i) - 1; // Se envia la mayor posicion a partir de la cual se puede encontrar el rango de posicioines pedidas.
	
	aux = find_data(pos1, pos2, index, S[id].s_tree());

	this-> min_ = aux.min();
	this-> max_ = aux.max();
	this-> mean_ = aux.sum()/aux.amount();
	this-> amount_ = aux.amount();
	
}

// Funcion recursiva que dadas dos posiciones y un indice a partir del cual empezar a buscar, encuentra el data equivalente al intervalo pedido por las posiciones
data
query::find_data(size_t pos1, size_t pos2, size_t index, segment_tree & s_tree){
	size_t new_index;
	data d_false;
	size_t i;
	double tot_am = (s_tree.size()+1)/2;
	double part_am;

	while (s_tree[index].pos1() != pos1){ // Se busca la primera posicion del segtree que tenga como posicion inicial la pedida por la consulta
		index++;
	}
	// A partir de este punto se trabaja con una posicion en el segtree cuya pos1 es igual a la pedida.
	if (pos2 == s_tree[index].pos2()){ // Caso base. Si el bloque del segtree tiene como pos2 la posicion final pedida se devuelve ese valor
		return s_tree[index];
	}
	else if (pos2 > s_tree[index].pos2()){ // En caso que la posicion final pedida sea mayor a la pos2 del lugar en el que me encuentro se realiza la busqueda cambiando
										   // la posicion inicial a la pos2 del bloque en la cual nos encontrabamos.
		part_am =  pos2-s_tree[index].pos2();
		i = ceil(log2(tot_am/part_am));
		new_index = pow(2, i) - 1; // La busqueda nuevamente empieza en la mayor posicion en la cual se puede encontrar el nuevo rango de posiciones pedidas.

		data aux(s_tree[index], find_data(s_tree[index].pos2(),pos2,new_index,s_tree));
		return aux;
	}
	else{ // Caso en el cual la posicion final pedida esta contenida dentro del rango de posiciones del bloque en el que nos encontramos.
		return find_data(pos1,pos2,index+1,s_tree); // Se vuelve a hacer la busqueda con los mismos valores que antes empezando en la posicion siguiente a la del bloque ya encontrado.
	}
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
