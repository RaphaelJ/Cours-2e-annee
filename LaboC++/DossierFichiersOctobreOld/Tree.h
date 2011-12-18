#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <ostream>

#include "Tuple.h"

template <typename T, typename U>
class Node;

template <typename T, typename U>
class Tree {
	public:
		typedef int(*COMPARATOR_FCT)(const T i1, const T i2);
		// http://stackoverflow.com/questions/26151/template-typedefs-whats-your-work-around
	
	private:
		Node<T, U>* root;
		
		Tree<T, U>::COMPARATOR_FCT comparator;
		
		Tree();
		Tree(const Tree<T, U>& tree);
	public:
		Tree(COMPARATOR_FCT comparator);
		~Tree();
		
		void add(T identifier, U data);
		Tuple<T, U> remove(const T identifier);
		Tuple<T, U> search(const T identifier);
		
		template <typename V>
		bool fold(bool(*f)(V& accumulator, const Tuple<T&, U&> node), V& init);
		
		// Exceptions
		class KeyExists {
		};
		class KeyError { // Key doesn't exists
		};
};

template <typename T, typename U>
struct Node {
	// Can't access to Tree<T, U>::COMPARATOR_FCT
	typedef int(*COMPARATOR_FCT)(const T i1, const T i2);
	
	T identifier;
	U data;
	
	Node<T, U>* left;
	Node<T, U>* right;
	
	Node(T identifier, U data);
	
	~Node();
	
	static void treeAdd(Node<T, U>** tree, Node<T, U>* node,
	                    COMPARATOR_FCT comparator);
	static void treeAdd(Node<T, U>** tree, T identifier, U data,
	                    COMPARATOR_FCT comparator);
	static Tuple<T, U> treeRemove(Node<T, U>** tree, const T identifier,
	                              COMPARATOR_FCT comparator);
	static Tuple<T, U> treeSearch(Node<T, U>* tree, const T identifier,
	                              COMPARATOR_FCT comparator);
	
	template <typename V>
	static bool treeFold(Node<T, U>* tree, bool(*f)(V& accumulator, const Tuple<T&, U&> node),
	                     V& init);
	// http://publib.boulder.ibm.com/infocenter/macxhelp/v6v81/index.jsp?topic=%2Fcom.ibm.vacpp6m.doc%2Flanguage%2Fref%2Fclrc16explicit_spec_members.htm
};

// Templates
#include "Tree.cpp"

#endif
