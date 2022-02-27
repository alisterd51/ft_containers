/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:56:36 by antoine           #+#    #+#             */
/*   Updated: 2022/02/27 00:57:14 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITSET_HPP
# define BITSET_HPP

namespace ft
{
	template<size_t N> class bitset {
		public:
			// bit reference:
			class reference {
				friend class bitset;
				reference();
				public:
				~reference();
				reference& operator=(bool x); // for b[i] = x;
				reference& operator=(const reference&); // for b[i] = b[j];
				bool operator~() const; // flips the bit
				operator bool() const; // for x = b[i];
				reference& flip(); // for b[i].flip();
			};
			// 23.3.5.1 constructors:
			bitset();
			bitset(unsigned long val);
			template<class charT, class traits, class Allocator>
				explicit bitset(
						const basic_string<charT,traits,Allocator>& str,
						typename basic_string<charT,traits,Allocator>::size_type pos = 0,
						typename basic_string<charT,traits,Allocator>::size_type n =
						basic_string<charT,traits,Allocator>::npos);
			// 23.3.5.2 bitset operations:
			bitset<N>& operator&=(const bitset<N>& rhs);
			bitset<N>& operator|=(const bitset<N>& rhs);
			bitset<N>& operator^=(const bitset<N>& rhs);
			bitset<N>& operator<<=(size_t pos);
			bitset<N>& operator>>=(size_t pos);
			bitset<N>& set();
			bitset<N>& set(size_t pos, int val = true);
			bitset<N>& reset();
			bitset<N>& reset(size_t pos);
			bitset<N> operator~() const;
			bitset<N>& flip();
			bitset<N>& flip(size_t pos);
			// element access:
			reference operator[](size_t pos); // for b[i];
			unsigned long to_ulong() const;
			template <class charT, class traits, class Allocator>
				basic_string<charT, traits, Allocator> to_string() const;
			size_t count() const;
			size_t size() const;
			bool operator==(const bitset<N>& rhs) const;
			bool operator!=(const bitset<N>& rhs) const;
			bool test(size_t pos) const;
			bool any() const;
			bool none() const;
			bitset<N> operator<<(size_t pos) const;
			bitset<N> operator>>(size_t pos) const;
	};
}

#endif
