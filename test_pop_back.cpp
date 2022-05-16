#include <vector>
#include "vector.hpp"

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

int main()
{
	NAMESPACE::vector<int>	v;

	v.push_back(42);
	v.push_back(42);
	v.pop_back();
	v.pop_back();
	v.push_back(42);
	v.push_back(42);
}
