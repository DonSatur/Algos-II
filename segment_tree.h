#ifndef _SEGMENT_TREE_H_INCLUDED_
#define _SEGMENT_TREE_H_INCLUDED_

#include <iostream>
#include "data.h"
#include "sensor.h"
#include "Array.h"
#include <cmath>

using namespace std;


class segment_tree{
	Array data s_tree_;
	size_t empty_index_;		// Indica cual es el primer indice contando de atras hacia adelante

	public:
		segment_tree();
		segment_tree(size_t n);
		segment_tree(Array data arr);
		segment_tree(const segment_tree & S_TREE);
		~segment_tree();

		size_t			empty_index();
		size_t			size();

		void 			push(const data &new_data);		
		sensor&			operator=( const sensor & S);
		data &			operator[ ]( size_t pos);
		data const &	operator[ ]( size_t pos) const;

		void 			process_sensor(segment_tree & S_TREE, sensor & s);

};


// Constructor por defecto
segment_tree::segment_tree(){
	this->s_tree_ = ARRAY_DEFAULT_SIZE ;
	this->empty_index = s_tree_.size() - 1;
}


// Constructor por tamano del arreglo
segment_tree::segment_tree(size_t n){
	Array <data> s_aux(n);
	this->s_tree_ = s_aux;
	this->empty_index_ = n - 1;
}


// Constructor por copia de arreglo
segment_tree::segment_tree(Array <data> arr){
	size_t i, j = arr.size();
	segment_tree s_aux(2 * arr.size() - 1);

	for (i = s_aux.size() - 1; j>0; i--){
		s_aux[i] = arr[j-1];
		j--;
	}

	this->s_tree_ = s_aux;
	this->empty_index = arr.size() - 2;

}


// Constructor por puntero
segment_tree::segment_tree(const segment_tree & S_TREE){
	this->s_tree_ = S_TREE.s_tree_;
	this->empty_index = S_TREE.empty_index-;
}


// Destructor
segment_tree::~segment_tree(){

}


// Devuelve el valor de empty_index_
size_t
segment_tree::empty_index(){
	return this->empty_index_;
}


size_t
segment_tree::size(){
	return s_tree_.size();
}


void
segment_tree::push(const data &new_data){
	this->s_tree_.push(new_data);
}
		

segment_tree&
segment_tree::operator=( const segment_tree & S_TREE)
{
	if ( S_TREE.s_tree_ == this->s_tree_ && S_TREE.empty_index_ == this->empty_index_) 
	{
		return *this;
	}
	// Después, cambiamos el tamaño del arreglo si es necesario y procedemos a copiar
	if(S_TREE.s_tree_ != this->s_tree_)
	{
		this->s_tree_=S_TREE.s_tree_;
	}

	if (S_TREE.empty_index_ != this->empty_index_)
	{
		this->empty_index_=S_TREE.empty_index_;
	}

	return *this;

} 


data &
segment_tree::operator[ ]( size_t pos){
	return s_tree_[pos];

}

data const &
segment_tree::operator[ ]( size_t pos) const{
	return s_tree_[pos];
}


// Procesamiento de un sensor para convertirlo en segment_tree

void 			
segment_tree::process_sensor(segment_tree & S_TREE, sensor & s){
	size_t i;
	Array data i_arr(s.size());

	for (i = 0; i < s.size(); i++){
		data i_aux(s[i]);			// Convierto los objetos data en objetos data y luego
		i_arr[i] = i_aux;			// creo el arreglo con toda la datarmacion

	}
	segment_tree s_tree_aux(i_arr);	// Creo el segment_tree con el arreglo original convertido
	S_TREE = s_tree_aux;			// en un arreglo de objetos data

	for (i = S_TREE.size(); i > 0; i-=2){
		data i_aux(S_TREE[i-1], S_TREE[i]);
		S_TREE[empty_index_] = i_aux;
	}

}

#endif