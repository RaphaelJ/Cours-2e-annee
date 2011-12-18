#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ExceptionBase.h"

using namespace std;

ExceptionBase::ExceptionBase()
{
	this->setMessage(NULL);
}
ExceptionBase::ExceptionBase(const ExceptionBase& except)
{
	*this = except;
}
ExceptionBase::ExceptionBase(const char* message)
{
	this->setMessage(message);
}

ExceptionBase::~ExceptionBase()
{

}

void ExceptionBase::setMessage(const char* message)
{
	this->message = message;
}

const char* ExceptionBase::getMessage() const
{
	return this->message;
}

ExceptionBase& ExceptionBase::operator=(const ExceptionBase& eb2)
{
	this->setMessage(eb2.getMessage());
	return *this;
}