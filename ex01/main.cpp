#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int	main(void)
{
	Data	data;

	data.foo = 4;
	data.bar = 2;

	uintptr_t	raw = Serializer::serialize(&data);

	std::cout << "the ptr to data is: " << &data << std::endl;
	std::cout << "the raw returned by serialize is: " << raw << std::endl;

	Data	*new_data_ptr;

	new_data_ptr = Serializer::deserialize(raw);

	std::cout << "the old prt is: " << &data << std::endl;
	std::cout << "the new ptr is: " << new_data_ptr << std::endl;

	std::cout << "data from the old ptr: " << data.foo << data.bar << std::endl;
	std::cout << "data from the new ptr: " << new_data_ptr->foo << new_data_ptr->bar << std::endl;

	return (0);
}
