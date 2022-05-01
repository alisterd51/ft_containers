/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 01:01:23 by antoine           #+#    #+#             */
/*   Updated: 2022/05/02 01:36:53 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include <string>
# include "type_traits.hpp"

namespace ft
{
	template <class Iterator>
		class iterator_traits
		{
			public:
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::iterator_category	iterator_category;
		};
	template <class T>
		class iterator_traits<T*>
		{
			public:
				typedef ptrdiff_t						difference_type;
				typedef T								value_type;
				typedef T*								pointer;
				typedef T&								reference;
				typedef std::random_access_iterator_tag	iterator_category;
		};
	template <class T>
		class iterator_traits<const T*>
		{
			public:
				typedef ptrdiff_t						difference_type;
				typedef T								value_type;
				typedef const T*						pointer;
				typedef const T&						reference;
				typedef std::random_access_iterator_tag	iterator_category;
		};
}

namespace ft
{
	template<typename Iter>
		class reverse_iterator
		{
			private:
				Iter iter;
			public:
				typedef Iter													iterator_type;
				typedef typename std::iterator_traits<Iter>::iterator_category	iterator_category;
				typedef typename std::iterator_traits<Iter>::value_type			value_type;
				typedef typename std::iterator_traits<Iter>::difference_type	difference_type;
				typedef typename std::iterator_traits<Iter>::pointer			pointer;
				typedef typename std::iterator_traits<Iter>::reference			reference;

				//constructor
				reverse_iterator() :
					iter()
			{
			}
				explicit reverse_iterator(iterator_type x) :
					iter(x)
			{
			}
				template<class U>
					reverse_iterator(const reverse_iterator<U>& other) :
						iter(other.base())
			{
			}
				//operator=
				//base
				iterator_type base() const
				{
					return (iter);
				}
				//operator*, operator->
				reference	operator*() const
				{
					Iter tmp = iter;
					return (*--tmp);
				}
				pointer		operator->() const
				{
					return (&operator*());
				}
				//operator[]
				reference	operator[](difference_type n) const
				{
					return (base()[-n-1]);
				}
				//operator++, +, +=, --, -, -=
				reverse_iterator& operator++()
				{
					--iter;
					return (*this);
				}
				reverse_iterator& operator--()
				{
					++iter;
					return (*this);
				}
				reverse_iterator  operator++(int)
				{
					reverse_iterator	temp = *this;

					++(*this);
					return (temp);
				}
				reverse_iterator operator--(int)
				{
					reverse_iterator	temp = *this;

					--(*this);
					return (temp);
				}
				reverse_iterator operator+(difference_type n) const
				{
					return (reverse_iterator(iter - n));
				}
				reverse_iterator operator-(difference_type n) const
				{
					return (reverse_iterator(iter + n));
				}
				reverse_iterator& operator+=(difference_type n)
				{
					iter -= n;
					return (*this);
				}
				reverse_iterator& operator-=(difference_type n)
				{
					iter += n;
					return (*this);
				}
		};

	template <class Iterator>
		bool operator== (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class Iterator>
		bool operator!= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class Iterator>
		bool operator<  (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class Iterator>
		bool operator<= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class Iterator>
		bool operator>  (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class Iterator>
		bool operator>= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class Iterator>
		reverse_iterator<Iterator> operator+ (
				typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& rev_it)
		{
			return (rev_it + n);
		}

	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator- (
				const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return (rhs.base() - lhs.base());
		}
	template<typename _IteratorL, typename _IteratorR>
		bool
		operator==(const reverse_iterator<_IteratorL>& __x,
				const reverse_iterator<_IteratorR>& __y)
		{
			return (__x.base() == __y.base());
		}

	template<typename _IteratorL, typename _IteratorR>
		bool
		operator<(const reverse_iterator<_IteratorL>& __x,
				const reverse_iterator<_IteratorR>& __y)
		{
			return (__y.base() < __x.base());
		}

	template<typename _IteratorL, typename _IteratorR>
		bool
		operator!=(const reverse_iterator<_IteratorL>& __x,
				const reverse_iterator<_IteratorR>& __y)
		{
			return (!(__x == __y));
		}

	template<typename _IteratorL, typename _IteratorR>
		bool
		operator>(const reverse_iterator<_IteratorL>& __x,
				const reverse_iterator<_IteratorR>& __y)
		{
			return (__y < __x);
		}

	template<typename _IteratorL, typename _IteratorR>
		bool
		operator<=(const reverse_iterator<_IteratorL>& __x,
				const reverse_iterator<_IteratorR>& __y)
		{
			return (!(__y < __x));
		}
	template<typename _IteratorL, typename _IteratorR>
		bool
		operator>=(const reverse_iterator<_IteratorL>& __x,
				const reverse_iterator<_IteratorR>& __y)
		{
			return (!(__x < __y));
		}
	template<typename _IteratorL, typename _IteratorR>
		typename reverse_iterator<_IteratorL>::difference_type
		operator-(const reverse_iterator<_IteratorL>& __x,
				const reverse_iterator<_IteratorR>& __y)
		{
			return (__y.base() - __x.base());
		}
}

namespace __ft
{
	template<typename _Iterator, typename _Container>
		class __normal_iterator
		{
			protected:
				_Iterator _M_current;

				typedef ft::iterator_traits<_Iterator>			traits_type;

			public:
				typedef _Iterator								iterator_type;
				typedef typename traits_type::iterator_category	iterator_category;
				typedef typename traits_type::value_type  		value_type;
				typedef typename traits_type::difference_type 	difference_type;
				typedef typename traits_type::reference 		reference;
				typedef typename traits_type::pointer   		pointer;

				__normal_iterator()
					: _M_current(_Iterator())
				{
				}

				explicit __normal_iterator(const _Iterator& __i)
					: _M_current(__i)
				{
				}

				// Allow iterator to const_iterator conversion
				template<typename _Iter>
					__normal_iterator(const __normal_iterator<_Iter,
							typename ft::enable_if<
							(ft::is_same<_Iter, typename _Container::pointer>::value),
							_Container>::type>& __i)
					: _M_current(__i.base())
					{
					}

				// Forward iterator requirements
				reference
					operator*() const
					{
						return (*_M_current);
					}

				pointer
					operator->() const
					{
						return (_M_current);
					}

				__normal_iterator&
					operator++()
					{
						++_M_current;
						return (*this);
					}

				__normal_iterator
					operator++(int)
					{
						return (__normal_iterator(_M_current++));
					}

				// Bidirectional iterator requirements
				__normal_iterator&
					operator--()
					{
						--_M_current;
						return (*this);
					}

				__normal_iterator
					operator--(int)
					{
						return (__normal_iterator(_M_current--));
					}

				// Random access iterator requirements
				reference
					operator[](difference_type __n) const
					{
						return (_M_current[__n]);
					}

				__normal_iterator&
					operator+=(difference_type __n)
					{
						_M_current += __n;
						return (*this);
					}

				__normal_iterator
					operator+(difference_type __n) const
					{
						return (__normal_iterator(_M_current + __n));
					}

				__normal_iterator&
					operator-=(difference_type __n)
					{
						_M_current -= __n;
						return (*this);
					}

				__normal_iterator
					operator-(difference_type __n) const
					{
						return (__normal_iterator(_M_current - __n));
					}

				const _Iterator&
					base() const
					{
						return (_M_current);
					}
		};

	// Forward iterator requirements
	template<typename _IteratorL, typename _IteratorR, typename _Container>
		bool
		operator==(const __normal_iterator<_IteratorL, _Container>& __lhs,
				const __normal_iterator<_IteratorR, _Container>& __rhs)
		{
			return (__lhs.base() == __rhs.base());
		}

	template<typename _Iterator, typename _Container>
		bool
		operator==(const __normal_iterator<_Iterator, _Container>& __lhs,
				const __normal_iterator<_Iterator, _Container>& __rhs)
		{
			return (__lhs.base() == __rhs.base());
		}

	template<typename _IteratorL, typename _IteratorR, typename _Container>
		bool
		operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs,
				const __normal_iterator<_IteratorR, _Container>& __rhs)
		{
			return __lhs.base() != __rhs.base();
		}

	template<typename _Iterator, typename _Container>
		bool
		operator!=(const __normal_iterator<_Iterator, _Container>& __lhs,
				const __normal_iterator<_Iterator, _Container>& __rhs)
		{
			return (__lhs.base() != __rhs.base());
		}

	// Random access iterator requirements
	template<typename _IteratorL, typename _IteratorR, typename _Container>
		bool
		operator<(const __normal_iterator<_IteratorL, _Container>& __lhs,
				const __normal_iterator<_IteratorR, _Container>& __rhs)
		{
			return (__lhs.base() < __rhs.base());
		}

	template<typename _Iterator, typename _Container>
		bool
		operator<(const __normal_iterator<_Iterator, _Container>& __lhs,
				const __normal_iterator<_Iterator, _Container>& __rhs)
		{
			return (__lhs.base() < __rhs.base());
		}

	template<typename _IteratorL, typename _IteratorR, typename _Container>
		bool
		operator>(const __normal_iterator<_IteratorL, _Container>& __lhs,
				const __normal_iterator<_IteratorR, _Container>& __rhs)
		{
			return (__lhs.base() > __rhs.base());
		}

	template<typename _Iterator, typename _Container>
		bool
		operator>(const __normal_iterator<_Iterator, _Container>& __lhs,
				const __normal_iterator<_Iterator, _Container>& __rhs)
		{
			return (__lhs.base() > __rhs.base());
		}

	template<typename _IteratorL, typename _IteratorR, typename _Container>
		bool
		operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs,
				const __normal_iterator<_IteratorR, _Container>& __rhs)
		{
			return (__lhs.base() <= __rhs.base());
		}

	template<typename _Iterator, typename _Container>
		bool
		operator<=(const __normal_iterator<_Iterator, _Container>& __lhs,
				const __normal_iterator<_Iterator, _Container>& __rhs)
		{
			return (__lhs.base() <= __rhs.base());
		}

	template<typename _IteratorL, typename _IteratorR, typename _Container>
		bool
		operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs,
				const __normal_iterator<_IteratorR, _Container>& __rhs)
		{
			return (__lhs.base() >= __rhs.base());
		}

	template<typename _Iterator, typename _Container>
		bool
		operator>=(const __normal_iterator<_Iterator, _Container>& __lhs,
				const __normal_iterator<_Iterator, _Container>& __rhs)
		{
			return (__lhs.base() >= __rhs.base());
		}

	template<typename _IteratorL, typename _IteratorR, typename _Container>
		typename __normal_iterator<_IteratorL, _Container>::difference_type
		operator-(const __normal_iterator<_IteratorL, _Container>& __lhs,
				const __normal_iterator<_IteratorR, _Container>& __rhs)
		{
			return (__lhs.base() - __rhs.base());
		}

	template<typename _Iterator, typename _Container>
		typename __normal_iterator<_Iterator, _Container>::difference_type
		operator-(const __normal_iterator<_Iterator, _Container>& __lhs,
				const __normal_iterator<_Iterator, _Container>& __rhs)
		{
			return (__lhs.base() - __rhs.base());
		}

	template<typename _Iterator, typename _Container>
		__normal_iterator<_Iterator, _Container>
		operator+(typename __normal_iterator<_Iterator, _Container>::difference_type
				__n, const __normal_iterator<_Iterator, _Container>& __i)
		{
			return (__normal_iterator<_Iterator, _Container>(__i.base() + __n));
		}
}

#endif
