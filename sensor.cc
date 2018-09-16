#include <sensor.h>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

sensor::sensor()
{
	ID=0;
	values=0;
}

sensor::sensor(size_t n)
{
	ID=0;
	values(n);
}

sensor::sensor(string a)
{
	ID=a;
	values=0;
}

sensor::sensor(string a, size_t n)
{
	ID=a;
	values(n);
}

sensor::sensor(const sensor & S)
{	
	ID=S.ID;
	values=S.values;
}

sensor::~sensor()
{
	if(values)
	{
		~values;
	}
}

sensor&
sensor::operator=( const sensor & S)
{
	if ( S.ID == this->ID && S.values==this->values) 
	{
		return *this;
	}
	// Después, cambiamos el tamaño del arreglo si es necesario y procedemos a copiar
	if(S.ID != this->ID)
	{
		ID=S.ID;
	}

	if (S.values != this->values)
	{
		values=S.values;
	}

	return *this;

} 


bool
sensor::operator==( const sensor & S) const
{
	if ( ID != S.ID)
		return false; 
	else{
			if (values != S.values){
				return false;
			}
		}

       	return true;
}
bool
sensor::operator!=( const sensor & ) const
{
	if ( ID == S.ID)
		return false; 
	else{
			if (values == S.values){
				return false;
			}
		}

       	return true;
}
double &
sensor::operator[ ](int pos)
{
	return sensor.values[pos];
}
double const &
sensor::operator[ ](int pos) const
{
	return sensor.values[pos];
}


double
sensor::mean(&sensor S,int pos1, int pos2)
{
	int i, pos2;
	double sum=0;
	for i=pos1,i++,i<=pos2
		sum+=S[i];
	return sum/(pos2-pos1+1);

}

double
sensor::max(&sensor S,int pos1, int pos2)
{
	int i;
	double max=0;
	for i=pos1,i++,i<=pos2
		if S[i]>=max
			max=S[i];
	return max;
}

double
sensor::min(&sensor S,int pos1, int pos2)
{
	int i;
	double min=0;
	for i=pos1,i++,i<=pos2
		if S[i]<min
			min=S[i];
	return min;
}

double
sensor::subsize(&sensor S,int pos1, int pos2)
{
	return pos2-pos1+1;
}


sensor::parse(std::istream &iss)
{
	Array <std::string> *entrada;
	char delim1= ',';
	char delim2='/n';
	int i=0;
	int u=0;

	while iss
		getline(iss, entrada[i], delim2);
		i++;

}
