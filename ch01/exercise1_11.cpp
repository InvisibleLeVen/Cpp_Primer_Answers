#include<iostream>
#define glub(a,b) a ## b
int main() {
	//std::glub(c, out) << "test";
	int first = 0, second = 0;
	std::cout << "please input two numbers:" << std::endl;
	std::cin >> first >> second;
	while (first > second? first - second: second - first) {
		int outputnum = first > second ? ++second : ++first;
		std::cout << outputnum << std::endl;
	}
	std::cin.ignore();
	std::cin.ignore();
	return 0;
}
