/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:38:28 by antoine           #+#    #+#             */
/*   Updated: 2022/02/27 00:44:03 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

namespace ft
{
	template <class T, class Allocator = allocator<T> >
		class vector
		{
			public:
				// types:
				typedef typename Allocator::reference reference;
				typedef typename Allocator::const_reference const_reference;
				typedef implementation defined iterator; // See 23.1
				typedef implementation defined const_iterator; // See 23.1
				typedef implementation defined size_type; // See 23.1
				typedef implementation defined difference_type;// See 23.1
				typedef T value_type;
				typedef Allocator allocator_type;
				typedef typename Allocator::pointer pointer;
				typedef typename Allocator::const_pointer const_pointer
					typedef std::reverse_iterator<iterator> reverse_iterator;
				typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
				// 23.2.4.1 construct/copy/destroy:
				explicit vector(const Allocator& = Allocator());
				explicit vector(size_type n, const T& value = T(),
						const Allocator& = Allocator());
				template <class InputIterator>
					vector(InputIterator first, InputIterator last,
							const Allocator& = Allocator());
				vector(const vector<T,Allocator>& x);
				~vector();
				vector<T,Allocator>& operator=(const vector<T,Allocator>& x);
				template <class InputIterator>
					void assign(InputIterator first, InputIterator last);
				void assign(size_type n, const T& u);
				allocator_type get_allocator() const;
				// iterators:
				iterator begin();
				const_iterator begin() const;
				iterator end();
				const_iterator end() const;
				reverse_iterator rbegin();
				const_reverse_iterator rbegin() const;
				reverse_iterator rend();
				const_reverse_iterator rend() const;
				// 23.2.4.2 capacity:
				size_type size() const;
				size_type max_size() const;
				void resize(size_type sz, T c = T());
				size_type capacity() const;
				bool empty() const;
				void reserve(size_type n);
				// element access:
				reference operator[](size_type n);
				const_reference operator[](size_type n) const;
				const_reference at(size_type n) const;
				reference at(size_type n);
				reference front();
				const_reference front() const;
				reference back();
				const_reference back() const;
				// 23.2.4.3 modifiers:
				void push_back(const T& x);
				void pop_back();
				iterator insert(iterator position, const T& x);
				void insert(iterator position, size_type n, const T& x);
				template <class InputIterator>
					void insert(iterator position,
							InputIterator first, InputIterator last);
				iterator erase(iterator position);
				iterator erase(iterator first, iterator last);
				void swap(vector<T,Allocator>&);
				void clear();
		};
	template <class T, class Allocator>
		bool operator==(const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator< (const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator!=(const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator> (const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator>=(const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator<=(const vector<T,Allocator>& x,
				const vector<T,Allocator>& y);
	// specialized algorithms:
	template <class T, class Allocator>
		void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}

namespace ft
{
	template <class Allocator> class vector<bool, Allocator>
	{
		public:
			// types:
			typedef bool const_reference;
			typedef implementation defined iterator; // See 23.1
			typedef implementation defined const_iterator; // See 23.1
			typedef implementation defined size_type; // See 23.1
			typedef implementation defined difference_type;// See 23.1
			typedef bool value_type;
			typedef Allocator allocator_type;
			typedef implementation defined pointer;
			typedef implementation defined const_pointer
				typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
			// bit reference:
			class reference {
				friend class vector;
				reference();
				public:
				~reference();
				operator bool() const;
				reference& operator=(const bool x);
				reference& operator=(const reference& x);
				void flip(); // flips the bit
			};
			// construct/copy/destroy:
			explicit vector(const Allocator& = Allocator());
			explicit vector(size_type n, const bool& value = bool(),
					const Allocator& = Allocator());
			template <class InputIterator>
				vector(InputIterator first, InputIterator last,
						const Allocator& = Allocator());
			vector(const vector<bool,Allocator>& x);
			~vector();
			vector<bool,Allocator>& operator=(const vector<bool,Allocator>& x);
			template <class InputIterator>
				void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const T& t);
			allocator_type get_allocator() const;
			// iterators:
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			// capacity:
			size_type size() const;
			size_type max_size() const;
			void resize(size_type sz, bool c = false);
			size_type capacity() const;
			bool empty() const;
			void reserve(size_type n);
			// element access:
			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			const_reference at(size_type n) const;
			reference at(size_type n);
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			// modifiers:
			void push_back(const bool& x);
			void pop_back();
			iterator insert(iterator position, const bool& x);
			void insert (iterator position, size_type n, const bool& x);
			template <class InputIterator>
				void insert(iterator position,
						InputIterator first, InputIterator last);
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void swap(vector<bool,Allocator>&);
			static void swap(reference x, reference y);
			void flip(); // flips all bits
			void clear();
	};
	template <class Allocator>
		bool operator==(const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		bool operator< (const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		bool operator!=(const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		bool operator> (const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		bool operator>=(const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	template <class Allocator>
		bool operator<=(const vector<bool,Allocator>& x,
				const vector<bool,Allocator>& y);
	// specialized algorithms:
	template <class Allocator>
		void swap(vector<bool,Allocator>& x, vector<bool,Allocator>& y);
}

#endif
