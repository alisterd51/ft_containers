/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:21:42 by antoine           #+#    #+#             */
/*   Updated: 2022/04/17 14:41:59 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
		class stack
		{
			public:
				//member type
				typedef typename Container::value_type	value_type;
				typedef typename Container::size_type	size_type;
				typedef Container						container_type;
			protected:
				//member objects
				Container c;
			public:
				//constructor
				explicit stack(const Container& cont = Container()) :
					c(cont)
				{
				}
				//destructor
				//operator=
				//capacity
				bool empty() const
				{
					return (c.empty());
				}
				size_type size() const
				{
					return (c.size());
				}
				//element access
				value_type& top()
				{
					return (c.back());
				}
				const value_type& top() const
				{
					return (c.back());
				}
				//modifiers
				void push(const value_type& x)
				{
					c.push_back(x);
				}
				void pop()
				{
					c.pop_back();
				}
				//getter
				Container	_getC() const
				{
					return (c);
				}
		};
	//non-member functions
	template <class T, class Container>
		bool operator==(const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (x._getC() == y._getC());
		}
	template <class T, class Container>
		bool operator< (const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (x._getC() < y._getC());
		}
	template <class T, class Container>
		bool operator!=(const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (x._getC() != y._getC());
		}
	template <class T, class Container>
		bool operator> (const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (x._getC() > y._getC());
		}
	template <class T, class Container>
		bool operator>=(const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (x._getC() >= y._getC());
		}
	template <class T, class Container>
		bool operator<=(const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (x._getC() <= y._getC());
		}
}

#endif
