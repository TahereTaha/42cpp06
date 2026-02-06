#include <iostream>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <ctime>

Base	*generate(void)
{
	Base	*base;

	std::srand(std::time(NULL));
	int	random_val = std::rand() % 3;

	if (random_val == 0)
	{
		std::cout << "the dice have chosen class A." << std::endl;
		base = new A();
	}
	else if (random_val == 1)
	{
		std::cout << "the dice have chosen class B." << std::endl;
		base = new B();
	}
	else
	{
		std::cout << "the dice have chosen class C." << std::endl;
		base = new C();
	}

	return (base);
}

int main(void)
{
	Base *obj = generate();
	return (0);
}
