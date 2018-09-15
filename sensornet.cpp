#include "sensornet.h"
#include <iostream>
#include <cmath>

using namespace std;

template <typename T> 
sensor::mean(&sensor S,string sensors,int pos1, int pos2)
{
	int i, pos2;
	double sum=0;
	for i=pos1,i++,i<=pos2
		sum+=S[i];
	return sum/(pos2-pos1);

}

sensor::max(&sensor S,int pos1, int pos2)
{
	int i;
	double max=0;
	for i=pos1,i++,i<=pos2
		if S[i]>=max
			max=S[i];
	return max;
}

sensor::min(&sensor S,int pos1, int pos2)
{
	int i;
	double min=0;
	for i=pos1,i++,i<=pos2
		if S[i]<min
			min=S[i];
	return min;
}


istream & operator>> (std::istream& is,sensornet& S)
{
	// Limpio el arreglo y leo en formato (T1,T2,...,Tn) de is. Si no se hace conforme a lo
	// esperado, limpio el arreglo (devuelvo uno sin elementos)
	// Si llega a EOF, marcará en el istream

	double aux = 0;
	char ch = 0;
	size_t i=0;

	arr.clear();
	if(  (is >> aux) ){
		S[i].values.push_back(aux);
		while( (is >> ch) && (ch == ',') && (is >> aux) ){
			i++;
			S[i].values.push_back(aux);
		}
	} 
	if ( ch != '/0' ){
		arr.clear();
	}

	return is;
}

template <typename T> 
void istream & read_file(istream &is, sensornet &s)
{

	string aux;
	double aux2;
	size_t i = 0, j = 0;
	sensornet sArray;

	getline(is,aux);
	while (aux[j]){
		if(aux[j] == ','){
			sArray.push_back(sensor(str));	//se puede hacer esto??
			i=0;
		}
		else{
			str[i] = aux[j];
			i++;
		}
		j++;
	}
	sArray.push_back(sensor(str));

	while(getline(is, aux)){
		streamstring str_st(str);
		if(!(str_st>>sArray) || str_st==eof){
			
		}
			// FALTA TERMINAR
	}
}