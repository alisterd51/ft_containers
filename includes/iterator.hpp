/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 01:01:23 by antoine           #+#    #+#             */
/*   Updated: 2022/04/06 00:33:30 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include <string>

namespace ft
{
	struct	input_iterator_tag
	{
	};
	struct	output_iterator_tag
	{
	};
	struct	forward_iterator_tag : public input_iterator_tag
	{
	};
	struct	bidirectional_iterator_tag : public forward_iterator_tag
	{
	};
	struct	random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};

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
				typedef random_access_iterator_tag		iterator_category;
		};
	template <class T>
		class iterator_traits<const T*>
		{
			public:
				typedef ptrdiff_t						difference_type;
				typedef T								value_type;
				typedef const T*						pointer;
				typedef const T&						reference;
				typedef random_access_iterator_tag		iterator_category;
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
				reverse_iterator() : iter()
			{
			}
				explicit reverse_iterator(iterator_type x) : iter(x)
			{
			}
				template<class U>
					reverse_iterator(const reverse_iterator<U>& other) : iter(other.base())
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
					return &(operator*());
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
}

#endif
