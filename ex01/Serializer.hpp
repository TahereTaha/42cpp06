#pragma once

#include "Data.hpp"
#include <stdint.h>

class Serializer
{
	private:
		Serializer(void);
		Serializer(const Serializer & src);
		~Serializer(void);
		Serializer & operator = (const Serializer & src);
	public:
		static uintptr_t	serialize(Data *ptr);
		static Data			*deserialize(uintptr_t raw);
};
