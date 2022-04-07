/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:38:28 by antoine           #+#    #+#             */
/*   Updated: 2022/04/07 05:15:59 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <algorithm>
#include <stdexcept>
#include "iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
		class iterator_vector : public std::iterator<std::bidirectional_iterator_tag, T>
		{
			public:
				//member types
				typedef T	value_type;
				typedef T*	pointer;
				//constructor
				iterator_vector(pointer p) :
					_it(p)
				{
				}
				//destructor
				//operator=
				//operators
				bool operator== (const iterator_vector<T>& rhs)
				{
					return (this->_it == rhs._it);
				}
			private:
				pointer	_it;
		};
	//non member function overloads

	template <class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				//member types
				typedef T														value_type;
				typedef Alloc													allocator_type;
				typedef typename allocator_type::reference						reference;
				typedef typename allocator_type::const_reference				const_reference;
				typedef typename allocator_type::pointer						pointer;
				typedef typename allocator_type::const_pointer					const_pointer;
				typedef iterator_vector<value_type>								iterator;
				typedef iterator_vector<const value_type>						const_iterator;
				typedef ft::reverse_iterator<iterator>							reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
				typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
				typedef std::size_t												size_type;
				//constructor
				explicit vector(const allocator_type& alloc = allocator_type()) :
					_m_start(),
					_m_finish(),
					_m_end_of_storage(),
					_allocator(alloc)
			{
				//Constructs an empty container, with no elements.
			}
				explicit vector(size_type n,
						const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()) :
					_m_start(allocator_type().allocate(n * sizeof(val), 0)),
					_m_finish(_m_start + n),
					_m_end_of_storage(_m_finish),
					_allocator(alloc)
			{
				for (size_type i = 0; i < n; ++i)
				{
					_m_start[i] = val;
				}
				//Constructs a container with n elements. Each element is a copy of val.
			}
				template <class InputIterator>
					vector(InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type()) :
						_m_start(),
						_m_finish(),
						_m_end_of_storage(),
						_allocator(alloc)
			{
				(void)first;
				(void)last;
				//Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
			}
				vector(const vector& x) :
					_m_start(),
					_m_finish(),
					_m_end_of_storage(),
					_allocator(Alloc())
			{
				*this = x;
				//Constructs a container with a copy of each of the elements in x, in the same order.
			}
				//destructor
				~vector()
				{
					if (_m_start)
						allocator_type().deallocate(_m_start, _m_end_of_storage - _m_start);
				}
				//operator=
				vector&	operator=(const vector& x)
				{
					(void)x;
				}
				//iterators
				iterator begin()
				{
					return (iterator(_m_start));
				}
				const_iterator begin() const
				{
					return (const_iterator(_m_start));
				}
				iterator end()
				{
					return (iterator(_m_finish));
				}
				const_iterator end() const
				{
					return (const_iterator(_m_finish));
				}
				reverse_iterator rbegin()
				{
					return (reverse_iterator(_m_start));
				}
				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(_m_start));
				}
				reverse_iterator rend()
				{
					return (reverse_iterator(_m_finish));
				}
				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(_m_finish));
				}
				//capacity
				size_type size() const
				{
					return (size_type(_m_finish - _m_start));
				}
				size_type max_size() const
				{
					return (size_type(allocator_type().max_size()));
				}
				void	resize(size_type n, value_type val = value_type())
				{
					if (n > size())
						insert(end(), n - size(), val);
					else if (n < size())
						erase(begin() + n, end());
					else
						;// do nothing
					return ;
				}
				size_type	capacity() const
				{
					return (size_type(_m_end_of_storage - _m_start));
				}
				bool	empty() const
				{
					return (begin() == end());
				}
				void	reserve(size_type n)
				{
					if (n > max_size())
						throw std::length_error("vector::reserve");
					if (n > capacity())
					{
						const size_type	old_size = size();
						pointer			new_vector = allocator_type().allocate(n * sizeof(value_type), 0);
						pointer			foo = _m_start;
						pointer			bar = new_vector;

						while (foo != _m_finish)
						{
							*bar = *foo;
							allocator_type().destroy(foo);
							++foo;
							++bar;
						}
						allocator_type().deallocate(_m_start, _m_end_of_storage - _m_start);
						_m_start = new_vector;
						_m_finish = new_vector + old_size;
						_m_end_of_storage = _m_start + n;
					}
				}
				//element access
				//modifiers
				//allocator
			private:
				pointer	_m_start;
				pointer	_m_finish;
				pointer	_m_end_of_storage;
				Alloc	_allocator;
		};
	//non member function overloads
	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (lhs.size() == rhs.size()
					&& std::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	//template specializations (non demmande)
}
/*
# include <cstddef>
# include <memory>

namespace ft
{
template <class T, class Allocator = std::allocator<T> >
class vector
{
public:
// types:
typedef typename Allocator::reference reference;
typedef typename Allocator::const_reference const_reference;
typedef iterator_vector<T> iterator;//LegacyRandomAccessIterator and LegacyContiguousIterator to value_type
									// See 23.1
									typedef iterator_vector<const T> const_iterator;//LegacyRandomAccessIterator and LegacyContiguousIterator to const value_type
																					// See 23.1
																					typedef std::size_t size_type;
// See 23.1
typedef std::ptrdiff_t difference_type;// See 23.1
typedef T value_type;
typedef Allocator allocator_type;
typedef typename Allocator::pointer pointer;
typedef typename Allocator::const_pointer const_pointer;
typedef std::reverse_iterator<iterator> reverse_iterator;
typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
// 23.2.4.1 construct/copy/destroy:
explicit vector(const Allocator& = Allocator()) :
_m_start(),
_m_finish(),
_m_end_of_storage(),
_allocator()
{
return ;
}
explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator())
{
_m_create_storage(n);
return ;
}
template <class InputIterator>
vector(InputIterator first, InputIterator last, const Allocator& = Allocator())
{
return ;
}
vector(const vector<T,Allocator>& x)
{
return ;
}
~vector()
{
_m_deallocate(_m_start, _m_end_of_storage - _m_start);
return ;
}
vector<T,Allocator>&	operator=(const vector<T,Allocator>& x);
template <class InputIterator>
void				assign(InputIterator first, InputIterator last)
{
erase(begin(), end());
insert(begin(), first, last);
return ;
}
void					assign(size_type n, const T& t)
{
erase(begin(), end());
insert(begin(), n, t);
}
allocator_type			get_allocator() const;
// iterators:
iterator				begin()
{
return (iterator(_m_start));
}
const_iterator			begin() const
{
	return (const_iterator(_m_start));
}
iterator				end()
{
	return (iterator(_m_finish));
}
const_iterator			end() const
{
	return (const_iterator(_m_finish));
}
reverse_iterator		rbegin()
{
	return (reverse_iterator(_m_start));
}
const_reverse_iterator	rbegin() const
{
	return (const_reverse_iterator(_m_start));
}
reverse_iterator		rend()
{
	return (reverse_iterator(_m_finish));
}
const_reverse_iterator	rend() const
{
	return (const_reverse_iterator(_m_finish));
}
// 23.2.4.2 capacity:
size_type				size() const
{
	return (size_type(_m_finish - _m_start));
}
size_type				max_size() const;
void					resize(size_type sz, T c = T())
{
	if (sz > size())
		insert(end(), sz - size(), c);
	else if (sz < size())
		erase(begin() + sz, end());
	else
		;// do nothing
	return ;
}
size_type				capacity() const
{
	return size_type(_m_end_of_storage - _m_start);
}
bool					empty() const
{
	return (begin() == end());
}
void					reserve(size_type n);
// element access:
reference				operator[](size_type n);
const_reference			operator[](size_type n) const;
const_reference			at(size_type n) const;
reference				at(size_type n);
reference				front();
const_reference			front() const;
reference				back();
const_reference			back() const;
// 23.2.4.3 modifiers:
void					push_back(const T& x);
void					pop_back();
iterator				insert(iterator position, const T& x);
void					insert(iterator position, size_type n, const T& x);
template <class InputIterator>
void				insert(iterator position, InputIterator first, InputIterator last);
iterator				erase(iterator position);
iterator				erase(iterator first, iterator last);
void					swap(vector<T,Allocator>&);
void					clear();
// operators
vector&					operator=(vector& rhs);
private:
pointer _m_start;
pointer _m_finish;
pointer _m_end_of_storage;
Allocator	_allocator;//

void					_m_create_storage(size_t n)
{
	_m_start = _m_allocate(n);
	_m_finish = _m_start;
	_m_end_of_storage = _m_start + n;
	return ;
}
pointer	_m_allocate(size_t n)
{
	if (n != 0)
		return (_allocator.allocate());
	else
		return (pointer());
}
void	_m_deallocate(pointer p, size_t n)
{
	if (p)
		_allocator.deallocate(p, n);
}
//using _Base::_M_impl;//
//using _Base::_M_get_Tp_allocator;//
};
template <class T, class Allocator>
bool	operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator>
bool	operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator>
bool	operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator>
bool	operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator>
bool	operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator>
bool	operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
// specialized algorithms:
template <class T, class Allocator>
void	swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}
*/
#endif
