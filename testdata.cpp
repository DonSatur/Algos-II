#include "data.h"
#include <iostream>

using namespace std;

int main(){
	data data1(0,0), data2(0,0);
	char c;
	size_t max,min,sum,amount;
	bool state;
	Array <size_t> pos;

	cout<<"M:Maximo entre D1 y D2 m:Minimo entre D1 y D2 S:Suma entre D1 y D2 P:Imprimir D1 y D2 C:Comparar K:Clonar D:Modificar data "<<endl;
	while(cin >> c){
		switch(c){
			case 'M':
				cout<<data1.calc_max(data1,data2)<<endl;
				break;
			case 'm':
				cout<<data1.calc_min(data1,data2)<<endl;
				break;
			case'S':
				cout<<data1.calc_sum(data1,data2)<<endl;
				break;
			case'P':
				if(!data1.state()){
					cout<<"Data 1 no contiene informacion"<<endl;
				}
				else{
					cout<<"Data 1:"<<endl;
					cout<<"Max: "<<data1.max()<<endl;
					cout<<"Min: "<<data1.min()<<endl;
					cout<<"Sum: "<<data1.sum()<<endl;
					cout<<"Cantidad: "<<data1.amount()<<endl;
				}
				if(!data2.state()){
					cout<<"Data 2 no contiene informacion"<<endl;
				}
				else{
					cout<<"Data 2:"<<endl;
					cout<<"Max: "<<data2.max()<<endl;
					cout<<"Min: "<<data2.min()<<endl;
					cout<<"Sum: "<<data2.sum()<<endl;
					cout<<"Cantidad: "<<data2.amount()<<endl;
				}
				break;
			case 'C':
				if(data1 == data2){
					cout<<"Las datas son iguales"<<endl;
					break;
				}
				cout<<"Las datas no son iguales"<<endl;
				break;
			case 'K':
				data2=data1;
				break;
			case 'D':{
				cout<<"Ingrese el estado de la data"<<endl;
				cin>> state;
				if(!state){
					data aux;
					data1=aux;
					break;
				}
				cin.clear();
				cin.ignore(10000,'\n');
				cout<<"Ingrese valor maximo : ";
				if(!(cin >> max)){
					cout<< "No es un entero "<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				cout<<"Ingrese valor minimo : ";
				if(!(cin >> min)){
					cout<< "No es un entero "<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				if(max<min){
					cout<<"El maximo no puede ser menor al minimo"<<endl;
					break;
				}
				cout<<"Ingrese el valor sum : ";
				if(!(cin >> sum)){
					cout<< "No es un entero "<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				cout<<"Ingrese amount : ";
				if(!(cin >> amount)){
					cout<< "No es un entero positivo"<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				cout<<"Ingrese limite inferior del intervalo: ";
				if(!(cin >> pos[0])){
					cout<< "No es un entero positivo "<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				cout<<"Ingrese limite superior del intervalo: ";
				if(!(cin >> pos[1])){
					cout<< "No es un entero positivo "<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				if(pos[1]<pos[0]){
					cout<<"El limite superior no puede ser menor al inferior"<<endl;
					break;
				}
				data aux(min,max,sum,amount,pos);
				data1 = aux;
				break;
			}
			default:
				cout<<"Invalid input("<< c <<")"<<endl;
				break;
		}
	}

}