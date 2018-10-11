#ifndef _SEGMENT_TREE_H_INCLUDED_
#define _SEGMENT_TREE_H_INCLUDED_

#include <iostream>
#include "data.h"
#include "Array.h"
#include <cmath>

using namespace std;


class segment_tree{
	Array info s_tree_;
	size_t empty_index_;		// Indica cual es el primer indice contando de atras hacia adelante

	public:
		segment_tree();
		segment_tree(Array info s_tree);
		segment_tree(const segment_tree & S_TREE);
		~segment_tree();

		void 			push(const info &new_info);
		info &			operator[ ]( size_t pos);
		info const &	operator[ ]( size_t pos) const;

};


// Constructor por defecto
segment_tree::segment_tree(){
	this->s_tree_ = ARRAY_DEFAULT_SIZE ;
	this->empty_index = s_tree_.size() - 1;
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



void
segment_tree::push(const info &new_info){
	this->s_tree_.push(new_info);
}
		


info &
segment_tree::operator[ ]( size_t pos){
	return s_tree_[pos];

}
info const &
segment_tree::operator[ ]( size_t pos) const{
	return s_tree_[pos];
}

#endif