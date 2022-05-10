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
		tree.insert(pair_value(i, i * 1.1));
//		mymap.insert(pair_value(i, 21.1));
	}
	tree.print();
	tree.erase(14);
	tree.print();
	tree.erase(12);
	tree.print();
	tree.erase(13);
	tree.print();
	tree.erase(11);
	tree.print();
	tree.erase(6);
	tree.print();
	tree.erase(5);
	tree.print();
	tree.erase(4);
	tree.print();
	tree.erase(7);
	tree.erase(8);
	tree.erase(2);
	tree.erase(0);
	tree.print();
	tree.balancing_double_black(tree.search(1), tree.search(3));
	tree.print();
}
