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

	friend bool read_file(istream&,ostream &os,sensornet&);
	bool read_ids(string IDs, sensornet &s);
	bool read_values(istream &is, sensornet &s, size_t &t);
	void fill_sensors(sensornet &s);
	void create_total_sensor(sensornet &s);

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


bool
read_ids(string IDs, sensornet &s){
	string ID;
	bool first = true;
	size_t i;

	if(IDs.empty())// En caso de que no haya ningun ID se devuelve un mensaje de error.
			return false;

	stringstream str_st(IDs);
	while(getline(str_st,ID,',')){ // Se parsea la linea ingresada por comas y se chequea que los datos sean validos.

		for(i = 0 ; i<s.size() ; i++){ // Se chequea que los nombres de los sensores no esten repetidos.
			if(ID == s[i].id())
				return false; 
		}

		sensor s_aux(ID); // Se crea un sensor auxiliar a partir de un ID con el nombre provisto por el archivo
		if (s.size() == 1 && first){ // Se toma por separado el caso en el que es el primer elemento del arreglo de sensores.
			s[0] = s_aux;
			first = false;
		}
		else{
			s.push(s_aux);
		}
	}
	return true;
}

bool
read_values(istream & is,sensornet &s, size_t &t){
	string values,parse;
	size_t data_count = 0, i;
	Array <bool> first = 0;
	size_t s_index;
	double value;


	for (i = 0; i < s.size(); i++)
		first.push(true);
	while(getline(is, values)){ // Se lee linea por linea el resto del archivo, en las cuales deberian estar los datos separados por comas
		if(values[values.size()-1] == '\r'){ // Chequeo del caso Windows.
			stringstream st_aux(values);
			getline(st_aux,values,'\r');
		}
		data_count = 0;
		s_index = 0;
		stringstream str_st(values);
		while(getline(str_st,parse,',')){ // Se parsea la cadena con valores por comas.
			data_count++;
			if(data_count > s.size()){// Caso en el cual hubieron mas datos que sensores.
				return false;
			}

			if(s[s_index].size() == 1 && first[s_index] == true){ //Se evalua el caso en que sea el primer elemento del arreglo de datos. Se inicializa el sensor en NO_DATA.
				data no_data(0);
				s[s_index][0] = no_data;					 
				first[s_index] = false;
			}
			else{
				data no_data(t);
				s[s_index].push(no_data);
			}
			if(!parse.empty()){ // Luego de inicializar el dato en NO_DATA se chequea que haya un dato valido dentro.
				if(!isdigit(parse[0]) && parse[0] != '-')
					return false;
				else{
					for (size_t r = 1; r<parse.size(); r++)
						if(parse[0] == '.'){
							return false;
						if(!isdigit(parse[r]) && parse[r] != '.')
							return false;
						if(parse[r] == '.' && !isdigit(parse[r+1]))
							return false;
					}
				} // Si el dato estaba vacio o si tenia un dato, y este paso por todas las pruebas anteriores se procede a ingresarlo al sensor en la posicion correspondiente.
				stringstream str_st2(parse);
				str_st2 >> value; 
				data d_aux(value, t); // Se crea un dato a partir del valor leido con la posicion j. 
				s[s_index][t] = d_aux;
			}
			s_index++;
		}
		if(parse.empty()){  // Se chequea el caso en el cual el ultimo sensor para el tiempo j no tenia data
			data_count++;
			data no_data(t);
			s[s_index].push(no_data);
		}
		t++;
		if(data_count != s.size()) // m cuenta la cantidad de valores que se agregaron para el tiempo j. Si no coincide con la cantidad de sensores ingresados inicialmente es un error.
			return false;

	}
	return true;
}

void
create_total_sensor(sensornet &s){
	size_t length,t,s_index;
	sensor all_sensors("All sensors"); // Se crea un sensor a partir del ID All sensors que luego se rellenara con los promedios en cada tiempo de todos los sensores
	double mean;

	length = s[s.size()-1].size();
	s.push(all_sensors);
	for(t = 0; t < length; t++){  // Se recorre un sensor hasta el final
		data data_temp(0);
		data data_t(0);
		for (s_index = 0 ; s_index < s.size()-1; s_index++){ // Se recorre cada sensor
			data data_temp(data_t,s[s_index][t]);  // Se genera un data a partir de todos los sensores para el tiempo j
			data_t = data_temp;
		}
		if(data_t.amount() != 0){
			mean = data_t.sum()/data_t.amount(); // Se calcula el promedio de los valores leidos para el tiempo j
			data data_temp(mean,t);
			data_t = data_temp; 
		}
		else{
			data no_data(t);
			data_t = no_data;
			}
		if (s[s.size()-1].size() == 1 && t == 0){ // Se guarda en el ultimo sensor (All sensors) el promedio de los datos para cada tiempo.
			s[s.size()-1][0] = data_t;
		}
		else{
			s[s.size()-1].push(data_t);
		}
	}	
}

void
fill_sensors(sensornet &s){
	size_t i,j;

	for(i = 0; i < s.size(); i++){ // Una vez llena la red de sensores con el archivo se completa cada arreglo con NO_DATA para que la longitud del arreglo sea alloc_size (potencia de 2)
		if (s[i].size() != s[i].alloc_size()){
			for(j = s[i].size(); j < s[i].alloc_size(); j++){
				data no_data(j);
				s[i][j] = no_data;
			}
		}
	}
}

// Metodo que recibe un archivo mediante flujo de entrada, lo parsea como corresponda para crear una red de sensores
bool read_file(istream &is,ostream &os,sensornet &s){
	
	string IDs;
	size_t t = 0;

	getline(is,IDs); // Se queda con la primera linea del archivo. Si el archivo es valido contiene los IDs de los sensores a agregar separados por coma
	if(IDs[IDs.size()-1] == '\r'){ // Chequeo en caso de que el archivo haya sido creado en Windows, por lo cual el ultimo caracter previo al \n es el caracter de retorno \r
		stringstream st_aux(IDs);
		getline(st_aux,IDs,'\r');
	}

	if(!(read_ids(IDs,s))){
		os << "BAD DATA"<<endl;
		return false;
	}
	
	if(!read_values(is,s,t)){
		os << "BAD DATA"<<endl;
		return false;
	}

	if(t == 0){
		for(size_t i = 0; i < s.size(); i++){
			s[i].clear();
		}
	}

	else{	
		fill_sensors(s);
		create_total_sensor(s);
		if(s.stree_mode()){ // Si el usuario ingreso la opcion de utilizar el segment tree se crean los mismo.
			for(size_t i=0; i<s.size(); i++){
				s[i].create_segment_tree();	
			}	
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
