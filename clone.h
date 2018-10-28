// clone.h - Implementación del método de clonación de objetos. 
//
// La idea es muy simple: ejercitar los casos de uso de los constructores
// de copia y operadores de asignación. Originalmente, esta función estaba
// ubicada en los .cc, pero se movió a un .h para dejar tranquilo al
// compilador de Intel.
//
// Leandro Santi, $Date: 2018/09/27 02:03:37 $.

#ifndef _CLONE_H_INCLUDED_
#define _CLONE_H_INCLUDED_

template <typename T>
T clone(T const t)
{
	return t;
}

#endif
