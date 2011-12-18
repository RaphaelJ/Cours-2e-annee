#ifndef EXCEPTIONBASE_H
#define EXCEPTIONBASE_H

#include "StringProperty.h"

class ExceptionBase {
	private:
		StringProperty message;
	
	public:
		ExceptionBase();
		ExceptionBase(const ExceptionBase& except);
		ExceptionBase(const char* message);
		
		~ExceptionBase();
		
		void setMessage(const char* message);
		
		const char* getMessage() const;
		
		ExceptionBase& operator=(const ExceptionBase& eb2);
};

#endif