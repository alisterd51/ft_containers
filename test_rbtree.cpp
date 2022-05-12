#include "map.hpp"

#include <map>

int	main()
{
/*	typedef int									type_key;
	typedef std::pair<const type_key, double>	pair_value;
	typedef std::_Select1st<pair_value>			select;
	typedef std::less<type_key>					less;
	typedef std::allocator<pair_value>			alloc;
	typedef __ft::RBtree<type_key, pair_value, select, less, alloc>
												tree_type;*/
//	tree_type	tree;
//	std::map<int,double> mymap;
	ft::map<int,double> mymap;
	
	for (int i = 0; i < 15; ++i)
	{
//		tree.insert(pair_value(i, i * 1.1));
//		mymap.insert(pair_value(i, i * 1.1));
	}
/*	tree.print();
	tree.search(4)->color = _FT_RB_TREE_BLACK;
	tree.search(2)->color = _FT_RB_TREE_BLACK;
	tree.search(3)->color = _FT_RB_TREE_RED;
	tree.print();
	tree.erase(1);
	tree.print();
*/}
