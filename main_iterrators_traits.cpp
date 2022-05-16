//
//	Made by lejulien
//

#include <iostream>
#include <iterator>
#include <vector>
#include "iterator.hpp"
#include <list>

template<class BidirIt>
void my_reverse(BidirIt first, BidirIt last)
{
    typename ft::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    --n;
    while(n > 0) {
        typename ft::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
        n -= 2;
    }
}

template<class BidirIt>
void y_reverse(BidirIt first, BidirIt last)
{
    typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    --n;
    while(n > 0) {
        typename std::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
        n -= 2;
    }
}

int main()
{
	{
		std::cout << " --> Test with my iterator_traits" << std::endl;
    	std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
    	my_reverse(v.begin(), v.end());
    	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
    	    std::cout << *it << ' ';
    	}
    	std::cout << '\n';

    	std::list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
    	my_reverse(l.begin(), l.end());
    	for (std::list<int>::iterator it = l.begin(); it != l.end(); it++) {
    	    std::cout << *it << ' ';
    	}
    	std::cout << '\n';

    	int a[] = {1, 2, 3, 4, 5};
    	my_reverse(a, a+5);
    	for (int i=0; i<5; ++i) {
    	    std::cout << a[i] << ' ';
    	}
    	std::cout << '\n';
	}
	{
		std::cout << " --> Test with STL iterator_traits" << std::endl;
    	std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
    	y_reverse(v.begin(), v.end());
    	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
    	    std::cout << *it << ' ';
    	}
    	std::cout << '\n';

    	std::list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
    	y_reverse(l.begin(), l.end());
    	for (std::list<int>::iterator it = l.begin(); it != l.end(); it++) {
    	    std::cout << *it << ' ';
    	}
    	std::cout << '\n';

    	int a[] = {1, 2, 3, 4, 5};
    	y_reverse(a, a+5);
    	for (int i=0; i<5; ++i) {
    	    std::cout << a[i] << ' ';
    	}
    	std::cout << '\n';
	}


}
//	Made by lejulien@42
