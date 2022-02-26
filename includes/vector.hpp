/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:49:51 by antoine           #+#    #+#             */
/*   Updated: 2022/02/27 00:02:41 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft {
	template <class T, class Allocator = std::allocator<T> > class vector;
	template <class T, class Allocator>
		bool operator==(const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator< (const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator!=(const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator> (const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator>=(const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator<=(const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
	template <class Allocator> class vector<bool,Allocator>;
	template <class Allocator>
		bool operator==(const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		bool operator< (const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		bool operator!=(const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		bool operator> (const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		bool operator>=(const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		bool operator<=(const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		void swap(vector<bool,Allocator>& x, vector<bool,Allocator>& y);
}

#endif
