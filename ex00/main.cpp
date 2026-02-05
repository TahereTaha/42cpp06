#include "ScalarConverter.hpp"
#include <string>
#include <iostream>

//int main(int ac, char **av)
//{
////	ScalarConverter		something;
//
//	if (ac != 2)
//	{
//		std::cout << "please provide only one argument." << std::endl;
//		return (1);
//	}
//	ScalarConverter::convert(av[1]);
//	return (0);
//}

#include <string>
#include <cstdlib>

int main()
{
	std::cout << std::atoi("-2.2") << std::endl;
	std::cout << std::atoi("-0.2") << std::endl;
}

