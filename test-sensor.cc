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
			    data d(k, s.size());
			    if(s.size() == 1 && first == true){
			    	s[0] = d;
			    	first = false;
			    }
			    else{
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
					cout<<"segment tree: (min;max;sum;amount;[pos1,pos2])"<< endl;
					cout<< prthl;

						cout << s.s_tree()[0].min()<< ";";
						cout << s.s_tree()[0].max()<< ";";
						cout << s.s_tree()[0].sum()<< ";";
						cout << s.s_tree()[0].amount()<< ";";
						cout << "[" << s.s_tree()[0].pos()[0] << ",";
						cout << s.s_tree()[0].pos()[1] << "]";

					for(i=1; i<s.s_tree().size(); i++){
						cout << coma;
						cout << s.s_tree()[i].min()<< ";";
						cout << s.s_tree()[i].max()<< ";";
						cout << s.s_tree()[i].sum()<< ";";
						cout << s.s_tree()[i].amount()<< ";";
						cout << "[" << s.s_tree()[i].pos()[0] << ",";
						cout << s.s_tree()[i].pos()[1] << "]";
						
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

		}
		case 'S': {
			// Create Segment Tree.
			//
			cout<< "create segment tree: "<< endl;
			const char *prthl = "(";
			const char *prthr = ")";
			const char *coma = ",";

			s.create_segment_tree();

			cout<<"segment tree: (min;max;sum;amount;[pos1,pos2])"<< endl;
			cout<< prthl;

				cout << s.s_tree()[0].min()<< ";";
				//cout << s.s_tree()[0].max()<< ";";
//				cout << s.s_tree()[0].sum()<< ";";
//				cout << s.s_tree()[0].amount()<< ";";
//				cout << "[" << s.s_tree()[0].pos()[0] << ",";
//				cout << s.s_tree()[0].pos()[1] << "]";

			for(i=1; i<s.s_tree().size(); i++){
				cout << coma;
				cout << s.s_tree()[i].min()<< ";";
//				cout << s.s_tree()[i].max()<< ";";
//				cout << s.s_tree()[i].sum()<< ";";
//				cout << s.s_tree()[i].amount()<< ";";
//				cout << "[" << s.s_tree()[i].pos()[0] << ",";
//				cout << s.s_tree()[i].pos()[1] << "]";
				
			}
			cout<< prthr;
			cout<< endl;
		}
		case 'I': {
			// Index.
			//
			cin >> i;
			cout << "value in position "<< i<< ": "<< s[i].sum()<< endl;
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
