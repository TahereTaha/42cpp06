#include "ScalarConverter.hpp"
#include <iostream>
#include <typeinfo>
#include <cstddef>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <limits>

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

//	a storage type for storing any of the scalars.
typedef union {
	char	_char;
	int		_int;
	float	_float;
	double	_double;
}	scalar_storage;
// the long exists here for error handeling purposes.

static scalar_storage	strToScalar(std::string str, const std::type_info &type)
{
	scalar_storage	storage;
	
	if (type == type_char)
		storage._char = str[0];
	
	if (type == type_int)
		storage._int = std::atoi(str.c_str());
	
	if (type == type_float)
		storage._float = std::atof(str.c_str());

	if (type == type_double)
		storage._double = std::atof(str.c_str());

	return (storage);
}

static bool	isFinite(scalar_storage scalar, const std::type_info &type)
{
	if (type == type_float && std::isfinite(scalar._float))
		return (true);
	if (type == type_double && std::isfinite(scalar._double))
		return (true);
	if (type == type_int || type == type_char)
		return (true);
	return (false);
}

static bool isWithinLimits(scalar_storage scalar, \
	const std::type_info &type, \
	long uper_bound, \
	long lower_bound)
{
	double number;
	if (type == type_float)
		number = static_cast<double>(scalar._float);
	else if (type == type_double)
		number = scalar._double;
	else if (type == type_int)
		number = static_cast<double>(scalar._int);
	else if (type == type_char)
		number = static_cast<double>(scalar._char);
	else
		number = 0;
	if (number <= uper_bound && number >= lower_bound)
		return (true);
	return (false);
}

static void	printConversionChar(scalar_storage scalar, const std::type_info &type)
{
	std::cout << "char: ";
	
	//	check for some non displayable values.

	if (!isFinite(scalar, type))
	{
		std::cout << "imposible" << std::endl;
		return ;
	}
	
	if (!isWithinLimits(scalar, \
						type, \
						std::numeric_limits<char>::max(), \
						std::numeric_limits<char>::min()))
	{
		std::cout << "overflow" << std::endl;
		return ;
	}
	
	//	convent the value to char.
	char value;
	if (type == type_char)
		value = static_cast<char>(scalar._char);
	if (type == type_int)
		value = static_cast<char>(scalar._int);
	if (type == type_float)
		value = static_cast<char>(scalar._float);
	if (type == type_double)
		value = static_cast<char>(scalar._double);

	if (isprint(value))
		std::cout << "'" << value << "'" << std::endl;
	else
		std::cout << "non printable character" << std::endl;
}

static void	printConversionInt(scalar_storage scalar, const std::type_info &type)
{
	std::cout << "int: ";
	
	//	check for some non displayable values.

	if (!isFinite(scalar, type))
	{
		std::cout << "imposible" << std::endl;
		return ;
	}

	if (!isWithinLimits(scalar, \
						type, \
						std::numeric_limits<int>::max(), \
						std::numeric_limits<int>::min()))
	{
		std::cout << "overflow" << std::endl;
		return ;
	}

	//	convent the value to char.
	int value;
	if (type == type_char)
		value = static_cast<int>(scalar._char);
	if (type == type_int)
		value = static_cast<int>(scalar._int);
	if (type == type_float)
		value = static_cast<int>(scalar._float);
	if (type == type_double)
		value = static_cast<int>(scalar._double);

	std::cout << value << std::endl;
}

static void	printConversionFloat(scalar_storage scalar, const std::type_info &type)
{
	std::cout << "float: ";
	
	//	convent the value to char.
	float value;
	if (type == type_char)
		value = static_cast<float>(scalar._char);
	if (type == type_int)
		value = static_cast<float>(scalar._int);
	if (type == type_float)
		value = static_cast<float>(scalar._float);
	if (type == type_double)
		value = static_cast<float>(scalar._double);

	std::cout << value << std::endl;
}

static void	printConversionDouble(scalar_storage scalar, const std::type_info &type)
{
	std::cout << "double: ";
	
	//	convent the value to char.
	double value;
	if (type == type_char)
		value = static_cast<double>(scalar._char);
	if (type == type_int)
		value = static_cast<double>(scalar._int);
	if (type == type_float)
		value = static_cast<double>(scalar._float);
	if (type == type_double)
		value = static_cast<double>(scalar._double);

	std::cout << value << std::endl;
}

void	ScalarConverter::convert(std::string literal)
{
	const std::type_info	&type = identifyType(literal);
	
	if (type == type_none)
	{
		std::cout << "malformed literal." << std::endl;
		return ;
	}

	scalar_storage	scalar = strToScalar(literal, type);

	printConversionChar(scalar, type);
	printConversionInt(scalar, type);
	printConversionFloat(scalar, type);
	printConversionDouble(scalar, type);
}

