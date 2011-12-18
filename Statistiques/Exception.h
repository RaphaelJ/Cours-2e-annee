#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

class Exception {
	private:
		string message;
	
	public:
		Exception();
		Exception(const char* message)
		{
			this->message = message;
		}
		
		const char* getMessage() const
		{
			return this->message.c_str();
		}
		
		friend ostream& operator<<(ostream& output, const Exception& e)
		{
			output << "Exception: ";
			if (e.getMessage() != NULL)
				output << e.getMessage() << endl;
			
			return output;
		}
};

#endif