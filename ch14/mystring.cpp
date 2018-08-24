#include "mystring.h"

#include <algorithm>
#include <iostream>

std::pair<char*, char*>
String::alloc_n_copy(const char* b, const char* e)
{
	auto str = alloc.allocate(e - b);
	return{ str, std::uninitialized_copy(b, e, str) };
}

void String::range_initializer(const char* first, const char* last)
{
	auto newstr = alloc_n_copy(first, last);
	elements = newstr.first;
	end = newstr.second;
}

String::String(const char* s)
{
	char *s1 = const_cast<char*>(s);
	while (*s1)
	{
		++s1;
	}
	range_initializer(s, ++s1);
}

String::String(String && s) {
	elements = std::move(s.elements), s.elements = nullptr;
	end = std::move(s.end), s.end = nullptr;
}

String & String::operator=(String && s) {
	if (this != &s) {
		free();
		elements = std::move(s.elements);
		end = std::move(s.end);
		s.elements = s.end = nullptr;
	}
	return *this;

}

String::String(const String& rhs)
{
	range_initializer(rhs.elements, rhs.end);
	std::cout << "copy constructor" << std::endl;
}

void String::free()
{
	if (elements)
	{
		std::for_each(elements, end, [this](char &c) { alloc.destroy(&c); });
		alloc.deallocate(elements, end - elements);
	}
}

String::~String()
{
	free();
}

String& String::operator=(const String& rhs)
{
	auto newstr = alloc_n_copy(rhs.elements, rhs.end);
	free();
	elements = newstr.first;
	end = newstr.second;
	std::cout << "copy-assignment" << std::endl;
	return *this;
}
std::ostream & operator<<(std::ostream & os,const String& str)
{
	char *c = const_cast<char*>(str.c_str());
	while(c != str.end) {
		os << *c++;
	}
	return os;
}

bool operator==(const String & S1, const String & S2)
{
	std::string s1(S1.elements, S1.end);
	std::string s2(S2.elements, S2.end);
	return s1 == s2;
}

bool operator!=(const String & S1, const String & S2)
{
	return !(S1 == S2);
}
bool operator<(const String & S1, const String & S2)
{
	std::string s1(S1.elements, S1.end);
	std::string s2(S2.elements, S2.end);
	return s1 < s2;
}
bool operator<=(const String & S1, const String & S2)
{
	return !(S1 > S2);
}
bool operator>(const String & S1, const String & S2)
{
	return S2 < S1;
}
bool operator>=(const String & S1, const String & S2)
{
	return !(S1 < S2);
}

