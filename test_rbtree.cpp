#include "map.hpp"

#include <map>

int	main()
{
	typedef int									type_key;
	typedef std::pair<const type_key, double>	pair_value;
	typedef std::_Select1st<pair_value>			select;
	typedef std::less<type_key>					less;
	typedef std::allocator<pair_value>			alloc;
	typedef __ft::RBtree<type_key, pair_value, select, less, alloc>
												tree_type;
	tree_type	tree;
//	std::map<int,double> mymap;
	
	for (int i = 0; i < 15; ++i)
	{
		tree.insert(pair_value(i, 21.1));
//		mymap.insert(pair_value(i, 21.1));
	}
	std::cout << tree.search(64);
//	tree.print();
}
