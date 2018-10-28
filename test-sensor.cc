#include <clone.h>
#include "sensor.h"
#include <iostream>

using namespace std;

int
main()
{
	size_t i;
	double k;
	char c;
	bool first = true, first1;
	string str;
	sensor s;
	sensor s_empty;
	cout << "Clone (C), Empty (E), Sensor Length (L), Add (A), Print (P), New (N), Compare (M), Index (I), Create Segment Tree (S)"<< endl;
	while (cin >> c) {
		switch (c) {
		case 'C':
			// Clone.
			// 
			cout << "clone";
			cout << endl;
			s = clone(s);
			break;
		case 'E':
			cout << "empty";
			cout << endl;
			s = s_empty;
			first = true;
			first1 = true;
			break;
		case 'L':
			// Sensor Length.
			// 
			cout << "sensor length: ";
			cout << s.size();
			cout << endl;
			break;
		case 'A':
			// Add.
			// 
			if (cin >> k) {
				cout << "add: ";
				cout << k;
			    cout << endl;
			    if(s.size() == 1 && first == true){
			    	data d(k, s.size()-1);
			    	s[0] = d;
			    	first = false;
			    }
			    else{
			    	data d(k, s.size());
					s.push(d);
				}
			}
			break;
		case 'P': {
			// Print.
			//
			const char *prthl = "(";
			const char *prthr = ")";
			const char *coma = ",";

			if(s.id()=="\0"){
				cout<<"no id"<<endl;
			}
			else{
				cout << "id: " << s.id() <<endl;
			}
			if (s.size() == 1 && first==true){
				cout << "empty" << endl;
			}
			else{
				cout<< "mediciones: ";
				cout << prthl;
				cout << s[0].sum();
				for(i=1; i<s.size(); i++) {
					cout << coma;
					cout << s[i].sum();
				}
				cout<<prthr;
				cout << endl;
				if(s.s_tree().size() == 1){
					cout<< "no segment tree"<<endl;
				}
				else{
					cout<<"segment tree:"<< endl;
					
					cout<< "minimum: ";
					cout<< prthl;
					cout << s.s_tree()[0].min();
					for(i=1; i<s.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << s.s_tree()[i].min();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "maximum: ";
					cout<< prthl;
					cout << s.s_tree()[0].max();
					for(i=1; i<s.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << s.s_tree()[i].max();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "sum: ";
					cout<< prthl;
					cout << s.s_tree()[0].sum();
					for(i=1; i<s.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << s.s_tree()[i].sum();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "amount: ";
					cout<< prthl;
					cout << s.s_tree()[0].amount();
					for(i=1; i<s.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << s.s_tree()[i].amount();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "positions: ";
					cout<< prthl;
					cout << "[" << s.s_tree()[0].pos1()<< coma;
					cout << s.s_tree()[0].pos2() << "]";
					for(i=1; i<s.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << "[" << s.s_tree()[i].pos1()<< coma;
						cout << s.s_tree()[i].pos2() << "]";
					}
					cout<< prthr;
					cout<< endl;
				}
			}
			break;
		}
		
		case 'N': {
			// New sensor.
			//
			cout<< "enter the sensor name: ";
			cin >> str;
			sensor aux(str);
			s = aux;
			break;
		}
		
		case 'M': {
			// Compare.
			//
			first1 = true;
			const char *prthl = "(";
			const char *prthr = ")";
			const char *coma = ",";


			cout<< "compare sensors: "<< endl;
			cout<< "enter sensor name: ";
			cin>>str;
			sensor aux(str);
			cout<< "enter sensor length: ";
			cin >> i;
			for(size_t j = 0; j<i; j++){
				cout<<"enter a measurement value: ";
				cin>> k;
				data d(k,j);
				if(aux.size() == 1 && first1 == true){
					aux[0] = d;
					first1 = false;
				}
				else{
					aux.push(d);
				}
			}
			cout<< "do you want segment tree? (yes:0, no:1): ";
			cin>> i;
			if(i == 0){
				aux.create_segment_tree();
			}


			if(aux.id()=="\0"){
				cout<<"no id"<<endl;
			}
			else{
				cout << "id: " << aux.id() <<endl;
			}
			if (aux.size() == 1 && first==true){
				cout << "empty" << endl;
			}
			else{
				cout<< "mediciones: ";
				cout << prthl;
				cout << aux[0].sum();
				for(i=1; i<aux.size(); i++) {
					cout << coma;
					cout << aux[i].sum();
				}
				cout<<prthr;
				cout << endl;
				if(aux.s_tree().size() == 1){
					cout<< "no segment tree"<<endl;
				}
				else{
					cout<<"segment tree:"<< endl;
					
					cout<< "minimum: ";
					cout<< prthl;
					cout << aux.s_tree()[0].min();
					for(i=1; i<aux.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << aux.s_tree()[i].min();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "maximum: ";
					cout<< prthl;
					cout << aux.s_tree()[0].max();
					for(i=1; i<aux.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << aux.s_tree()[i].max();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "sum: ";
					cout<< prthl;
					cout << aux.s_tree()[0].sum();
					for(i=1; i<aux.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << aux.s_tree()[i].sum();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "amount: ";
					cout<< prthl;
					cout << aux.s_tree()[0].amount();
					for(i=1; i<aux.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << aux.s_tree()[i].amount();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "positions: ";
					cout<< prthl;
					cout << "[" << aux.s_tree()[0].pos1()<< coma;
					cout << aux.s_tree()[0].pos2() << "]";
					for(i=1; i<aux.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << "[" << aux.s_tree()[i].pos1()<< coma;
						cout << aux.s_tree()[i].pos2() << "]";
					}
					cout<< prthr;
					cout<< endl;
				}
			}
			





			if(aux == s){
				cout<< "equal" << endl;
			}
			else{
				cout<< "not equal"<< endl;
			}
			break;

		}
		case 'S': {
			// Create Segment Tree.
			//
			cout<< "create segment tree: "<< endl;
			const char *prthl = "(";
			const char *prthr = ")";
			const char *coma = ",";

			s.create_segment_tree();

			cout<<"segment tree:"<< endl;
					
					cout<< "minimum: ";
					cout<< prthl;
					cout << s.s_tree()[0].min();
					for(i=1; i<s.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << s.s_tree()[i].min();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "maximum: ";
					cout<< prthl;
					cout << s.s_tree()[0].max();
					for(i=1; i<s.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << s.s_tree()[i].max();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "sum: ";
					cout<< prthl;
					cout << s.s_tree()[0].sum();
					for(i=1; i<s.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << s.s_tree()[i].sum();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "amount: ";
					cout<< prthl;
					cout << s.s_tree()[0].amount();
					for(i=1; i<s.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << s.s_tree()[i].amount();
					}
					cout<< prthr;
					cout<< endl;

					cout<< "positions: ";
					cout<< prthl;
					cout << "[" << s.s_tree()[0].pos1()<< coma;
					cout << s.s_tree()[0].pos2() << "]";
					for(i=1; i<s.s_tree().size(); i++){
						cout << " " << coma << " ";
						cout << "[" << s.s_tree()[i].pos1()<< coma;
						cout << s.s_tree()[i].pos2() << "]";
					}
					cout<< prthr;
					cout<< endl;
					break;
		}
		case 'I': {
			// Index.
			//
			cin >> i;
			cout << "value in position "<< i<< ": "<< s[i-1].sum()<< endl;
			break;
		}
		default:
			cout << "error: unknown command (";
			cout << c;
			cout << ")";
			cout << endl;
			break;
		}
	}
}
