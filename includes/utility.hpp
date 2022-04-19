/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:00:58 by anclarma          #+#    #+#             */
/*   Updated: 2022/04/19 17:27:56 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace	ft
{
	template <class T1, class T2> struct pair
	{
		public:
			// Member types
			typedef T1	first_type;
			typedef T2	second_type;
			// Member variables
			first_type	first;
			second_type	second;
			// (constructor)
			pair() : first(), second()
		{
		}
			template<class U, class V>
				pair(const pair<U,V>& pr) : first(pr.first), second(pr.second)
			{
			}
			pair (const first_type& a, const second_type& b) : first(a), second(b)
		{
		}
			// pair::operator=
			// implicitly declared
	};
	//relational operators (pair)
	template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return (lhs.first == rhs.first && lhs.second == rhs.second);
		}

	template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return (!(lhs == rhs));
		}

	template <class T1, class T2>
		bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
		}

	template <class T1, class T2>
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return (!(rhs < lhs));
		}

	template <class T1, class T2>
		bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return (rhs < lhs);
		}

	template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return (!(lhs<rhs));
		}

	template <class T1, class T2>
		pair<T1, T2>	make_pair(T1 x, T2 y)
		{
			return (pair<T1, T2>(x, y));
		}
}

#endif
