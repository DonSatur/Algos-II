#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <iostream>

class sensor {
	double *sensor;	//Un vector con los valores de un sensor
	int longitud; //Longitud del vector sensor (variable)
public:
	double promedio(&sensor,int, int);	//Hace el promedio entre la posicion int y la posicion int
	double maximo(&sensor,int, int);	//Hace el maximo entre la posicion int y la posicion int
	double minimo(&sensor,int, int);	//Hace el minimo entre la posicion int y la posicion int
	double cantidad(&sensor,int, int);	//Calcula la cantidad de valores que se usaron para las operaciones anteriores

	friend std::istream &operator>>(std::istream &, sensor &**);	//Lee el archivo y lo convierte en una matriz
	friend std::ostream &operator<<(std::ostream &, const sensor &*);
	//Chequear si la entrada es correcta
	//Chequear si la consulta es correcta
	//Chequear que el sensor sea existente

};



#endif
