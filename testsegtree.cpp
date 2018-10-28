#include <iostream>
#include "sensor.h"
#include "Array.h"
#include "data.h"
#include "segment_tree.h"

using namespace std;

int main(){
	size_t i;
	segment_tree ST1,ST2;
	double daux;
	size_t j = 0;
	char c;
	Array <data> arr;

	cout<<"A:Push data to array L: Clear array O: Compare segment trees C:Create segment tree from array K: Clone P: Print segment tree. H: Index I: Print second segment tree "<<endl;
	while (cin >> c){
		switch(c){
			case 'A':{
				if(!(cin >> daux)){
					cout<< "Value is not an int."<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				data aux(daux,j);
				arr.push(aux);
				j++;
				break;
			}
			case 'H':
				if(!(cin >> i)){
					cout<< "Value is not an int."<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
				}
				if(i < ST1.size()){
					cout<< "min : "<<ST1[i].min()<<endl;;
					cout<< "max : "<<ST1[i].max()<<endl;	
					cout<< "sum : "<<ST1[i].sum()<<endl;
					cout<< "amount : "<<ST1[i].amount()<<endl;
					cout<< "pos : "<<'['<<ST1[i].pos1()<<','<<ST1[i].pos2()<<')'<<endl;
					break;
				}
				cout<< "Index too high."<<endl;
				break;
			case 'O':
				if(ST1 == ST2){
					cout<<"Segment trees are equal"<<endl;
					break;
				}
				cout<<"Segment trees are different."<<endl;
				break;
			case 'L':
				arr.clear();
				break;
			case 'T':
				cout<<arr.size()<<endl;
				break;
			case 'C':{
				segment_tree aux(arr);
				ST1 = aux;
				j = 0;
				break;
			}
			case 'K':
				ST2 = ST1;
				break;
			case 'I':
				cout<< "min : ";
				for(i=0; i<ST2.size();i++){
					cout<<ST2[i].min()<<',';
				}
				cout<<endl;
				cout<< "max : ";
				for(i=0; i<ST2.size();i++){
					cout<<ST2[i].max()<<',';
				}
				cout<<endl;
				cout<< "sum : ";
				for(i=0; i<ST2.size();i++){
					cout<<ST2[i].sum()<<',';
				}
				cout<<endl;
				cout<< "amount : ";
				for(i=0; i<ST2.size();i++){
					cout<<ST2[i].amount()<<',';
				}
				cout<<endl;
				cout<< "pos : ";
				for(i=0; i<ST2.size();i++){
					cout<<'['<<ST2[i].pos1()<<','<<ST2[i].pos2()<<')';
				}
				cout<<endl;
				break;
			case 'P':
				cout<< "min : ";
				for(i=0; i<ST1.size();i++){
					cout<<ST1[i].min()<<',';
				}
				cout<<endl;
				cout<< "max : ";
				for(i=0; i<ST1.size();i++){
					cout<<ST1[i].max()<<',';
				}
				cout<<endl;
				cout<< "sum : ";
				for(i=0; i<ST1.size();i++){
					cout<<ST1[i].sum()<<',';
				}
				cout<<endl;
				cout<< "amount : ";
				for(i=0; i<ST1.size();i++){
					cout<<ST1[i].amount()<<',';
				}
				cout<<endl;
				cout<< "pos : ";
				for(i=0; i<ST1.size();i++){
					cout<<'['<<ST1[i].pos1()<<','<<ST1[i].pos2()<<')';
				}
				cout<<endl;
				break;
			default:
				cout<<"Invalid input("<< c <<")"<<endl;
				break;
		}
	}
}