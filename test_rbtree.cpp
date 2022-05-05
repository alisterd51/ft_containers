#include "map.hpp"

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
	
	for (int i = 0; i < 50; ++i)
	{
		int	key;

		if (i % 2)
			key = i;
		else
			key = -i;
		pair_value	product(key, 21.1);
		
		tree.insert(product);
	}
	tree.print();
}
