/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:21:42 by antoine           #+#    #+#             */
/*   Updated: 2022/05/25 18:43:11 by anclarma         ###   ########.fr       */
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
			private:
				//friend use to unlock access to protected objects in
				//non member functions
				template<typename _T1, typename _C1>
					friend bool
					operator==(const stack<_T1, _C1>&, const stack<_T1, _C1>&);

				template<typename _T1, typename _C1>
					friend bool
					operator<(const stack<_T1, _C1>&, const stack<_T1, _C1>&);
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
				//Copy-constructs the underlying container c with the contents of cont.
				//Complexity:
				// Same as the corresponding operation on the wrapped container
				explicit stack(const Container& cont = Container()) :
					c(cont)
			{
			}
				//destructor
				//operator=
				//capacity
				//Complexity:
				// Constant
				bool empty() const
				{
					return (c.empty());
				}
				//Complexity:
				// Constant
				size_type size() const
				{
					return (c.size());
				}
				//element access
				//Complexity:
				// Constant
				value_type& top()
				{
					return (c.back());
				}
				//Complexity:
				// Constant
				const value_type& top() const
				{
					return (c.back());
				}
				//modifiers
				//Complexity:
				// Equal to the complexity of Container::push_back
				void push(const value_type& x)
				{
					c.push_back(x);
				}
				//Complexity:
				// Equal to the complexity of Container::pop_back
				void pop()
				{
					c.pop_back();
				}
		};
	//non-member functions
	//Complexity:
	// Linear in the size of the container
	template <class T, class Container>
		bool operator==(const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (x.c == y.c);
		}
	//Complexity:
	// Linear in the size of the container
	template <class T, class Container>
		bool operator< (const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (x.c < y.c);
		}
	//Complexity:
	// Linear in the size of the container
	template <class T, class Container>
		bool operator!=(const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (!(x == y));
		}
	//Complexity:
	// Linear in the size of the container
	template <class T, class Container>
		bool operator> (const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (!(x <= y));
		}
	//Complexity:
	// Linear in the size of the container
	template <class T, class Container>
		bool operator>=(const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (!(x < y));
		}
	//Complexity:
	// Linear in the size of the container
	template <class T, class Container>
		bool operator<=(const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return (x < y || x == y);
		}
}

#endif
