/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:38:28 by antoine           #+#    #+#             */
/*   Updated: 2022/04/04 22:47:36 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iterator>

template <typename T>
	class iterator_vector : std::iterator_traits<T*>
{
	public:
		// types:
		typedef typename std::allocator<T>::pointer pointer;
		// construct/copy/destroy:
		iterator_vector(pointer p) :
			_p(p)
		{
			return ;
		}
		// comparison
		bool operator!=(iterator_vector const &rhs) const
		{
			return (this->_p != rhs._p);
		}
		iterator_vector& operator++()
		{
			this->_p = this->_p + 1;
			return (*this);
		}
		iterator_vector operator++(int)
		{
			iterator_vector	post(*this);
			operator++();
			return (post);
		}
		T& operator* ()
		{
			return (*this->_p);
		}
	private:
		pointer	_p;
};

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

#endif
