#ifndef TUPLE_CPP
#define TUPLE_CPP

#include "Tuple.h"

using namespace std;

template <typename T, typename U>
Tuple<T, U>::Tuple(T e1, U e2)
	: e1(e1),
	e2(e2)
{
}

template <typename T, typename U, typename V>
Tuple3<T, U, V>::Tuple3(T e1, U e2, V e3)
	: e1(e1),
	e2(e2),
	e3(e3)
{
}

template <typename T, typename U, typename V, typename X>
Tuple4<T, U, V, X>::Tuple4(T e1, U e2, V e3, X e4)
	: e1(e1),
	e2(e2),
	e3(e3),
	e4(e4)
{
}

template <typename T, typename U, typename V, typename X, typename Y>
Tuple5<T, U, V, X, Y>::Tuple5(T e1, U e2, V e3, X e4, Y e5)
	: e1(e1),
	e2(e2),
	e3(e3),
	e4(e4),
	e5(e5)
{
}

#endif