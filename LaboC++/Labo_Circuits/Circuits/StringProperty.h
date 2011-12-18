#ifndef STRINGPROPERTY_H
#define STRINGPROPERTY_H

using namespace std;

class StringProperty {
	private:
		char* value;
	public:
		StringProperty();
		StringProperty(StringProperty& copy);
		StringProperty(const char* value);
		
		~StringProperty();
		
		virtual void set(const char* value);
		virtual const char* get() const;
		
		const char* operator=(const char* value); // char* to StringProperty
		const StringProperty& operator=(const StringProperty& copy);
		
		operator const char*() const; // StringProperty to char*
};

#endif