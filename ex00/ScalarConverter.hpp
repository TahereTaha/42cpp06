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
		static void	convert(std::string literal);
};
