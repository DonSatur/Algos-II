#include "Array.h"
#include <iostream>

using namespace std;

int main(){
	char c;
	size_t i;
	size_t j;
	Array <double> arr;
	Array <double> arr2;
	double aux;

	cout<<"A: Agregar valor  I: Imprimir Y:Imprimir segundo arreglo P: Comparar T: Tamaño  L: Limpiar  H : Index  K:clonar" << endl;
	while(cin >> c){
		switch(c){
			case 'A':
				if(!(cin >> aux)){
					cout<< "No es un double "<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				arr.push(aux);

				break;
			case 'T':
				cout<<arr.size()<<endl;
				break;
			case 'L':
				arr.clear();
				break;
			case 'H':
				if(!(cin >> i)){
					cout<< "No es un entero"<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				if(i < arr.size()){
					cout<<arr[i]<<endl;
					break;
				}
				cout<< "Indice muy alto"<<endl;
				break;
			case 'I':
				if(arr.size() == 0){
					cout<<"Arreglo vacio"<<endl;
					break;
				}
				cout<<arr[0];
				for(j = 1 ; j < arr.size(); j++){
					cout<<','<<arr[j];
				}		
				cout<<endl;
				break;
			case 'Y':
				if(arr2.size() == 0){
					cout<<"Arreglo vacio"<<endl;
					break;
				}
				cout<<arr2[0];
				for(j = 1 ; j < arr2.size(); j++){
					cout<<','<<arr2[j];
				}		
				cout<<endl;
				break;
			case 'K':
				arr2=arr;
				break;
			case 'P':
				if(arr == arr2){
					cout<<"Los arreglos son iguales"<<endl;
					break;
				}
				cout<<"Los arreglos no son iguales"<<endl;
				break;
			default:
				cout<<"Invalid input("<< c <<")"<<endl;
				break;
		}
	} 
}