#include "ScalarConverter.hpp"
#include <iostream>

//	canonical orthodox form.
ScalarConverter::ScalarConverter(void)
{
	std::cout << "ScalarConverter default constructor." << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter & src)
{
	std::cout << "ScalarConverter copy constructor." << std::endl;
	*this = src;
}

ScalarConverter &  ScalarConverter::operator = (const ScalarConverter & src)
{
	std::cout << "ScalarConverter copy assigment." << std::endl;
	if (this != &src)
	{
		// making any field equal.
	}
	return  (*this);
}

ScalarConverter::~ScalarConverter(void)
{
}

ScalarConverter::convert(std::string literal)
{
	std::cout << "the literal is: " << literal << std::endl;
}

