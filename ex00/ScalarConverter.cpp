#include "ScalarConverter.hpp"
#include <iostream>
#include <typeinfo>
#include <cstddef>
#include <cctype>

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

// defining some types.
const std::type_info	&type_char = typeid(char);
const std::type_info	&type_int = typeid(int);
const std::type_info	&type_float = typeid(float);
const std::type_info	&type_double = typeid(double);
const std::type_info	&type_none = typeid(char *);

//	my float literals will allow event the cursed '-.' witch maps to 0 or -0.

// the regex for matching a char: ^[\x20-\x7f]$
static size_t	matchChar(std::string str)
{
	//	^
	size_t	i = 0;
	
	//	[\x20-\x7f]
	if (str.size() > i && isprint(str[i]))
		i++;
	else
		return (0);

	//	$
	if (str.size() == i)
		return (i);
	else
		return (0);
}

// the regex for matching a int: ^[+-]?[0-9]+$
static size_t	matchInt(std::string str)
{
	//	^
	size_t	i = 0;
	
	//	[+-]?
	if (str.size() > i && (str[i] == '+' || str[i] == '-'))
		i++;

	//	[0-9]+
	if (!(str.size() > i && isdigit(str[i])))
		return (0);
	while (str.size() > i && isdigit(str[i]))
		i++;

	//	$
	if (str.size() == i)
		return (i);
	else
		return (0);
}

// the regex for matching a float: ^(nan|[+-]?(inf|[0-9]*[.][0-9]*))[f]$
static size_t	matchFloat(std::string str)
{
	//	^
	size_t	i = 0;

	//	(nan|x)
	if (!str.compare(i, 3, "nan"))
		i += 3;
	else
	{
		//	[+-]?
		if (str.size() > i && (str[i] == '+' || str[i] == '-'))
			i++;

		//	(inf|x)
		if (!str.compare(i, 3, "inf"))
			i += 3;
		else
		{
			//	[0-9]*
			while (str.size() > i && isdigit(str[i]))
				i++;
		
			//	[.]
			if (str.size() > i && str[i] == '.')
				i++;
			else
				return (0);
		
			//	[0-9]*
			while (str.size() > i && isdigit(str[i]))
				i++;
		}
	}

	//	[f]
	if (str.size() > i && str[i] == 'f')
		i++;
	else
		return (0);

	//	$
	if (str.size() == i)
		return (i);
	else
		return (0);
}

// the regex for matching a double:	^(nan|[+-]?(inf|[0-9]*[.][0-9]*))$ 
static size_t	matchDouble(std::string str)
{
	//	^
	size_t	i = 0;

	//	(nan|x)
	if (!str.compare(i, 3, "nan"))
		i += 3;
	else
	{
		//	[+-]?
		if (str.size() > i && (str[i] == '+' || str[i] == '-'))
			i++;

		//	(inf|x)
		if (!str.compare(i, 3, "inf"))
			i += 3;
		else
		{
			//	[0-9]*
			while (str.size() > i && isdigit(str[i]))
				i++;
		
			//	[.]
			if (str.size() > i && str[i] == '.')
				i++;
			else
				return (0);
		
			//	[0-9]*
			while (str.size() > i && isdigit(str[i]))
				i++;
		}
	}

	//	$
	if (str.size() == i)
		return (i);
	else
		return (0);
}

//	it will allwais identify all singel digit as int and never as char.
static const std::type_info	&identifyType(std::string literal)
{
	if (matchFloat(literal))
		return (type_float);
	if (matchDouble(literal))
		return (type_double);
	if (matchInt(literal))
		return (type_int);
	if (matchChar(literal))
		return (type_char);
	return (type_none);
}

void	ScalarConverter::convert(std::string literal)
{
	const std::type_info	&type = identifyType(literal);

	if (type == type_none)
		std::cout << "incorrect value." << std::endl;
	else
		std::cout << "the type is: " << type.name() << std::endl;
	if (type == type_char)
		std::cout << "is a char." << std::endl;
	if (type == type_int)
		std::cout << "is a int." << std::endl;
	if (type == type_float)
		std::cout << "is a float." << std::endl;
	if (type == type_double)
		std::cout << "is a double." << std::endl;
	std::cout << "the literal is: " << literal << std::endl;
}

