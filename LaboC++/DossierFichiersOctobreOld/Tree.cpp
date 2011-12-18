#ifndef TREE_CPP
#define TREE_CPP

#include <stdio.h>
#include <ostream>

#include "Tree.h"

using namespace std;

template <typename T, typename U>
Tree<T, U>::Tree(const Tree<T, U>& tree) // private
{
}
template <typename T, typename U>
Tree<T, U>::Tree(COMPARATOR_FCT comparator)
{
	this->root = NULL;
	
	this->comparator = comparator;
}

template <typename T, typename U>
Tree<T, U>::~Tree()
{
	delete root;
}

template <typename T, typename U>
void Tree<T, U>::add(T identifier, U data)
{
	Node<T, U>::treeAdd(&(this->root), identifier, data, comparator);
}

template <typename T, typename U>
Tuple<T, U> Tree<T, U>::remove(const T identifier)
{
	return Node<T, U>::treeRemove(&(this->root), identifier, comparator);
}

template <typename T, typename U>
Tuple<T, U> Tree<T, U>::search(const T identifier)
{
	return Node<T, U>::treeSearch(this->root, identifier, comparator);
}

template <typename T, typename U>
template <typename V>
bool Tree<T, U>::fold(bool(*f)(V& accumulator, const Tuple<T&, U&> node), V& init)
{
	return Node<T, U>::treeFold(this->root, f, init);
}

template <typename T, typename U>
Node<T, U>::Node(T identifier, U data)
	: identifier(identifier),
	data(data)
{
	this->left = NULL;
	this->right = NULL;
}

template <typename T, typename U>
Node<T, U>::~Node()
{
	if (this->left != NULL)
		delete left;
	
	if (this->right != NULL)
		delete right;
}

template <typename T, typename U>
void Node<T, U>::treeAdd(Node<T, U>** tree, Node<T, U>* node,
                         COMPARATOR_FCT comparator)
{
	// TODO: Balanced tree
	if (*tree != NULL) { // insert in sub-tree
		cerr << "Subtree " << node->identifier << " " << (*tree)->identifier << endl;
		int cmp = comparator(node->identifier, (*tree)->identifier);
		
		cerr << "Compared : " << cmp << endl;
		if (cmp == 0)
			throw typename Tree<T, U>::KeyExists();
		else if (cmp < 0) { // left

			cerr << "left" << endl;
			Node<T, U>::treeAdd(&((*tree)->left), node, comparator);
		} else { // right

			cerr << "right" << endl;
			Node<T, U>::treeAdd(&((*tree)->right), node, comparator);
		}
	} else // insert elem here
		*tree = node;
}
template <typename T, typename U>
void Node<T, U>::treeAdd(Node<T, U>** tree, T identifier, U data,
                         COMPARATOR_FCT comparator)
{
	Node<T, U>* node = new Node<T, U>(identifier, data);
	try {
		Node<T, U>::treeAdd(tree, node, comparator);
	} catch (typename Tree<T, U>::KeyExists except) {
		delete node;
		throw except;
	} catch (...) { // TODO: re-throw every exception
		delete node;
	}
}

template <typename T, typename U>
Tuple<T, U> Node<T, U>::treeRemove(Node<T, U>** tree, const T identifier,
                                   COMPARATOR_FCT comparator)
{
	if (*tree == NULL) // Key doesn't exists
		throw typename Tree<T, U>::KeyError();
	else {
		cerr << "Start Remove " << endl;
		cerr << identifier << " " << (*tree)->identifier  << endl;
		int cmp = comparator(identifier, (*tree)->identifier);
		cerr << "Stop compare" << endl;
		if (cmp == 0) { // find key
			cerr << "Find key" << endl;
			// Copy old node's values
			Tuple<T, U> nodeValues((*tree)->identifier,
			                         (*tree)->data);
			Node<T, U>* oldNode = *tree;
			
			if ((*tree)->left == NULL) { // left is empty, replace by right
				cerr << "Remove right" << endl;
				*tree = (*tree)->right;
			} else if ((*tree)->right == NULL){ // right is empty, replace by left
				*tree = (*tree)->left;
				cerr << "Remove left" << endl;
			} else { // Right & left trees are not empty
				cerr << "Remove all" << endl;
				Node<T, U>* leftTree = (*tree)->left;
				
				// Replace the current element by its right tree
				// Add the left tree to the ex-right tree
				*tree = (*tree)->right;
				
				Node<T, U>::treeAdd(tree, leftTree, comparator);
				// TODO: choose the max left element to replace the
				// current element instead.
			}
			
			oldNode->left = NULL;
			oldNode->right = NULL;
			delete oldNode;
			
			return nodeValues;
		} else if (cmp < 0) { // left
			cerr << "Go left" << endl;
			return Node<T, U>::treeRemove(&((*tree)->left), identifier,
			                              comparator);
		} else { // right
			cerr << "Go right" << endl;
			return Node<T, U>::treeRemove(&((*tree)->right), identifier,
			                              comparator);
		}
	}
}

template <typename T, typename U>
Tuple<T, U> Node<T, U>::treeSearch(Node<T, U>* tree, const T identifier,
                               COMPARATOR_FCT comparator)
{
	if (tree == NULL) // Key doesn't exists
		throw typename Tree<T, U>::KeyError();
	else {
		int cmp = comparator(identifier, tree->identifier);
		if (cmp == 0) // find key
			return Tuple<T, U>(tree->identifier, tree->data);
		else if (cmp < 0) {
			return Node<T, U>::treeSearch(tree->left, identifier,
			                              comparator);
		} else {
			return Node<T, U>::treeSearch(tree->right, identifier,
			                              comparator);
		}
	}
}

template <typename T, typename U>
template <typename V> 
bool Node<T, U>::treeFold(Node<T, U>* tree, bool(*f)(V& accumulator, const Tuple<T&, U&> node),
                       V& init)
{
	if (tree == NULL)
		return true;
	else {
		const Tuple<T&, U&> node(tree->identifier, tree->data);
		
		return Node<T, U>::treeFold(tree->left, f, init)
		    && f(init, node)
		    && Node<T, U>::treeFold(tree->right, f, init);
	}
}

#endif