/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 03:06:35 by anclarma          #+#    #+#             */
/*   Updated: 2022/05/03 02:53:37 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace	ft
{
	//equal
	//Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), and false otherwise
	//Complexity:
	// At most last1 - first1 applications of the predicate
	template <class InputIterator1, class InputIterator2>
		bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
		{
			for (; first1 != last1; ++first1, ++first2)
				if (!(*first1 == *first2))
					return (false);
			return (true);
		}
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
		bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
		{
			for (; first1 != last1; ++first1, ++first2)
				if (!pred(*first1, *first2))
					return (false);
			return (true);
		}

	//lexicographical_compare
	//Elements are compared using operator<
	//Complexity:
	// At most 2·min(N1, N2) applications of the comparison operation,
	// where N1 = std::distance(first1, last1) and N2 = std::distance(first2, last2)
	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2)
		{
			for (; first1 != last1; ++first1, ++first2)
			{
				if (first2 == last2 || *first2 < *first1)
					return (false);
				else if (*first1 < *first2)
					return (true);
			}
			return (first2 != last2);
		}
	//Elements are compared using the given binary comparison function comp
	//Complexity:
	// At most 2·min(N1, N2) applications of the comparison operation,
	// where N1 = std::distance(first1, last1) and N2 = std::distance(first2, last2)
	template <class InputIterator1, class InputIterator2, class Compare>
		bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2, Compare comp)
		{
			for (; first1 != last1; ++first1, ++first2)
			{
				if (first2 == last2 || comp(*first2, *first1))
					return (false);
				else if (comp(*first1, *first2))
					return (true);
			}
			return (first2 != last2);
		}
}

#endif
