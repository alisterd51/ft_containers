/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 01:01:23 by antoine           #+#    #+#             */
/*   Updated: 2022/04/05 17:41:27 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include <string>

namespace ft
{
	// 24.3, primitives:
	template<class Iterator> struct iterator_traits;
	template<class T> struct iterator_traits<T*>;
	template<class T> struct iterator_traits<const T*>;
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&> struct iterator;
	
	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag: public input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag: public forward_iterator_tag
	{
	};
	struct random_access_iterator_tag: public bidirectional_iterator_tag
	{
	};

	template<class Iterator> struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
	template<class T> struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};
	template<class T> struct iterator_traits<const T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<class Category, class T, class Distance, class Pointer, class Reference> struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	// 24.3.4, iterator operations:
	template <class InputIterator, class Distance>
		void advance(InputIterator& i, Distance n);
	template <class InputIterator>
		typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last);
	// 24.4, predefined iterators:
	template <class Iterator> class reverse_iterator;
	template <class Iterator> bool operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
	template <class Iterator> bool operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
	template <class Iterator> bool operator!=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
	template <class Iterator> bool operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
	template <class Iterator> bool operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
	template <class Iterator> bool operator<=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
	template <class Iterator> typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
	template <class Iterator> reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x);
	template <class Container> class back_insert_iterator;
	template <class Container> back_insert_iterator<Container> back_inserter(Container& x);
	template <class Container> class front_insert_iterator;
	template <class Container> front_insert_iterator<Container> front_inserter(Container& x);
	template <class Container> class insert_iterator;
	template <class Container, class Iterator> insert_iterator<Container> inserter(Container& x, Iterator i);
	// 24.5, stream iterators:
	template <class T, class charT = char, class traits = std::char_traits<charT>, class Distance = ptrdiff_t>
		class istream_iterator;
	template <class T, class charT, class traits, class Distance>
		bool operator==(const istream_iterator<T,charT,traits,Distance>& x, const istream_iterator<T,charT,traits,Distance>& y);
	template <class T, class charT, class traits, class Distance>
		bool operator!=(const istream_iterator<T,charT,traits,Distance>& x, const istream_iterator<T,charT,traits,Distance>& y);
	template <class T, class charT = char, class traits = std::char_traits<charT> >
		class ostream_iterator;
	template<class charT, class traits = std::char_traits<charT> >
		class istreambuf_iterator;
	template <class charT, class traits>
		bool operator==(const istreambuf_iterator<charT,traits>& a, const istreambuf_iterator<charT,traits>& b);
	template <class charT, class traits>
		bool operator!=(const istreambuf_iterator<charT,traits>& a, const istreambuf_iterator<charT,traits>& b);
	template <class charT, class traits = std::char_traits<charT> >
		class ostreambuf_iterator;
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
