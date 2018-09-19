// Prueba de la clase cmdline: dado un factor entero pasado por la
// línea de comando, leemos una secuencia de números que ingresan
// por la entrada estándar, los multiplicamos por ese factor, y
// luego mostramos el resultado por std::cout.
//
// $Id: main.cc,v 1.5 2012/09/15 12:23:57 lesanti Exp $

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "cmdline.h"
#include "sensor.h"

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_data(string const &);
static void opt_help(string const &);

// Tabla de opciones de línea de comando. El formato de la tabla
// consta de un elemento por cada opción a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opción lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opción.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opción en caso que no esté explícitamente presente
//   en la línea de comandos del programa. Si la opción no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al método de parseo de la opción,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La última columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opción: cuando la
//   opción es obligatoria, deberá activarse OPT_MANDATORY.
//
// Además, la última entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//

/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "d", "data", NULL, opt_data, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static fstream difs;
static istream *diss;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)



/*****************************************************/

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void
opt_data(string const &arg)
{
	difs.open(arg.c_str(), ios::in); 
	diss = &difs;

	// Verificamos que el stream este OK.
	//
	if (!diss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_help(string const &arg)
{
	cout << "cmdline [-d file] [-i file] [-o file]"
	     << endl;
	exit(0);
}




//Funcion que lee el query

bool
read_query(istream & is, Array <string> & q_ids, int pos1, int pos2)
{
	bool state=false;
	string str, str2, str3;
	stringstream str_st, str_st2;
	char ch=',';
	char ch2=';';

	if(getline(is, str)){				//Se lee una linea
		stringstream str_st(str);		//Se convierte en flujo
		getline(str_st,str2,ch)	;		//Se leen los ids por un lado
		stringstream str_st2(str2);		//Se convierte en flujo
		while(getline(str_st2,str3,ch2)){	//Se separa cada id y se guarda en un arreglo de strings
			q_ids.push_back(str3);
		}			
		if(!(str_st2>>pos1) || (str_st2>>ch && ch!=',')){
			cout<< "BAD QUERY" << endl;
			return state;
		}
		if (!(str_st2>>pos2) || (str_st2>>ch && ch!='\0')){		//PREGUNTAR SI >> RECONOCE AL '/0'
			cout<< "BAD QUERY" << endl;
			return state;
		}

		state=true;
		return state;
	}
	return state;
}

int 
amount(size_t pos1, size_t pos2){
	return int(pos2)-int(pos1)+1;
}

double
mean(Array <double> vector, size_t pos1, size_t pos2, int amount){
	size_t i;
	double sum = 0;

	for (i=pos1, i<=pos2, i++){
		sum+=vector[i];
	}

	return sum/double(amount);		//PREGUNTAR SI ESTA BIEN CONVERTIRLO A DOUBLE PARA HACER LA DIVISION
}

double 
max_min(Array <double> vector, size_t pos1, size_t pos2){
	double max=vector[pos1], min=vector[pos1];
	for (int i=pos1+1, i<=pos2, i++){
		if (vector[i]>=max){
			max=vector[i];
		}
		if(vector[i]<min){
			min=vector[i];
		}
	}
}

int
main(int argc, char * const argv[])
{
	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline


}