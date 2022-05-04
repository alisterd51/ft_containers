#include "map.hpp"

int	main()
{
	typedef int									type_key;
	typedef std::pair<const type_key, double>	pair_value;
	typedef std::_Select1st<pair_value>			select;
	typedef std::less<type_key>					less;
	typedef std::allocator<pair_value>			alloc;
	typedef __ft::RBnode<type_key, pair_value, select, less, alloc>
												node_type;
	pair_value	product1(42, 21.1);
/*	node_type	*root = new node_type(product1);
	for (int i = 0; i < 3; ++i)
	{
		pair_value	product(i, 21.1);
		node_type*	node = new node_type(product);
		
		root = insertion(root, node);
	}
	root->print();*/
	node_type	rbTree;
}
