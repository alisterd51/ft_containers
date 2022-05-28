#include "map.hpp"

#include <map>

int	main()
{
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator it;
	ft::map<char,int>::iterator ite;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;

	std::cout << (mymap.insert(ft::make_pair<const char, int>('a', 21))).second << std::endl;
	std::cout << (mymap.insert(ft::make_pair<const char, int>('z', 21))).second << std::endl;

	mymap.insert(mymap.find('z'), ft::make_pair<const char, int>('z', 42));
	it=mymap.find('b');
	std::cout << "found b\n";
	mymap.erase (it);                   // erasing by iterator
	std::cout << "erase iterator to b\n";
	mymap.erase ('c');                  // erasing by key
	std::cout << "erase by key 'c'\n";
	it=mymap.find ('e');
	ite=mymap.find ('z');
	std::cout << "erase by range 'e' to 'y'\n";
	mymap.erase ( it, ite );    // erasing by range

	std::cout << " display :\n";
	// show content:
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}
