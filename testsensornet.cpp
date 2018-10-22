#include "sensornet.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "cmdline.h"

using namespace std;
/**************************/


static fstream file;		// Flujo de archivo de entrada correspondiente a los valores y IDs de cada sensor
static istream *diss;		// Flujo de entrada que toma los valores que posee difs
static bool enable_stree = false;


int main(){
	size_t i,j;
	sensornet SN1(enable_stree);
	char c;
	string str;

	cout<<"A: Crear sensornet a partir de archivo H: Imprimr el sensor indexado."<<endl;
	while(cin>>c){
		switch(c){
			case 'A':
				cout<<"Ingrese el nombre del archivo a partir del cual se creara la red de sensores."<<endl;
				cin >> str;
				if(str.empty()){
					cout<<"Hubo un error leyendo el string"<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				file.open(str.c_str(),ios::in);
				diss = &file;
				if (!diss->good()) {
					cerr << "cannot open "
			    	 	 << str
			     		 << "."
			    		 << endl;
					break;
				}
				if(!read_file(*diss,SN1)){
					cout<<"El formato esta mal qcyo"<<endl;
				}
				break;
			case 'H':
				if(!(cin >> i)){
					cout<< "No es un entero"<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				if(i < SN1.size()){
					cout<<SN1[i].id()<<endl;
					for(j = 0; j<SN1[i].size() ; j++){
						cout<<SN1[i][j].min()<<endl;
					}
					break;
				}
				cout<< "Indice muy alto"<<endl;
				break;

			default:
				cout<<"Invalid input("<< c <<")"<<endl;
				break;
		}
	}


}