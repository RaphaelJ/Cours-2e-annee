#ifndef NODE_H
#define NODE_H

#include <ostream>

using namespace std;

template <typename U>
struct Node;

template <typename T>
ostream& operator<<(ostream& output, const Node<T>& node)
{
	output << node.item;
	
	if (node.next != NULL)
		return output << " - " << *node.next;
	else
		return output << endl;
}

template <typename T>
struct Node {
	T item;
	Node<T>* next;
	
	Node()
	{
		this->next = NULL;
	}
	
	Node(const Node<T>& list)
	{
		*this = list;
	}
	
	~Node()
	{
		if (this->next != NULL)
			delete this->next; // Recursive delete
	}
	
	int size() const 
	{
		return this->size(0);
	}
	
	int size(int acc) const
	{
		if (this->next == NULL)
			return acc + 1;
		else 
			return this->next->size(acc + 1);
	}
	
	// Retourne une nouvelle liste avec le nouveau
	// noeud en premier.
	Node<T>* ajouterAvant(T item)
	{
		Node<T>* newNode = new Node<T>();
		newNode->item = item;
		newNode->next = this;
		
		return newNode;
	}
	
	Node<T>* ajouterApres(T item)
	{
		Node<T>* newNode = new Node<T>();
		newNode->item = item;
		newNode->next = NULL;
	
		this->next = newNode;
		
		return this;
	}
	
	Node<T>* ajouterCroissant(T item)
	{
		if (item <= this->item) // Ajoute avant si plus petit
			return this->ajouterAvant(item); // Noeud changé
		else if (this->next != NULL) { // Ajoute dans les éléments suivants
			this->next = this->next->ajouterCroissant(item);
			return this; // Noeud inchangé
		} else { // Fin de la liste (ajoute après)
			return this->ajouterApres(item); // Noeud inchangé
		}
	}
	
	Node<T>* ajouterDecroissant(T item)
	{
		if (item >= this->item) // Ajoute avant si plus grand
			return this->ajouterAvant(item); // Noeud changé
		else if (this->next != NULL) { // Ajoute dans les éléments suivants
			this->next = this->next->ajouterDecroissant(item);
			return this; // Noeud inchangé
		} else { // Fin de la liste (ajoute après)
			return this->ajouterApres(item); // Noeud inchangé
		}
	}
	
	T retirerSuivant()
	{
		Node<T>* oldNode = this->next;
		this->next = oldNode->next;
		
		T item = oldNode->item;
		oldNode->next = NULL; // Disable recursive delete
		delete oldNode;
		return item;
	}
	
	Node<T>* retourner()
	{
		return this->retourner(NULL); // Le début devient la fin
	}
	
	Node<T>* retourner(Node<T>* nouvelleListe)
	{
		Node<T>* oldNext = this->next;
		this->next = nouvelleListe; // Rajoute le noeud en cours au début de le nv liste
		
		if (oldNext != NULL) // Rajoute l'ancien suivant devant
			return oldNext->retourner(this);
		else // Fin de l'ancienne liste (et nouveau début)
			return this;
		
		// ??? !! ???
	}
	
	friend ostream& operator<< <>(ostream& output, const Node<T>& node);
	
	Node<T>& operator=(const Node<T>& list)
	{
		this->item = list.item;
		if (list.next != NULL) { // Si élements suivants
			if (this->next == NULL) // Nouvelle liste plus longue
				this->next = new Node<T>(); // Rajoute un element
			
			*(this->next) = *(list.next); // Recursive copy
		} else if (this->next != NULL) { // Nouvelle liste plus courte
			delete this->next; // Recursive delete
			this->next = NULL;
		}
		
		return *this;
	}
};

#endif