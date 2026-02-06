#include "Serializer.hpp"
#include "Data.hpp"
#include <stdint.h>
#include <iostream>

//	canonical orthodox form.
Serializer::Serializer(void)
{
	std::cout << "Serializer default constructor." << std::endl;
}

Serializer::Serializer(const Serializer & src)
{
	std::cout << "Serializer copy constructor." << std::endl;
	*this = src;
}

Serializer &  Serializer::operator = (const Serializer & src)
{
	std::cout << "Serializer copy assigment." << std::endl;
	if (this != &src)
	{
		// making any field equal.
	}
	return  (*this);
}

Serializer::~Serializer(void)
{
}

uintptr_t	Serializer::serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data		*Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}
