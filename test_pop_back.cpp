#include <map>
#include "map.hpp"

#include <utility> //pair make_pair
#include "utility.hpp" //pair make_pair //a enlever
#include <vector>

int main()
{
	std::vector<ft::pair<int, double> >	std_vector_ft_pair;

	std_vector_ft_pair.push_back(ft::make_pair(1, 21.0));
	std_vector_ft_pair.push_back(ft::make_pair(2, 25.0));
	std_vector_ft_pair.push_back(ft::make_pair(3, 42.0));

	std::vector<std::pair<int, double> >	std_vector_std_pair;

	std_vector_std_pair.push_back(std::make_pair(1, 21.0));
	std_vector_std_pair.push_back(std::make_pair(2, 25.0));
	std_vector_std_pair.push_back(std::make_pair(3, 42.0));

	ft::map<int, double, std::less<int>, std::allocator<ft::pair<const int, double> > > 	ft_empty_map;
	std::map<int, double, std::less<int>, std::allocator<std::pair<const int, double> > >	std_empty_map;


	ft_empty_map[1];
	std_empty_map[1];
	ft_empty_map[2];
	std_empty_map[2];
	ft_empty_map[3];
	std_empty_map[3];
	ft_empty_map[4];
	std_empty_map[4];

	ft_empty_map.erase(42);
	std_empty_map.erase(42);

	ft_empty_map.erase(2);
	std_empty_map.erase(2);
}
