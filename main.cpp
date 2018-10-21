#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "cmdline.h"
#include "sensornet.h"
#include "query.h"
#include "Array.h"
#include "data.h"

using namespace std;


// Funciones correspondientes a cada opcion posible de la linea de comandos
static void opt_input(string const &);
static void opt_output(string const &);
static void opt_data(string const &);
static void opt_help(string const &);
static void opt_stree(string const &);

/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "d", "data", NULL, opt_data, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, "s", "stree", NULL, opt_stree, OPT_DEFAULT},
	{0, },
};

static fstream difs;		// Flujo de archivo de entrada correspondiente a los valores y IDs de cada sensor
static istream *diss;		// Flujo de entrada que toma los valores que posee difs
static fstream ifs; 		// Flujo de archivo de entrada correspondiente al query 
static istream *iss = 0;	// Flujo de entrada que de existir archivo, toma sus valores y si no, lee el query por cin
static fstream ofs;			// Flujo de archivo de salida donde se escribiran los resultados
static ostream *oss = 0;	// Flujo de salida que de existir archivo de salida, toma su direccion y si no, escribe por cout
static bool enable_stree = false;


// Definicion y desarrollo de las funciones necesarias para cada opcion:

static void
opt_input(string const &arg)
{
	// Si la entrada es "-", el flujo de entrada es cin
	if (arg == "-") {
		iss = &cin;		
	}
	else {
		ifs.open(arg.c_str(), ios::in); // Al ser un archivo, se abre para lectura
		iss = &ifs;
	}

	// Se verifica que el flujo sea correcto
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
	// Si la entrada es "-", el flujo de entrada es cout
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		if(!ofs){		// Chequea si el archivo existe y si no, lo crea
			ofstream output_csv("output.csv");
			output_csv.open(arg.c_str(), ios::out);
			oss = &output_csv;
		}
		else{			// Si el archivo existe, lo abre para escritura
			ofs.open(arg.c_str(), ios::out);
			oss = &ofs;
		}
		
	}

	// Se verifica que el flujo sea correcto
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		
	}
}
static void
opt_data(string const &arg)
{
	difs.open(arg.c_str(), ios::in); 	// Al ser un archivo obligatoriamente, se abre y 
	diss = &difs;						// luego se pasa la direccion al flujo de entrada

	// Se verifica que el flujo sea correcto
	if (!diss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}


// Opcion que indica como se deben ingresar los argumentos en la linea de comandos
static void
opt_help(string const &arg)
{
	cout << "cmdline [-d file] [-i file] [-o file]"
	     << endl;
	exit(0);
}

static void
opt_stree(string const &arg){
	enable_stree = true;
}



int
main(int argc, char * const argv[])
{
	cmdline cmdl(options);
	cmdl.parse(argc, argv); 

	bool q_state = true;			// Variable que indica si las consultas fueron correctas o no
	sensornet S(enable_stree);					// Inicializacion del arreglo de sensores
	size_t id = 0;						// Arreglo donde se guarda la posicion (en el arreglo de sensores) 
									// de cada sensor (que pide la consulta) 
	size_t pos1 = 0, pos2 = 0;		// Posiciones para las cuales se calcula el resultado
	query Q;						// Objeto donde se van a guardar:
									//	*el arreglo al que se le calculan los resultados
									//	*los resultados: promedio, minimo, maximo, cantidad de valores.

	if (!read_file(*diss,S)){		// Lee el archivo de entrada donde estan los valores de los sensores
		return EXIT_FAILURE;
	}
	else{
		while(read_query(*iss,*oss, S, id, pos1, pos2,q_state)){	// Lee las consultas
			if(q_state){												// Si las consultas son correctas,
				Q.process_data(Q, S, id, pos1, pos2);				// se procesa la data.
				*oss <<Q;									// Se escribe el resultado donde corresponde.

			}

		}
	}
	return EXIT_SUCCESS;
}