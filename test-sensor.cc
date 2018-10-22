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
	bool first = true, first1 = true;
	string str;
	sensor s;
	sensor aux;
	sensor s_empty;
	cout << "Clone (C), Empty (E), Length (L), Add (A), Print (P), Name (N), Compare (M), Index (I), Create Segment Tree (S)"<< endl;
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
			// Length.
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

			cout << s.id();
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
			// Sensor name.
			//
			cout<< "sensor name/id: ";
			cin >> str;
			s.id() = str;
			break;
		}
		case 'M': {
			// Compare.
			//

			cout<< "compare sensors: "<< endl;
			cout<< "enter ID: ";
			cin>>str;
			aux.id() = str;
			cout<< "enter sensor length: ";
			cin >> i;
			for(size_t j = 0; j<i; j++){
				cout<<"enter a measurment value: ";
				cin>> k;
				data d(k, j);
				if(aux.size() == 1 && first1 == true){
					aux[0] = d;
					first = false;
				}
				else{
					aux.push(d);
				}
				cout<<endl;
			}
			aux.create_segment_tree();
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
