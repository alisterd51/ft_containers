/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:38:28 by antoine           #+#    #+#             */
/*   Updated: 2022/05/01 15:47:46 by anclarma         ###   ########.fr       */
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
					_m_start(),
					_m_finish(),
					_m_end_of_storage(),
					_allocator(alloc)
			{
				insert(begin(), n, val);
				//Constructs a container with n elements. Each element is a copy of val.
			}
				//thanks https://stackoverflow.com/questions/11898657/enable-if-iterator-as-a-default-template-parameter
				//and
				//https://stackoverflow.com/questions/15598939/how-do-i-use-stdis-integral-to-select-an-implementation
				template <class InputIterator>
					vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL,
							typename std::iterator_traits<InputIterator>::iterator_category* = NULL) :
						_m_start(),
						_m_finish(),
						_m_end_of_storage(),
						_allocator(alloc)
			{
				assign(first, last);
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
					{
						for (pointer i = _m_start; i < _m_finish; ++i)
							_allocator.destroy(i);
						_allocator.deallocate(_m_start, _m_end_of_storage - _m_start);
					}
				}
				//operator=
				vector&	operator=(const vector& x)
				{
					if (this != &x)
						assign(x.begin(), x.end());
					return (*this);
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
					return (reverse_iterator(end()));
				}
				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(end()));
				}
				reverse_iterator rend()
				{
					return (reverse_iterator(begin()));
				}
				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(begin()));
				}
				//capacity
				size_type size() const
				{
					return (size_type(_m_finish - _m_start));
				}
				size_type max_size() const
				{
					return (size_type(_allocator.max_size()));
				}
				void	resize(size_type n, value_type val = value_type())
				{
					if (n > size())
						insert(end(), n - size(), val);
					else if (n < size())
						erase(begin() + n, end());
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
						pointer			new_vector = _allocator.allocate(n);
						pointer			foo = _m_start;
						pointer			bar = new_vector;

						while (foo != _m_finish)
						{
							_allocator.construct(bar, *foo);
							++foo;
							++bar;
						}
						for (pointer i = _m_start; i != _m_finish; ++i)
							_allocator.destroy(i);
						if (_m_start != _m_end_of_storage)
							_allocator.deallocate(_m_start, _m_end_of_storage - _m_start);
						_m_start = new_vector;
						_m_finish = new_vector + old_size;
						_m_end_of_storage = new_vector + n;
					}
				}
				//element access
				reference		operator[](size_type n)
				{
					return (*(_m_start + n));
				}
				const_reference	operator[](size_type n) const
				{
					return (*(_m_start + n));
				}
				reference		at(size_type n)
				{
					if (n >= size())
						throw std::out_of_range("vector::at");
					return (*(_m_start + n));
				}
				const_reference	at(size_type n) const
				{
					if (n >= size())
						throw std::out_of_range("vector::at");
					return (*(_m_start + n));
				}
				reference		front()
				{
					return (*_m_start);
				}
				const_reference	front() const
				{
					return (*_m_start);
				}
				reference		back()
				{
					return (*(_m_finish - 1));
				}
				const_reference	back() const
				{
					return (*(_m_finish - 1));
				}
				//modifiers
				template <class InputIterator>
					void	assign(InputIterator first, InputIterator last)
					{
						typedef typename std::__is_integer<InputIterator>::__type _Integral;
						_M_assign_dispatch(first, last, _Integral());
					}
				void		assign(size_type n, const value_type& val)
				{
					_M_fill_assign(n, val);
				}
				void		push_back(const value_type& val)
				{
					if (size() + 1 > capacity())
						reserve(capacity() == 0 ? 1 : capacity() * 2);
					_allocator.construct(_m_finish, val);
					++_m_finish;
				}
				void		pop_back()
				{
					_allocator.destroy(_m_finish - 1);
					--_m_finish;
				}
				iterator	insert(iterator position, const value_type& val)
				{
					const difference_type	diff = position - begin();

					insert(position, 1, val);
					return (begin() + diff);
				}
				void		insert(iterator position, size_type n, const value_type& val)
				{
					_M_fill_insert(position, n, val);
				}
				template<typename InputIterator>
					void	insert(iterator pos, InputIterator first, InputIterator last)
					{
						typedef typename std::__is_integer<InputIterator>::__type _Integral;
						_M_insert_dispatch(pos, first, last, _Integral());
					}
				iterator	erase(iterator position)
				{
					const difference_type	diff = position - begin();
					pointer	p = _m_start + diff;

					_allocator.destroy(p);
					while (p != _m_finish - 1)
					{
						_allocator.construct(p, *(p + 1));
						_allocator.destroy(p + 1);
						++p;
					}
					--_m_finish;
					return (begin() + diff);
				}
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
					_m_finish -= diff;
					return (ret);
				}
				void	swap(vector& x)
				{
					pointer	tmp_start = x._m_start;
					pointer	tmp_finish = x._m_finish;
					pointer	tmp_end_of_storage = x._m_end_of_storage;
					Alloc	tmp_allocator = x._allocator;

					x._m_start = this->_m_start;
					x._m_finish = this->_m_finish;
					x._m_end_of_storage = this->_m_end_of_storage;
					x._allocator = this->_allocator;
					this->_m_start = tmp_start;
					this->_m_finish = tmp_finish;
					this->_m_end_of_storage = tmp_end_of_storage;
					this->_allocator = tmp_allocator;
				}
				void	clear()
				{
					for (pointer i = _m_start; i < _m_finish; ++i)
						_allocator.destroy(i);
					_m_finish = _m_start;
				}
				//allocator
				allocator_type	get_allocator() const
				{
					return (_allocator);
				}
			private:
				pointer	_m_start;
				pointer	_m_finish;
				pointer	_m_end_of_storage;
				Alloc	_allocator;

				//sub assign function
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
				template<typename _Integer>
					void
					_M_assign_dispatch(_Integer __n, _Integer __val, std::__true_type)
					{ _M_fill_assign(__n, __val); }
				template<typename _InputIterator>
					void
					_M_assign_dispatch(_InputIterator __first, _InputIterator __last,
							std::__false_type)
					{ _M_assign_aux(__first, __last, std::__iterator_category(__first)); }
				void		_M_fill_assign(size_type n, const value_type& val)
				{
					erase(begin(), end());
					insert(begin(), n, val);
				}
				//sub insert function
				void		_M_fill_insert(iterator position, size_type n, const value_type& val)
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
						_allocator.construct(&_m_start[i + n], _m_start[i]);
						_allocator.destroy(&_m_start[i]);
					}
					for (size_type i = diff; i < diff + n; i++)
						_allocator.construct(&_m_start[i], val);
					_m_finish += n;
				}
				template<typename _InputIterator>
					void
					_M_range_insert(iterator pos, _InputIterator first,
							_InputIterator last, std::input_iterator_tag)
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
				template<typename _InputIterator>
					void
					_M_insert_dispatch(iterator __pos, _InputIterator __first,
							_InputIterator __last, std::__false_type)
					{
						_M_range_insert(__pos, __first, __last,
								std::__iterator_category(__first));
					}
				template<typename _Integer>
					void
					_M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
							std::__true_type)
					{
						_M_fill_insert(__pos, __n, __val);
					}
		};
	//non member function overloads
	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (lhs.size() == rhs.size()
					&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}
	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}
	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			return (x.swap(y));
		}
	//template specializations (non demmande)
}

#endif
