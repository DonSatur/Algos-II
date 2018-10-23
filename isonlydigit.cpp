#include "isonlydigit.h"

bool 
isonlydigit(const string str){
  size_t length = str.size();
  size_t j=0;

  while(str[j] == ' '){
  	j++;
  }

  for (size_t i = j; i < length; i++){
    if (str[i-1] == ' ' && str[i] != ' '){
    	return false;
    }
    else{
   		if(!isdigit(str[i])){
     		return false;
    	}
  	}

  return true;
}
