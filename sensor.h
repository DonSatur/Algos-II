#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <iostream>

class sensor {
	double *sensor;
public:
	sensor(double,double,double,double);	//Crea un vector sensor
	double posicion(int);	//Encuentra el valor en la posicion int
	double promedio(int, int);	//Hace el promedio entre la posicion int y la posicion int
	double maximo(int, int);	//Hace el maximo entre la posicion int y la posicion int
	double minimo(int, int);	//Hace el maximo entre la posicion int y la posicion int
	double cantidad(int, int);


	friend std::istream &operator>>(std::istream &, sensor &*);	//Lee el archivo y lo convierte en una matriz
	friend std::ostream &operator<<(std::ostream &, const sensor &*);


}


class complejo {
	double re_, im_;
public:
	complejo();
	complejo(double);
	complejo(double, double);
	complejo(const complejo &);
	complejo const &operator=(complejo const &);
	complejo const &operator*=(complejo const &);
	complejo const &operator+=(complejo const &);
	complejo const &operator-=(complejo const &);
	~complejo();

	double re() const;
	double im() const;
	double abs() const;
	double abs2() const;
	complejo const &conjugar();
	complejo const conjugado() const;
	bool zero() const;

	friend complejo const operator+(complejo const &, complejo const &);
	friend complejo const operator-(complejo const &, complejo const &);
	friend complejo const operator*(complejo const &, complejo const &);
	friend complejo const operator/(complejo const &, complejo const &);
	friend complejo const operator/(complejo const &, double);

	friend bool operator==(complejo const &, double);
	friend bool operator==(complejo const &, complejo const &);

	friend std::ostream &operator<<(std::ostream &, const complejo &);
	friend std::istream &operator>>(std::istream &, complejo &);
};

#endif