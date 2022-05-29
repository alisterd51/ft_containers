#include "map.hpp"

#include <map>

int	main()
{
	ft::map<char,int> mymap;


                if (mymap.begin() != mymap.end())
                        std::cout << "This should not happen\n";

                mymap['b'] = 100;
                mymap['a'] = 200;
                mymap['c'] = 300;

                if (mymap.begin() == mymap.end())
                        std::cout << "This is wrong\n";
                // show content:
                for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); it++)
                        std::cout << it->first << " => " << it->second << '\n';

                std::cout << "Hello there\n";
                for (ft::map<char,int>::const_iterator it=mymap.begin(); it!=mymap.end(); it++)
                        std::cout << it->first << " => " << it->second << '\n';
                std::cout << "General Kenobi\n";

                ft::map<char, int>::const_iterator it = mymap.begin();
                ft::map<char, int>::const_iterator ti = mymap.end();
                std::cout << "Wupwup\n";

                it++;
                ++it;
                it--;
                --it;
                std::cout << "marker1\n";

                ti--;
                --ti;
                ++ti;
                ti++;

                ti = it;

                std::cout << "Trump is a kiddo\n";
                ft::map<char, int>::iterator end = mymap.end();
                while(it != end)
                {
                        std::cout << it->first << " => " << it->second << '\n';
                        it++;
                }
}
