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

// Metodo que recibe un archivo mediante flujo de entrada, lo parsea como corresponda para crear una red de sensores

bool read_file(istream &is,sensornet &s){
	
	string str,str2;
	size_t i=0, m, j = 0;
	Array <bool> first;
	first[0] = true;
	double val_aux;
	bool k = true;
	sensor all_sensors("All sensors"); // Se crea un sensor a partir del ID All sensors que luego se rellenara con los promedios en cada tiempo de todos los sensores

	getline(is,str2); // Se queda con la primera linea del archivo. Si el archivo es valido contiene los IDs de los sensores a agregar separados por coma
	if(str2[str2.size()-1] == '\r'){ // Chequeo en caso de que el archivo haya sido creado en Windows, por lo cual el ultimo caracter previo al \n es el caracter de retorno \r
		stringstream st_aux(str2);
		getline(st_aux,str2,'\r');
	}
	stringstream str_st(str2);
	while(getline(str_st,str,',')){ // Se parsea la linea ingresada por comas y se chequea que los datos sean validos.
		
		if(str.empty()){ // En caso de que no haya ningun ID se devuelve un mensaje de error.
			cout<<"BAD DATA"<<endl;
			return false;
		}

		for(i = 0 ; i<s.size() ; i++){ // Se chequea que los nombres de los sensores no esten repetidos.
			if(str == s[i].id()){
				cout<<"BAD DATA"<<endl;
				return false; 
			}
		}

		sensor s_aux(str); // Se crea un sensor auxiliar a partir de un ID con el nombre provisto por el archivo
		if (s.size() == 1 && k){ // Se toma por separado el caso en el que es el primer elemento del arreglo de sensores.
			s[0] = s_aux;
			k = false;
		}
		else{
			s.push(s_aux);
		}
	}
	for (size_t i = 0; i < s.size(); i++){
		first.push(true);
	}
	while(getline(is, str2)){ // Se lee linea por linea las siguientes lineas, en las cuales deberian estar los datos separados por comas
		if(str2[str2.size()-1] == '\r'){ // Chequeo del caso Windows.
			stringstream st_aux(str2);
			getline(st_aux,str2,'\r');
		}
		m=0;
		i=0;
		stringstream str_st(str2);
		while(getline(str_st,str,',')){ // Se parsea la cadena con valores por comas.
			m++;
			if(m>s.size()){ // Caso en el cual hubieron mas datos que sensores.
				cout << "BAD DATA"<< endl;
				return false;
			}
			if(s[i].size() == 1 && first[i] == true){ //Se evalua el caso en que sea el primer elemento del arreglo de datos. Se inicializa el sensor en NO_DATA.
				data no_data(0);
				s[i][0] = no_data;					 
				first[i] = false;
			}
			else{
				data no_data(j);
				s[i].push(no_data);
			}
			if(!str.empty()){ // Luego de inicializar el dato en NO_DATA se chequea que haya un dato valido dentro.
				if(!isdigit(str[0]) && str[0] != '-'){
					cout<<"BAD DATA" << endl;
					return false;
				}
				else{
					for (size_t r = 1; r<str.size(); r++){
						if(str[0] == '.'){
							cout<<"BAD DATA"<<endl;
							return false;
						}
						if(!isdigit(str[r]) && str[r] != '.'){
							cout<<"BAD DATA"<<endl;
							return false;
						}
						if(str[r] == '.' && !isdigit(str[r+1])){
							cout << "BAD DATA"<<endl;
							return false;
						}
					}
				} // Si el dato estaba vacio o si tenia un dato, y este paso por todas las pruebas anteriores se procede a ingresarlo al sensor en la posicion correspondiente.
				stringstream str_st2(str);
				str_st2 >> val_aux; 
				data d_aux(val_aux, j); // Se crea un dato a partir del valor leido con la posicion j. 
				s[i][j] = d_aux;
			}
			i++;
		}
		if(str.empty()){  // Se chequea el caso en el cual el ultimo sensor para el tiempo j no tenia data
			m++;
			data no_data(j);
			s[i].push(no_data);
		}
		j++;
		if(m != s.size()){ // m cuenta la cantidad de valores que se agregaron para el tiempo j. Si no coincide con la cantidad de sensores ingresados inicialmente es un error.
			cout << "BAD DATA" << endl;
			return false;
		}

	}

	if(j == 0){
		for(i=0; i<s.size(); i++){
			s[i].clear();
		}
	}

	else{	
		for(i=0; i<s.size(); i++){ // Una vez llena la red de sensores con el archivo se completa cada arreglo con NO_DATA para que la longitud del arreglo sea alloc_size (potncia de 2)
			if (s[i].size() != s[i].alloc_size()){
				for(j=s[i].size(); j<s[i].alloc_size(); j++){
					data no_data(j);
					s[i][j] = no_data;
				}
			}
		}

		m = s[i-1].size();
		s.push(all_sensors);
		for(j = 0; j<m; j++){  // Se recorre un sensor hasta el final
			data data_aux(0);
			data d_aux(0);
			for (i = 0 ; i<s.size()-1; i++){ // Se recorre cada sensor
				data d_aux(data_aux,s[i][j]);  // Se genera un data a partir de todos los sensores para el tiempo j
				data_aux = d_aux;
			}
			if(data_aux.amount() !=0){
				val_aux = data_aux.sum()/data_aux.amount(); // Se calcula el promedio de los valores leidos para el tiempo j
				data d_aux(val_aux,j); 
			}
			else{
				data d_aux(j);
			}
			if (s[s.size()-1].size() == 1 && j == 0){ // Se guarda en el ultimo sensor (All sensors) el promedio de los datos para cada tiempo.
				s[s.size()-1][0] = d_aux;
			}
			else{
				s[s.size()-1].push(d_aux);
			}
		}	
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
