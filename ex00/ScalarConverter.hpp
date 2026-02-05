#pragma once

#include <string>

class ScalarConverter
{
	private:
		ScalarConverter(void);
		ScalarConverter(const ScalarConverter & src);
		~ScalarConverter(void);
		ScalarConverter & operator = (const ScalarConverter & src);
	public:
		static	convert(std::string literal);
};
