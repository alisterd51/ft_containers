/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:38:28 by antoine           #+#    #+#             */
/*   Updated: 2022/04/30 23:01:59 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <stdexcept>
#include <limits>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
/*
_M_fill_insert(iterator __position, size_type __n, const value_type& __x)
{
	if (__n != 0)
	{
		if (size_type(this->_M_impl._M_end_of_storage
					- this->_M_impl._M_finish) >= __n)
		{
			value_type __x_copy = __x;
			const size_type __elems_after = end() - __position;
			pointer __old_finish(this->_M_impl._M_finish);

			if (__elems_after > __n)
			{
				_GLIBCXX_ASAN_ANNOTATE_GROW(__n);
				std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
						this->_M_impl._M_finish,
						this->_M_impl._M_finish,
						_M_get_Tp_allocator());
				this->_M_impl._M_finish += __n;
				_GLIBCXX_ASAN_ANNOTATE_GREW(__n);
				_GLIBCXX_MOVE_BACKWARD3(__position.base(),
						__old_finish - __n, __old_finish);
				std::fill(__position.base(), __position.base() + __n,
						__x_copy);
			}
			else
			{
				_GLIBCXX_ASAN_ANNOTATE_GROW(__n);
				this->_M_impl._M_finish =
					std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
							__n - __elems_after,
							__x_copy,
							_M_get_Tp_allocator());
				_GLIBCXX_ASAN_ANNOTATE_GREW(__n - __elems_after);
				std::__uninitialized_move_a(__position.base(), __old_finish,
						this->_M_impl._M_finish,
						_M_get_Tp_allocator());
				this->_M_impl._M_finish += __elems_after;
				_GLIBCXX_ASAN_ANNOTATE_GREW(__elems_after);
				std::fill(__position.base(), __old_finish, __x_copy);
			}
		}
		else
		{
			const size_type __len =
				_M_check_len(__n, "vector::_M_fill_insert");
			const size_type __elems_before = __position - begin();
			pointer __new_start(this->_M_allocate(__len));
			pointer __new_finish(__new_start);
			__try
			{
				// See _M_realloc_insert above.
				std::__uninitialized_fill_n_a(__new_start + __elems_before,
						__n, __x,
						_M_get_Tp_allocator());
				__new_finish = pointer();

				__new_finish
					= std::__uninitialized_move_if_noexcept_a
					(this->_M_impl._M_start, __position.base(),
					 __new_start, _M_get_Tp_allocator());

				__new_finish += __n;

				__new_finish
					= std::__uninitialized_move_if_noexcept_a
					(__position.base(), this->_M_impl._M_finish,
					 __new_finish, _M_get_Tp_allocator());
			}
			__catch(...)
			{
				if (!__new_finish)
					std::_Destroy(__new_start + __elems_before,
							__new_start + __elems_before + __n,
							_M_get_Tp_allocator());
				else
					std::_Destroy(__new_start, __new_finish,
							_M_get_Tp_allocator());
				_M_deallocate(__new_start, __len);
				__throw_exception_again;
			}
			std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
					_M_get_Tp_allocator());
			_GLIBCXX_ASAN_ANNOTATE_REINIT;
			_M_deallocate(this->_M_impl._M_start,
					this->_M_impl._M_end_of_storage
					- this->_M_impl._M_start);
			this->_M_impl._M_start = __new_start;
			this->_M_impl._M_finish = __new_finish;
			this->_M_impl._M_end_of_storage = __new_start + __len;
		}
	}
}
*/
/*
   namespace ft
   {
   template <class T, class Alloc = std::allocator<T> >
   class iterator_vector : public std::iterator<std::bidirectional_iterator_tag, T>
   {
   private:
   typedef std::iterator<std::bidirectional_iterator_tag, T>	iterator_base;
   public:
//member types
using typename iterator_base::value_type;
using typename iterator_base::difference_type;
using typename iterator_base::pointer;
using typename iterator_base::reference;
using typename iterator_base::iterator_category;
//default-constructible, copy-constructible, copy-assignable and destructible
iterator_vector() :
_p()
{
}
iterator_vector(const iterator_vector& it) :
_p(it.base())
{
}
iterator_vector&	operator= (const iterator_vector& rhs)
{
if (*this != rhs)
{
this->base = rhs.base;
}
return (*this);
}
~iterator_vector()
{
}
//
iterator_vector(pointer p) :
_p(p)
{
}
//				template<typename _Iter>
//					iterator_vector(iterator_vector<_Iter, typename __enable_if<(std::__are_same<_Iter, typename _Container::pointer>::__value), _Container>::__type>& __i)
//					: _M_current(__i.base()) { }
//
pointer	base() const
{
return (_p);
}
//a == b, a != b
bool	operator==(const iterator_vector<T>& rhs) const
{
return (this->base() == rhs.base());
}
bool	operator!=(const iterator_vector<T>& rhs) const
{
return (this->base() != rhs.base());
}
// *a, a->m
reference	operator*()
{
return (*_p);
}
pointer		operator->()
{
return (_p);
}
//++a, a++
iterator_vector&	operator++()
{
_p = _p + 1;
return (*this);
}
iterator_vector		operator++(int)
{
	iterator_vector	temp = *this;

	++(*this);
	return (temp);
}
//--a, a--
iterator_vector&	operator--()
{
	_p = _p - 1;
	return (*this);
}
iterator_vector		operator--(int)
{
	iterator_vector	temp = *this;

	--(*this);
	return (temp);
}
//a + n, n + a, a - n, a - b
iterator_vector	operator+(difference_type n) const
{
	return (iterator_vector(this->_p + n));
}
iterator_vector	operator-(difference_type n) const
{
	return (iterator_vector(this->_p - n));
}
difference_type	operator-(const iterator_vector<T>& rhs) const
{
	return (this->_p - rhs._p);
}
//a < b, a > b, a <= b, a >= b
bool	operator<(const iterator_vector<T>& rhs) const
{
	return (this->base() < rhs.base());
}
bool	operator>(const iterator_vector<T>& rhs) const
{
	return (this->base() > rhs.base());
}
bool	operator<=(const iterator_vector<T>& rhs) const
{
	return (this->base() <= rhs.base());
}
bool	operator>=(const iterator_vector<T>& rhs) const
{
	return (this->base() >= rhs.base());
}
//a += n, a -= n
iterator_vector&	operator+=(const difference_type n)
{
	this->_p += n;
	return (*this);
}
iterator_vector&	operator-=(const difference_type n)
{
	this->_p -= n;
	return (*this);
}
//a[n]
reference	operator[](difference_type n)
{
	return (*(_p + n));
}
private:
pointer	_p;
};
//n + a
	template <class T, class Alloc>
iterator_vector<T, Alloc> operator+(const typename iterator_vector<T,Alloc>::difference_type lhs, const iterator_vector<T,Alloc>& rhs)
{
	return (rhs + lhs);
}
}
*/
/*
   namespace ft
   {
   template<typename _Iterator, typename _Container>
   class __normal_iterator
   {
   protected:
   _Iterator _M_current;

   typedef std::iterator_traits<_Iterator>		__traits_type;

   public:
   typedef _Iterator					iterator_type;
   typedef typename __traits_type::iterator_category iterator_category;
   typedef typename __traits_type::value_type  	value_type;
   typedef typename __traits_type::difference_type 	difference_type;
   typedef typename __traits_type::reference 	reference;
   typedef typename __traits_type::pointer   	pointer;


   __normal_iterator()
   : _M_current(_Iterator()) { }

   explicit
   __normal_iterator(const _Iterator& __i)
   : _M_current(__i) { }

// Allow iterator to const_iterator conversion
template<typename _Iter>
__normal_iterator(const __normal_iterator<_Iter,
typename __enable_if<
(std::__are_same<_Iter, typename _Container::pointer>::__value),
_Container>::__type>& __i)
: _M_current(__i.base()) { }

// Forward iterator requirements
reference
operator*() const
{ return *_M_current; }

pointer
operator->() const
{ return _M_current; }

__normal_iterator&
operator++()
{
++_M_current;
return *this;
}

__normal_iterator
operator++(int)
{ return __normal_iterator(_M_current++); }

__normal_iterator&
operator--()
{
--_M_current;
return *this;
}

__normal_iterator
operator--(int)
{ return __normal_iterator(_M_current--); }

reference
operator[](difference_type __n) const
{ return _M_current[__n]; }

__normal_iterator&
operator+=(difference_type __n)
{ _M_current += __n; return *this; }

__normal_iterator
operator+(difference_type __n) const
{ return __normal_iterator(_M_current + __n); }

	__normal_iterator&
operator-=(difference_type __n)
{ _M_current -= __n; return *this; }

__normal_iterator
operator-(difference_type __n) const
{ return __normal_iterator(_M_current - __n); }

const _Iterator&
base() const
{ return _M_current; }
};

template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
operator==(const __normal_iterator<_IteratorL, _Container>& __lhs,
		const __normal_iterator<_IteratorR, _Container>& __rhs)
{ return __lhs.base() == __rhs.base(); }

template<typename _Iterator, typename _Container>
	inline bool
operator==(const __normal_iterator<_Iterator, _Container>& __lhs,
		const __normal_iterator<_Iterator, _Container>& __rhs)
{ return __lhs.base() == __rhs.base(); }

template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs,
		const __normal_iterator<_IteratorR, _Container>& __rhs)
{ return __lhs.base() != __rhs.base(); }

template<typename _Iterator, typename _Container>
	inline bool
operator!=(const __normal_iterator<_Iterator, _Container>& __lhs,
		const __normal_iterator<_Iterator, _Container>& __rhs)
{ return __lhs.base() != __rhs.base(); }

// Random access iterator requirements
template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
operator<(const __normal_iterator<_IteratorL, _Container>& __lhs,
		const __normal_iterator<_IteratorR, _Container>& __rhs)
{ return __lhs.base() < __rhs.base(); }

template<typename _Iterator, typename _Container>
	inline bool
operator<(const __normal_iterator<_Iterator, _Container>& __lhs,
		const __normal_iterator<_Iterator, _Container>& __rhs)
{ return __lhs.base() < __rhs.base(); }

template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
operator>(const __normal_iterator<_IteratorL, _Container>& __lhs,
		const __normal_iterator<_IteratorR, _Container>& __rhs)
{ return __lhs.base() > __rhs.base(); }

template<typename _Iterator, typename _Container>
	inline bool
operator>(const __normal_iterator<_Iterator, _Container>& __lhs,
		const __normal_iterator<_Iterator, _Container>& __rhs)
{ return __lhs.base() > __rhs.base(); }

template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs,
		const __normal_iterator<_IteratorR, _Container>& __rhs)
{ return __lhs.base() <= __rhs.base(); }

template<typename _Iterator, typename _Container>
	inline bool
operator<=(const __normal_iterator<_Iterator, _Container>& __lhs,
		const __normal_iterator<_Iterator, _Container>& __rhs)
{ return __lhs.base() <= __rhs.base(); }

template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs,
		const __normal_iterator<_IteratorR, _Container>& __rhs)
{ return __lhs.base() >= __rhs.base(); }

template<typename _Iterator, typename _Container>
	inline bool
operator>=(const __normal_iterator<_Iterator, _Container>& __lhs,
		const __normal_iterator<_Iterator, _Container>& __rhs)
{ return __lhs.base() >= __rhs.base(); }

template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline typename __normal_iterator<_IteratorL, _Container>::difference_type
operator-(const __normal_iterator<_IteratorL, _Container>& __lhs,
		const __normal_iterator<_IteratorR, _Container>& __rhs)
{ return __lhs.base() - __rhs.base(); }

template<typename _Iterator, typename _Container>
	inline typename __normal_iterator<_Iterator, _Container>::difference_type
operator-(const __normal_iterator<_Iterator, _Container>& __lhs,
		const __normal_iterator<_Iterator, _Container>& __rhs)
{ return __lhs.base() - __rhs.base(); }

template<typename _Iterator, typename _Container>
inline __normal_iterator<_Iterator, _Container>
operator+(typename __normal_iterator<_Iterator, _Container>::difference_type
		__n, const __normal_iterator<_Iterator, _Container>& __i)
{ return __normal_iterator<_Iterator, _Container>(__i.base() + __n); }

}
*/

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
				typedef __gnu_cxx::__normal_iterator<pointer, vector>			iterator;
				typedef __gnu_cxx::__normal_iterator<const_pointer, vector>		const_iterator;
				typedef std::reverse_iterator<iterator>							reverse_iterator;
				typedef std::reverse_iterator<const_iterator>					const_reverse_iterator;
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
							//_allocator.destroy(foo);
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
					void	assign(InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL,
							typename std::iterator_traits<InputIterator>::iterator_category* = NULL)
					{
						erase(begin(), end());
						insert(begin(), first, last);
					}
				void		assign(size_type n, const value_type& val)
				{
					erase(begin(), end());
					insert(begin(), n, val);
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
					const difference_type	diff = position - begin();

					if (size() + n > capacity())
						reserve(size() + n);
					for (difference_type i = size() - 1; i >= diff; i--)
					{
						_allocator.construct(&_m_start[i + n], _m_start[i]);
						_allocator.destroy(&_m_start[i]);
					}
					for (size_type i = diff; i < diff + n; i++)
						_allocator.construct(&_m_start[i], val);
					_m_finish += n;
					/*if (n == 0)
						return ;
					if (n > this->max_size())
						throw (std::length_error("vector::insert (fill)"));
					size_type pos_len = position - this->begin();
					if (size_type(_m_end_of_storage - _m_finish) >= n)
					{
						for (size_type i = 0; i < this->size() - pos_len; i++)
							_allocator.construct(_m_finish - i + (n - 1), *(_m_finish - i - 1));
						_m_finish += n;
						while (n)
						{
							_allocator.construct(&(*position) + (n - 1), val);
							n--;
						}
					}
					else
					{
						pointer new_start = pointer();
						pointer new_end = pointer();
						pointer new_end_capacity = pointer();

						int next_capacity = (this->capacity() > 0) ? (int)(this->size() * 2) : 1;
						new_start = _allocator.allocate(next_capacity);
						new_end_capacity = new_start + next_capacity;

						if (size_type(new_end_capacity - new_start) < this->size() + n)
						{
							if (new_start)
								_allocator.deallocate(new_start, new_start - new_end_capacity);
							next_capacity = this->size() + n;
							new_start = _allocator.allocate(next_capacity);
							new_end = new_start + this->size() + n;
							new_end_capacity = new_start + next_capacity;
						}

						new_end = new_start + this->size() + n;

						for (int i = 0; i < (position - begin()); i++)
							_allocator.construct(new_start + i, *(_m_start + i));
						for (size_type k = 0; k < n; k++)
							_allocator.construct(new_start + pos_len + k, val);
						for (size_type j = 0; j < (this->size() - pos_len); j++)
							_allocator.construct(new_end - j - 1, *(_m_finish - j - 1));

						for (size_type u = 0; u < this->size(); u++)
							_allocator.destroy(_m_start + u);
						_allocator.deallocate(_m_start, this->capacity());

						_m_start = new_start;
						_m_finish = new_end;
						_m_end_of_storage = new_end_capacity;
					}*/
				}
				template<typename InputIterator>
					void	insert(iterator pos, InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL,
							typename std::iterator_traits<InputIterator>::iterator_category* = NULL)
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
