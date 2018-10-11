#ifndef _SEGMENT_TREE_H_INCLUDED_
#define _SEGMENT_TREE_H_INCLUDED_

#include <iostream>
#include "data.h"
#include "sensor.h"
#include "Array.h"
#include <cmath>

using namespace std;


class segment_tree{
	Array info s_tree_;
	size_t empty_index_;		// Indica cual es el primer indice contando de atras hacia adelante

	public:
		segment_tree();
		segment_tree(size_t n);
		segment_tree(Array info s_tree);
		segment_tree(const segment_tree & S_TREE);
		~segment_tree();

		size_t			empty_index();
		size_t			size();

		void 			push(const info &new_info);		
		sensor&			operator=( const sensor & S);
		info &			operator[ ]( size_t pos);
		info const &	operator[ ]( size_t pos) const;

		void 			process_sensor(segment_tree & S_TREE, sensor & s);

};


// Constructor por defecto
segment_tree::segment_tree(){
	this->s_tree_ = ARRAY_DEFAULT_SIZE ;
	this->empty_index = s_tree_.size() - 1;
}


// Constructor por tamano del arreglo
segment_tree::segment_tree(size_t n){
	Array info s_aux(n);
	this->s_tree_ = s_aux;
	this->empty_index_ = n - 1;
}


// Constructor por copia de arreglo
segment_tree::segment_tree(Array info s_tree){
	size_t j = s_tree.size() - 1;

	Array info s_aux(2 * s_tree.size() - 1);
	for (size_t i = s_aux.size() - 1; i--){
		info i_aux(s_tree[j])
		s_aux[i] == i_aux;
	}

	this->s_tree_ = s_aux;
	this->empty_index = s_tree.size() - 1;

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
segment_tree::push(const info &new_info){
	this->s_tree_.push(new_info);
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


info &
segment_tree::operator[ ]( size_t pos){
	return s_tree_[pos];

}

info const &
segment_tree::operator[ ]( size_t pos) const{
	return s_tree_[pos];
}


// Procesamiento de un sensor para convertirlo en segment_tree

void 			
segment_tree::process_sensor(segment_tree & S_TREE, sensor & s){
	size_t i;
	Array info i_arr(s.size());

	for (i = 0; i < s.size(); i++){
		info i_aux(s[i]);			// Convierto los objetos data en objetos info y luego
		i_arr[i] = i_aux;			// creo el arreglo con toda la informacion

	}
	segment_tree s_tree_aux(i_arr);	// Creo el segment_tree con el arreglo original convertido
	S_TREE = s_tree_aux;			// en un arreglo de objetos info

	for (i = S_TREE.size(); i > 0; i-=2){
		info i_aux(S_TREE[i-1], S_TREE[i]);
		S_TREE[empty_index_] = i_aux;
	}

}

#endif