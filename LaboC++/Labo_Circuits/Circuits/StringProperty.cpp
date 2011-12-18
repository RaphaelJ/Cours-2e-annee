#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "StringProperty.h"

using namespace std;

StringProperty::StringProperty()
{
	this->value = NULL;
}
StringProperty::StringProperty(StringProperty& copy)
{
	*this = copy;
}
StringProperty::StringProperty(const char* value)
{
	this->value = NULL;
	this->set(value);
}
StringProperty::~StringProperty()
{
	if (this->value != NULL) {
		delete [] this->value;
		this->value = NULL;
	}
}

void StringProperty::set(const char* value)
{
	if (this->value != NULL)
		delete [] this->value;
	
	if (value != NULL) {
		this->value = new char[strlen(value) + 1];
		strcpy(this->value, value);
	} else
		this->value = NULL;
}

const char* StringProperty::get() const
{
	return this->value;
}

const char* StringProperty::operator=(const char* value)
{
	this->set(value);
	return this->value;
}

const StringProperty& StringProperty::operator=(const StringProperty& copy)
{
	this->value = NULL;
	
	this->set(copy.get());
}

StringProperty::operator const char*() const
{
	return this->get();
}
