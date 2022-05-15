#include <iostream>
#include "functions.h"
#include "functions.cpp"

int main()
{
	fm::Vector<size_t> v1;
	fm::Vector<size_t> v2(4, 1);
	fm::Vector<size_t> v3;
	v3 = v2;
	std::cout <<"1. " << v1 << "2. " << v2 << "3. " << v3 << std::endl;

	v1.Push_back(9);
	v1.Push_back(2);
	v1.Push_back(8);
	v1.Push_back(6);
	v1.Push_back(3);
	v2.Push_back(9);
	std::cout << "1. " << v1 << "2. " << v2 << std::endl;

	v1.Push_here(15,4);
	v2.Push_here(15,4);
	std::cout << "1. " << v1 << "2. " << v2 << std::endl;

	auto a = v1.Find(9);
	auto b = v2.Find(9);
	std::cout << "1. " << v1 << "2. " << v2 << std::endl;
	std::cout << "Index from v1: " << a << " " << "Index from v2: " << b << std::endl << std::endl;

	v1.Delete_element(4);
	v2.Delete_element(4);
	std::cout << "1. " << v1 << "2. " << v2 << std::endl;

	v1.Delete_all();
	v2.Delete_all();
	v3.Delete_all();
	std::cout << "1. " << v1 << "2. " << v2 << "3. " << v3 << std::endl;
}