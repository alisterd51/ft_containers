/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:44:32 by antoine           #+#    #+#             */
/*   Updated: 2022/05/02 00:25:46 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# define _FT_RB_TREE_BLACK	0
# define _FT_RB_TREE_RED	1
# define _FT_RB_TREE_LEAF	NULL

namespace ft
{
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		class _Rb_tree
		{
			private:
				typedef struct s_node_rb_tree	node_rb_tree;
				struct	s_node_rb_tree
				{
					private:
						node_rb_tree	*_left;
						node_rb_tree	*_right;
						node_rb_tree	*_parent;
						int				_color;
						_Key			_key;
						_Val			_value;
					public:
						_Key			get_key()
						{
							return (this->_key);
						}
						_Val			get_value()
						{
							return (this->_value);
						}
						int				color()
						{
							return (this->_color);
						}
						node_rb_tree    *left()
						{
							return (this->_left)
						}
						node_rb_tree    *right()
						{
							return (this->_right)
						}
						node_rb_tree    *parent()
						{
							return (this->_parent)
						}
						node_rb_tree	*grandparent()
						{
							if (this->parent() == NULL)
								return (NULL);
							return (this->parent()->parent());
						}
						node_rb_tree	*brother()
						{
							if (this->parent() == NULL)
								return (NULL);
							if (this == this->parent()->left())
								return (this->parent()->right());
							else
								return (this->parent()->left());
						}
						node_rb_tree	*uncle()
						{
							if (this->grandparent() == NULL)
								return (NULL);
							return (this->parent()->brother());
						}
				};
				//rotation
				void	left_rotation(node_rb_tree *x)
				{
					node_rb_tree	*y = x->right();

					x->right() = y->left();
					if (y->left != _FT_RB_TREE_LEAF)
						y->right()->parent() = x;
					y->parent() = x->parent();
					if (c->parent() == NULL)
						x = y;
					else if (x ==  x->parent()->left())
						x->parent()->left() = y;
					else
						 x->parent()->right() = y;
					y->left() = x;
					x->parent() = y;
				}
				void	right_rotation(node_rb_tree *x)
				{
					node_rb_tree	*y = x->left();

					x->left() = y->right();
					if (y->right != _FT_RB_TREE_LEAF)
						y->left()->parent() = x;
					y->parent() = x->parent();
					if (c->parent() == NULL)
						x = y;
					else if (x ==  x->parent()->right())
						x->parent()->right() = y;
					else
						 x->parent()->left() = y;
					y->right() = x;
					x->parent() = y;
				}
				//search
				//insertion
				node_rb_tree *insertion(node_rb_tree *root, node_rb_tree *n)
				{
					// Insertion d'un nouveau nœud dans l'arbre
					insertion_recursif(root, n);
					// Réparation de l'arbre au cas où les propriétés rouge-noir seraient violées
					insertion_repare_arbre(n);
					// Recherche de la nouvelle racine à renvoyer
					root = n;
					while (root->parent() != NULL)
						root = root->parent();
					return (root);
				}
				void recursive_insertion(node_rb_tree *root, node_rb_tree *n)
				{
					// Descente récursive dans l'arbre jusqu'à atteindre une feuille
					if (root != NULL && n->get_key() < root->get_key()) {
						if (root->left() != FEUILLE)
						{
							recursive_insertion(root->left(), n);
							return ;
						}
						else
							root->left() = n;
					}
					else if (root != NULL) {
						if (root->right() != _FT_RB_TREE_LEAF)
						{
							recursive_insertion(root->right(), n);
							return;
						}
						else
							root->right() = n;
					}

					// Insertion du nouveau noeud n
					n->parent() = root;
					n->left() = _FT_RB_TREE_LEAF; // NIL
					n->right() = _FT_RB_TREE_LEAF; // NIL
					n->color() = _FT_RB_TREE_RED;
				}
				//balancing
				void	balancing(node_rb_tree *n)
				{
					if (n->parent() == NULL)
						balancing_cas1(n);
					else if (n->parent()->color() == _FT_RB_TREE_BLACK)
						balancing_cas2(n);
					else if (n->uncle()->color() == _FT_RB_TREE_RED)
						balancing_cas3(n);
					else
						balancing_cas4(n);
				}
				void	balancing_cas1(node_rb_tree *n)
				{
					if (n->parent() == NULL)
						n->color() = _FT_RB_TREE_BLACK;
				}
				void	balancing_cas2(node_rb_tree *n)
				{
					return ;
				}
				void	balancing_cas3(node_rb_tree *n)
				{
					n->parent()->color() = _FT_RB_TREE_BLACK;
					n->uncle()->color() = _FT_RB_TREE_BLACK;
					n->grandparent()->color() = _FT_RB_TREE_RED;
					balancing(n->grandparent());
				}
				void	balancing_cas4(node_rb_tree *n)
				{
					if (n == n->grandparent()->left()->right())
					{
						left_rotation(n->parent());
						n = n->left();
					}
					else if (n == n->grandparent()->right()->left())
					{
						right_rotation(n->parent());
						n = n->right();
					}
					balancing_cas5(n);
				}
				void	balancing_cas5(node_rb_tree *n)
				{
					if (n == n->parent()->left())
						right_rotation(n->grandparent());
					else
						left_rotation(n->grandparent());
					n->parent()->color() = _FT_RB_TREE_BLACK;
					n->grandparent()->color() = _FT_RB_TREE_RED;
				}
			public:
		};
}

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
		class map
		{
			public:
				// types:
				typedef Key										key_type;
				typedef T										mapped_type;
				typedef std::pair<const Key, T>					value_type;
				typedef Compare									key_compare;
				typedef Allocator								allocator_type;
			private:
				typedef typename __gnu_cxx::__alloc_traits<Allocator>::template
					rebind<value_type>::other					_Pair_alloc_type;
				typedef _Rb_tree<key_type, value_type, std::_Select1st<value_type>,
						key_compare, _Pair_alloc_type>			_Rep_type;
			public:
				typedef typename Allocator::reference			reference;
				typedef typename Allocator::const_reference 	const_reference;
				typedef typename _Rep_type::iterator			iterator;
				typedef typename _Rep_type::const_iterator		const_iterator;
				typedef typename _Rep_type::size_type			size_type;
				typedef typename _Rep_type::difference_type		difference_type;
				typedef typename Allocator::pointer				pointer;
				typedef typename Allocator::const_pointer		const_pointer;
				typedef std::reverse_iterator<iterator>			reverse_iterator;
				typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
				class value_compare
					: public std::binary_function<value_type,value_type,bool> {
						friend class map;
						protected:
						Compare comp;
						value_compare(Compare c) : comp(c) {}
						public:
						bool operator()(const value_type& x, const value_type& y) const {
							return comp(x.first, y.first);
						}
					};
				// 23.3.1.1 construct/copy/destroy:
				explicit map(const Compare& comp = Compare(),
						const Allocator& = Allocator());
				template <class InputIterator>
					map(InputIterator first, InputIterator last,
							const Compare& comp = Compare(), const Allocator& = Allocator());
				map(const map<Key,T,Compare,Allocator>& x);
				~map();
				map<Key,T,Compare,Allocator>&
					operator=(const map<Key,T,Compare,Allocator>& x);
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
				bool empty() const;
				size_type size() const;
				size_type max_size() const;
				// 23.3.1.2 element access:
				T& operator[](const key_type& x);
				// modifiers:
				std::pair<iterator, bool> insert(const value_type& x);
				iterator insert(iterator position, const value_type& x);
				template <class InputIterator>
					void insert(InputIterator first, InputIterator last);
				void erase(iterator position);
				size_type erase(const key_type& x);
				void erase(iterator first, iterator last);
				void swap(map<Key,T,Compare,Allocator>&);
				void clear();
				// observers:
				key_compare key_comp() const;
				value_compare value_comp() const;
				// 23.3.1.3 map operations:
				iterator find(const key_type& x);
				const_iterator find(const key_type& x) const;
				size_type count(const key_type& x) const;
				iterator lower_bound(const key_type& x);
				const_iterator lower_bound(const key_type& x) const;
				iterator upper_bound(const key_type& x);
				const_iterator upper_bound(const key_type& x) const;
				std::pair<iterator,iterator>
					equal_range(const key_type& x);
				std::pair<const_iterator,const_iterator>
					equal_range(const key_type& x) const;
		};
	template <class Key, class T, class Compare, class Allocator>
		bool operator==(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
		bool operator< (const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
		bool operator!=(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
		bool operator> (const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
		bool operator>=(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
		bool operator<=(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y);
	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
		void swap(map<Key,T,Compare,Allocator>& x,
				map<Key,T,Compare,Allocator>& y);
}

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
		class multimap
		{
			public:
				// types:
				typedef Key										key_type;
				typedef T										mapped_type;
				typedef std::pair<const Key,T>					value_type;
				typedef Compare									key_compare;
				typedef Allocator								allocator_type;
			private:
				typedef typename __gnu_cxx::__alloc_traits<Allocator>::template
					rebind<value_type>::other					_Pair_alloc_type;
				typedef _Rb_tree<key_type, value_type, std::_Select1st<value_type>,
						key_compare, _Pair_alloc_type>			_Rep_type;
			public:
				typedef typename Allocator::reference			reference;
				typedef typename Allocator::const_reference		const_reference;
				typedef typename _Rep_type::iterator			iterator;
				typedef typename _Rep_type::const_iterator		const_iterator;
				typedef typename _Rep_type::size_type			size_type;
				typedef typename _Rep_type::difference_type		difference_type;
				typedef typename Allocator::pointer				pointer;
				typedef typename Allocator::const_pointer		const_pointer;
				typedef std::reverse_iterator<iterator>			reverse_iterator;
				typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
				class value_compare
					: public std::binary_function<value_type, value_type, bool>
				{
					friend class multimap;
					protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
					public:
					bool operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
				};
				// construct/copy/destroy:
				explicit multimap(const Compare& comp = Compare(),
						const Allocator& = Allocator());
				template <class InputIterator>
					multimap(InputIterator first, InputIterator last,
							const Compare& comp = Compare(),
							const Allocator& = Allocator());
				multimap(const multimap<Key,T,Compare,Allocator>& x);
				~multimap();
				multimap<Key,T,Compare,Allocator>&
					operator=(const multimap<Key,T,Compare,Allocator>& x);
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
				bool empty() const;
				size_type size() const;
				size_type max_size() const;
				// modifiers:
				iterator insert(const value_type& x);
				iterator insert(iterator position, const value_type& x);
				template <class InputIterator>
					void insert(InputIterator first, InputIterator last);
				void erase(iterator position);
				size_type erase(const key_type& x);
				void erase(iterator first, iterator last);
				void swap(multimap<Key,T,Compare,Allocator>&);
				void clear();
				// observers:
				key_compare key_comp() const;
				value_compare value_comp() const;
				// map operations:
				iterator find(const key_type& x);
				const_iterator find(const key_type& x) const;
				size_type count(const key_type& x) const;
				iterator lower_bound(const key_type& x);
				const_iterator lower_bound(const key_type& x) const;
				iterator upper_bound(const key_type& x);
				const_iterator upper_bound(const key_type& x) const;
				std::pair<iterator,iterator>
					equal_range(const key_type& x);
				std::pair<const_iterator,const_iterator>
					equal_range(const key_type& x) const;
		};
	template <class Key, class T, class Compare, class Allocator>
		bool operator==(const multimap<Key,T,Compare,Allocator>& x,
				const multimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
		bool operator< (const multimap<Key,T,Compare,Allocator>& x,
				const multimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
		bool operator!=(const multimap<Key,T,Compare,Allocator>& x,
				const multimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
		bool operator> (const multimap<Key,T,Compare,Allocator>& x,
				const multimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
		bool operator>=(const multimap<Key,T,Compare,Allocator>& x,
				const multimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator>
		bool operator<=(const multimap<Key,T,Compare,Allocator>& x,
				const multimap<Key,T,Compare,Allocator>& y);
	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
		void swap(multimap<Key,T,Compare,Allocator>& x,
				multimap<Key,T,Compare,Allocator>& y);
}

#endif
