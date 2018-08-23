#ifndef String_h
#define String_h

#include <memory>

class String
{
	friend std::ostream& operator<<(std::ostream &, const String &);
	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);
public:
	String() :String("") {}
	String(const char *);
	String(const String&);
	String(String &&);
	String& operator=(const String&);
	String & operator=(String &&);
	~String();

	const char* c_str() const { return elements; }
	size_t size() const { return end - elements; }
	size_t length() const { return end - elements + 1; }

private:
	std::pair<char*, char*> alloc_n_copy(const char*, const char*);
	void range_initializer(const char*, const char*);
	void free();

private:
	char *elements;
	char *end;
	std::allocator<char> alloc;
};
std::ostream& operator<<(std::ostream &, const String &);
bool operator==(const String &, const String &);
bool operator!=(const String &, const String &);

#endif