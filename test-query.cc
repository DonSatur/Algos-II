#include <clone.h>
#include "query.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "cmdline.h"

using namespace std;

static fstream file;		// Flujo de archivo de entrada correspondiente a los valores y IDs de cada sensor
static istream *diss;		// Flujo de entrada que toma los valores que posee difs
static bool enable_stree = false;


int
main()
{
	size_t id=0, pos1, pos2;
	bool not_end;
	char c;
	string str;
	sensornet S (enable_stree);
	query q;
	query q_empty;
	cout << "Clone (C), Empty (E), Print (P), New Query(N), Create Sensornet From File (S), Compare (M)"<< endl;
	while (cin >> c) {
		switch (c) {
		case 'C':
			// Clone.
			// 
			cout << "clone";
			cout << endl;
			q = clone(q);
			break;
		case 'E':
			cout << "empty";
			cout << endl;
			q = q_empty;
			break;
		case 'P': {
			// Print.
			//

			cout<< "min: " << q.min()<< endl;
			cout<< "max: " << q.max()<< endl;
			cout<< "mean: " << q.mean()<< endl;
			cout<< "amount: " << q.amount()<< endl;

			break;
		}
		case 'N': {
			// New query.
			//
			cout<< "enter the query: ";
			getline(cin,str);
			stringstream str_st(str);
			read_query(str_st, cout, S, id, pos1, pos2, not_end);
			if(not_end){
				q.process_data(S, id, pos1, pos2);				
				cout << q;
			}

			cin.clear();
			cin.ignore(1000000,'\n');

			break;
		}
		case 'M': {
			// Compare.
			//
			query aux;
			cout<< "enter the query: ";
			getline(cin, str);
			cout<< str<<endl;
			stringstream str_st(str);
			read_query(str_st, cout, S, id, pos1, pos2, not_end);
			if(not_end){
				aux.process_data(S, id, pos1, pos2);				
				cout << aux;
			}

			if(q == aux){
				cout << "equal" << endl;
			}
			else{
				cout << "not equal" << endl;
			}

			cin.clear();
			cin.ignore(1000000,'\n');

			break;

		}
		case 'S': {
			// Create Sensornet From File.
			//

			cout<<"enter the name of the file: ";
				cin >> str;
				if(str.empty()){
					cout<<"error reading name"<<endl;
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
				read_file(*diss,S);
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
