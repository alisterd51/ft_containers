/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:38:28 by antoine           #+#    #+#             */
/*   Updated: 2022/05/03 02:34:56 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <stdexcept>
#include <limits>
#include "iterator.hpp"
#include "algorithm.hpp"

namespace ft
{
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
				typedef __ft::__normal_iterator<pointer, vector>				iterator;
				typedef __ft::__normal_iterator<const_pointer, vector>			const_iterator;
				typedef ft::reverse_iterator<iterator>							reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
				typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
				typedef std::size_t												size_type;
				//constructor
				//Constructs an empty container, with no elements.
				//Complexity:
				// Constant
				explicit vector(const allocator_type& alloc = allocator_type()) :
					_start(),
					_finish(),
					_end_of_storage(),
					_allocator(alloc)
			{
			}
				//Constructs a container with n elements. Each element is a copy of val.
				//Complexity:
				// Linear in n
				explicit vector(size_type n,
						const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()) :
					_start(),
					_finish(),
					_end_of_storage(),
					_allocator(alloc)
			{
				insert(begin(), n, val);
			}
				//Constructs a container with as many elements as the range [first,last),
				//with each element constructed from its corresponding element in that range, in the same order.
				//Complexity:
				// Linear in distance between first and last
				template <class InputIterator>
					vector(InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type()) :
						_start(),
						_finish(),
						_end_of_storage(),
						_allocator(alloc)
			{
				_assign_dispatch(first, last, is_integral<InputIterator>());
			}
				//Constructs a container with a copy of each of the elements in x, in the same order.
				//Complexity:
				// Linear in size of x
				vector(const vector& x) :
					_start(),
					_finish(),
					_end_of_storage(),
					_allocator(Alloc())
			{
				*this = x;
			}
				//destructor
				//Complexity:
				// Linear in the size of the vector
				~vector()
				{
					if (_start)
					{
						for (pointer i = _start; i < _finish; ++i)
							_allocator.destroy(i);
						_allocator.deallocate(_start, _end_of_storage - _start);
					}
				}
				//operator=
				//Complexity:
				//  Linear in the size of *this and x.
				vector&	operator=(const vector& x)
				{
					if (this != &x)
						assign(x.begin(), x.end());
					return (*this);
				}
				//iterators
				//Complexity:
				// Constant
				iterator begin()
				{
					return (iterator(_start));
				}
				//Complexity:
				// Constant
				const_iterator begin() const
				{
					return (const_iterator(_start));
				}
				//Complexity:
				// Constant
				iterator end()
				{
					return (iterator(_finish));
				}
				//Complexity:
				// Constant
				const_iterator end() const
				{
					return (const_iterator(_finish));
				}
				//Complexity:
				// Constant
				reverse_iterator rbegin()
				{
					return (reverse_iterator(end()));
				}
				//Complexity:
				// Constant
				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(end()));
				}
				//Complexity:
				// Constant
				reverse_iterator rend()
				{
					return (reverse_iterator(begin()));
				}
				//Complexity:
				// Constant
				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(begin()));
				}
				//capacity
				//Complexity:
				// Constant
				size_type size() const
				{
					return (size_type(_finish - _start));
				}
				//Complexity:
				// Constant
				size_type max_size() const
				{
					return (size_type(_allocator.max_size()));
				}
				//Complexity:
				// Linear in the difference between the current size and n.
				// Additional complexity possible due to reallocation if capacity is less than count
				void	resize(size_type n, value_type val = value_type())
				{
					if (n > size())
						insert(end(), n - size(), val);
					else if (n < size())
						erase(begin() + n, end());
					return ;
				}
				//Complexity:
				// Constant
				size_type	capacity() const
				{
					return (size_type(_end_of_storage - _start));
				}
				//Complexity:
				// Constant
				bool	empty() const
				{
					return (begin() == end());
				}
				//Complexity:
				// At most linear in the size() of the container.
				void	reserve(size_type n)
				{
					if (n > max_size())
						throw std::length_error("vector::reserve");
					if (n > capacity())
					{
						const size_type	old_size = size();
						pointer			new_vector = _allocator.allocate(n);

						for (pointer foo = _start, bar = new_vector;
								foo != _finish; ++foo, ++bar)
							_allocator.construct(bar, *foo);
						for (pointer i = _start; i != _finish; ++i)
							_allocator.destroy(i);
						if (_start != _end_of_storage)
							_allocator.deallocate(_start, _end_of_storage - _start);
						_start = new_vector;
						_finish = new_vector + old_size;
						_end_of_storage = new_vector + n;
					}
				}
				//element access
				//Complexity:
				// Constant
				reference		operator[](size_type n)
				{
					return (*(_start + n));
				}
				//Complexity:
				// Constant
				const_reference	operator[](size_type n) const
				{
					return (*(_start + n));
				}
				//Complexity:
				// Constant
				reference		at(size_type n)
				{
					if (n >= size())
						throw std::out_of_range("vector::at");
					return (*(_start + n));
				}
				//Complexity:
				// Constant
				const_reference	at(size_type n) const
				{
					if (n >= size())
						throw std::out_of_range("vector::at");
					return (*(_start + n));
				}
				//Complexity:
				// Constant
				reference		front()
				{
					return (*_start);
				}
				//Complexity:
				// Constant
				const_reference	front() const
				{
					return (*_start);
				}
				//Complexity:
				// Constant
				reference		back()
				{
					return (*(_finish - 1));
				}
				//Complexity:
				// Constant
				const_reference	back() const
				{
					return (*(_finish - 1));
				}
				//modifiers
				//call either:
				// _assign_aux if InputIterator is std::input_iterator_tag
				// _fill_assign else
				//Complexity:
				// Linear in distance between first and last
				template <class InputIterator>
					void	assign(InputIterator first, InputIterator last)
					{
						_assign_dispatch(first, last, is_integral<InputIterator>());
					}
				//call _fill_assign
				//Complexity:
				// Linear in n
				void		assign(size_type n, const value_type& val)
				{
					_fill_assign(n, val);
				}
				//Complexity:
				// Amortized constant
				void		push_back(const value_type& val)
				{
					if (size() + 1 > capacity())
						reserve(capacity() == 0 ? 1 : capacity() * 2);
					_allocator.construct(_finish, val);
					++_finish;
				}
				//Complexity:
				// Constant
				void		pop_back()
				{
					_allocator.destroy(_finish - 1);
					--_finish;
				}
				//Complexity:
				// Constant plus linear in the distance between position and end of the container
				iterator	insert(iterator position, const value_type& val)
				{
					const difference_type	diff = position - begin();

					insert(position, 1, val);
					return (begin() + diff);
				}
				//call _fill_insert
				//Complexity:
				// Linear in n plus linear in the distance between position and end of the container
				void		insert(iterator position, size_type n, const value_type& val)
				{
					_fill_insert(position, n, val);
				}
				//call either:
				// _range_insert if InputIterator is std::input_iterator_tag
				// _insert_dispatch else
				//Complexity:
				// Linear in std::distance(first, last) plus linear in the distance between pos and end of the container
				template<typename InputIterator>
					void	insert(iterator pos, InputIterator first, InputIterator last)
					{
						_insert_dispatch(pos, first, last, is_integral<InputIterator>());
					}
				//Complexity:
				// Linear: the number of calls to the destructor of T is the
				// same as the number of elements erased, the assignment
				// operator of T is called the number of times equal to the
				// number of elements in the vector after the erased elements
				iterator	erase(iterator position)
				{
					const difference_type	diff = position - begin();
					pointer	p = _start + diff;

					_allocator.destroy(p);
					while (p != _finish - 1)
					{
						_allocator.construct(p, *(p + 1));
						_allocator.destroy(p + 1);
						++p;
					}
					--_finish;
					return (begin() + diff);
				}
				//Complexity:
				// Linear: the number of calls to the destructor of T is the
				// same as the number of elements erased, the assignment
				// operator of T is called the number of times equal to the
				// number of elements in the vector after the erased elements
				iterator	erase(iterator first, iterator last)
				{
					const iterator			ret = first;
					const difference_type	diff = last - first;

					for (; first < end(); ++first, ++last)
					{
						if (last < end())
						{
							_allocator.destroy(&(first[0]));
							_allocator.construct(&(first[0]), last[0]);
						}
						else
							_allocator.destroy(&(first[0]));
					}
					_finish -= diff;
					return (ret);
				}
				//Complexity:
				// Constant
				void	swap(vector& x)
				{
					pointer	tmp_start = x._start;
					pointer	tmp_finish = x._finish;
					pointer	tmp_end_of_storage = x._end_of_storage;
					Alloc	tmp_allocator = x._allocator;

					x._start = this->_start;
					x._finish = this->_finish;
					x._end_of_storage = this->_end_of_storage;
					x._allocator = this->_allocator;
					this->_start = tmp_start;
					this->_finish = tmp_finish;
					this->_end_of_storage = tmp_end_of_storage;
					this->_allocator = tmp_allocator;
				}
				//Complexity:
				// Linear in the size of the container, i.e., the number of elements
				void	clear()
				{
					for (pointer i = _start; i < _finish; ++i)
						_allocator.destroy(i);
					_finish = _start;
				}
				//allocator
				//Complexity:
				// Constant
				allocator_type	get_allocator() const
				{
					return (_allocator);
				}
			private:
				pointer	_start;
				pointer	_finish;
				pointer	_end_of_storage;
				Alloc	_allocator;

				//sub assign function
				template<typename Integer>
					void
					_assign_dispatch(Integer n, Integer val, true_type)
					{
						_fill_assign(n, val);
					}
				template<typename InputIterator>
					void
					_assign_dispatch(InputIterator first, InputIterator last, false_type)
					{
						_M_assign_aux(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
					}
				//Replaces the contents with n copies of value val
				void		_fill_assign(size_type n, const value_type& val)
				{
					erase(begin(), end());
					insert(begin(), n, val);
				}
				//Replaces the contents with copies of those in the range [first, last).
				//The behavior is undefined if either argument is an iterator into *this
				template<typename InputIterator>
					void
					_M_assign_aux(InputIterator first, InputIterator last,
							std::input_iterator_tag)
					{
						if (capacity() == 0)
						{
							size_type	new_size = 0;

							for (InputIterator test = first; test != last; ++test, ++new_size)
								;
							reserve(new_size);
						}
						erase(begin(), end());
						insert(begin(), first, last);
					}
				//sub insert function
				template<typename InputIterator>
					void
					_insert_dispatch(iterator pos, InputIterator first,
							InputIterator last, false_type)
					{
						_range_insert(pos, first, last,
								typename ft::iterator_traits<InputIterator>::iterator_category());
					}
				template<typename Integer>
					void
					_insert_dispatch(iterator pos, Integer n, Integer val,
							true_type)
					{
						_fill_insert(pos, n, val);
					}
				//inserts n copies of val before position
				void	_fill_insert(iterator position, size_type n, const value_type& val)
				{
					const difference_type	diff = position - begin();

					if (n == 0)
						return ;
					if (size() + n > capacity())
					{
						if (size() > n)
							reserve(size() * 2);
						else
							reserve(size() + n);
					}
					for (difference_type i = size() - 1; i >= diff; i--)
					{
						_allocator.construct(&_start[i + n], _start[i]);
						_allocator.destroy(&_start[i]);
					}
					for (size_type i = diff; i < diff + n; i++)
						_allocator.construct(&_start[i], val);
					_finish += n;
				}
				//inserts elements from range [first, last) before pos.
				//The behavior is undefined if first and last are iterators into *this
				template<typename InputIterator>
					void
					_range_insert(iterator pos, InputIterator first,
							InputIterator last, std::input_iterator_tag)
					{
						if (pos == end())
						{
							for (; first != last; ++first)
								insert(end(), *first);
						}
						else if (first != last)
						{
							for (difference_type i = pos - begin(); first != last; ++first, ++i)
								insert(begin() + i, *first);
						}
					}
		};
	//non member function overloads
	//Complexity:
	// Constant if lhs and rhs are of different size, otherwise linear in the size of the vector
	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (lhs.size() == rhs.size()
					&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
	//Complexity:
	// Constant if lhs and rhs are of different size, otherwise linear in the size of the vector
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}
	//Complexity:
	// Linear in the size of the vector
	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	//Complexity:
	// Linear in the size of the vector
	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}
	//Complexity:
	// Linear in the size of the vector
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}
	//Complexity:
	// Linear in the size of the vector
	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}
	//Complexity:
	// Linear in the size of the vector
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			return (x.swap(y));
		}
	//template specializations (non demmande)
}

#endif
