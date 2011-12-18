#ifndef TUPLE_H
#define TUPLE_H

template <typename T, typename U>
struct Tuple {
	T e1;
	U e2;
	
	Tuple(T e1, U e2);
};

// Unable to over
template <typename T, typename U, typename V>
struct Tuple3 {
	T e1;
	U e2;
	V e3;
	
	Tuple3(T e1, U e2, V e3);
};

template <typename T, typename U, typename V, typename X>
struct Tuple4 {
	T e1;
	U e2;
	V e3;
	X e4;
	
	Tuple4(T e1, U e2, V e3, X e4);
};

template <typename T, typename U, typename V, typename X, typename Y>
struct Tuple5 {
	T e1;
	U e2;
	V e3;
	X e4;
	Y e5;
	
	Tuple5(T e1, U e2, V e3, X e4, Y e5);
};

// Templates
#include "Tuple.cpp"

#endif
