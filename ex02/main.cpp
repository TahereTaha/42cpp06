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

void	identify(Base *p)
{
	std::cout << "ptr base identify: ";
	if (dynamic_cast<A*>(p))
		std::cout << "the identified class is: A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "the identified class is: B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "the identified class is: C" << std::endl;
	else
		std::cout << "no type has been identified." << std::endl;
}

void	identify(Base &p)
{
	std::cout << "ref base identify: ";
	try
	{
		dynamic_cast<A&>(p);
		std::cout << "the identified class is: A" << std::endl;
		return ;
	}
	catch (...) {}
	try
	{
		dynamic_cast<B&>(p);
		std::cout << "the identified class is: B" << std::endl;
		return ;
	}
	catch (...) {}
	try
	{
		dynamic_cast<C&>(p);
		std::cout << "the identified class is: C" << std::endl;
		return ;
	}
	catch (...) {}
	std::cout << "no type has been identified." << std::endl;
}

int main(void)
{
	Base *obj = generate();
	identify(obj);
	identify(*obj);
	return (0);
}
