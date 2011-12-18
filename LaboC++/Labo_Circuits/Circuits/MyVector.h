#ifndef MYVECTOR_H
#define MYVECTOR_H

#include "ExceptionBase.h"

template <typename T>
class MyVector;

template <typename T>
ostream& operator<<(ostream& stream, const MyVector<T>& v);

template <typename T>
class MyVector {
	private:
		template <typename U>
		class Element {
		private:
			bool free;
			U item;
			
		public:
			Element()
			{
				this->free = true;
			}
			Element(T item)
			{
				this->setItem(item);
			}
			
			void setItem(T item)
			{
				this->item = item;
				this->free = false;
			}
			
			U getItem() const
			{
				return this->item;
			}
			bool getFree() const
			{
				return this->free;
			}
			
			void remove()
			{
				this->free = true;
			}
			
			U operator=(T value)
			{
				this->setItem(value);
			}
			
			operator U() const
			{
				return this->getItem();
			}
		};
		
		Element<T>* vector;
		int size;
	
		MyVector();
		
		void initVector(const int size);
	public:
		MyVector(const MyVector& vector);
		MyVector(const int size);
		
		~MyVector();
		
		void setElement(const int index, T value);
		T retireElement(const int index);
		
		int getSize() const;
		T getElement(const int index) const;
		
		bool indiceValide(const int index) const;
		bool estOccupe(const int index) const;

		void Affiche() const;
		void affiche() const;
		
		MyVector& operator=(const MyVector& v2);
		MyVector& operator+(T value);
		
		friend ostream& operator<< <>(ostream& output, const MyVector<T>& v);
		
		class InvalidIndexException : ExceptionBase {
		public:
			InvalidIndexException()
			{
				this->setMessage("Index invalide");
			}
		};
		
		class NoValueException : ExceptionBase {
		public:
			NoValueException()
			{
				this->setMessage("L'élement demandé n'a pas de valeur");
			}
		};
};

#include "MyVector.cpp" // template's code

#endif