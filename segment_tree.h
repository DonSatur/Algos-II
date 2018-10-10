#ifndef _SEGMENT_TREE_H_INCLUDED_
#define _SEGMENT_TREE_H_INCLUDED_

#include <iostream>
#include "data.h"
#include "Array.h"
#include <cmath>

using namespace std;


class segment_tree{
	Array info s_tree_;
	size_t empty_index;		// Indica cual es el primer indice contando de atras hacia adelante

	public:
		segment_tree();
		segment_tree(Array info s_tree);
		segment_tree(const segment_tree & S_TREE);
		~segment_tree();

		void 			push(const info &new_info);
		segment_tree&	operator=( const segment_tree & S_TREE); 
		bool 			operator==( const segment_tree & S_TREE) const; 
		bool 			operator!=( const segment_tree & S_TREE) const; 
		info &			operator[ ]( size_t pos);
		info const &	operator[ ]( size_t pos) const;

};

#endif