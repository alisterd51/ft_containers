/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:44:32 by antoine           #+#    #+#             */
/*   Updated: 2022/05/26 18:27:02 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <algorithm>
# include <iostream>
# include <iomanip>
# include <cassert>
# include "iterator.hpp"
# include "utility.hpp"

# define _FT_RB_TREE_BLACK	0
# define _FT_RB_TREE_RED	1
# define _FT_RB_TREE_LEAF	NULL

# define _FT_BLACK			"\033[1;37m"
# define _FT_RED			"\033[1;31m"
# define _FT_RESET			"\033[0m"

namespace __ft
{
	//https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		struct RBnode
		{
			RBnode		*parent;
			RBnode		*left;
			RBnode		*right;
			int			color;
			_Val		*value;
			_Alloc		_allocator;
			_Compare	_compare;

			RBnode(_Val newValue) :
				parent(_FT_RB_TREE_LEAF),
				left(_FT_RB_TREE_LEAF),
				right(_FT_RB_TREE_LEAF),
				color(_FT_RB_TREE_RED),
				_allocator(_Alloc()),
				_compare(_Compare())
			{
				value = _allocator.allocate(1);
				_allocator.construct(value, newValue);
			}
			~RBnode()
			{
				_allocator.destroy(value);
				_allocator.deallocate(value, 1);
			}
			RBnode	*grandparent()
			{
				if (this->parent == NULL)
					return (NULL);
				return (this->parent->parent);
			}
			RBnode	*brother()
			{
				RBnode	*p = this->parent;

				if (p == NULL)
					return (NULL);
				if (this == p->left)
					return (p->right);
				else
					return (p->left);
			}
			RBnode	*uncle()
			{
				if (this->grandparent() == NULL)
					return (NULL);
				return (this->parent->brother());
			}
			RBnode	*next()
			{
				RBnode	*n;
				RBnode	*prev = NULL;

				n = this;
				while (n && n->value->first <= this->value->first)//
				{

					//right && diff de prev
					//parent
					if (n->right && n->right != prev)
					{
						prev = n;
						n = n->right;
					}
					else
					{
						prev = n;
						n = n->parent;
					}
				}
				while (n && n->left && n->left->value->first > this->value->first)
					n = n->left;
				return (n);
			}
			RBnode	*recursive_copy(RBnode *p)
			{
				RBnode	*new_node = new RBnode(*(this->value));

				new_node->parent = p;
				new_node->color = this->color;
				if (this->left != NULL)
					new_node->left = this->left->recursive_copy(new_node);
				else
					new_node->left = NULL;
				if (this->right != NULL)
					new_node->right = this->right->recursive_copy(new_node);
				else
					new_node->right = NULL;
				return (new_node);
			}
			void	insert(RBnode *new_node)
			{
				if (_compare(this->value->first, new_node->value->first))
				{
					if (this->left != NULL)
						this->left->insert(new_node);
					else
					{
						new_node->parent = this;
						this->left = new_node;
					}
				}
				else
				{
					if (this->right != NULL)
						this->right->insert(new_node);
					else
					{
						new_node->parent = this;
						this->right = new_node;
					}
				}
			}
			void	print_recursive_space()
			{
				if (parent == NULL)
					return ;
				parent->print_recursive_space();
				if (parent && parent->parent
						&& ((parent->left == this && parent->parent->right == parent)
							|| (parent->right == this && parent->parent->left == parent)))
					std::cout << "║";
				else
					std::cout << " ";
			}
			void	print_direction(int direction)
			{
				if (direction == 0)
					std::cout << "═";
				else if (direction == 1)
					std::cout << "╔";
				else if (direction == 2)
					std::cout << "╚";
				else
					std::cout << " ";
			}
			void	print_bypass()
			{
				if (left == _FT_RB_TREE_LEAF && right == _FT_RB_TREE_LEAF)
					std::cout << "═";
				else if (left != _FT_RB_TREE_LEAF && right != _FT_RB_TREE_LEAF)
					std::cout << "╬";
				else if (left == _FT_RB_TREE_LEAF && right != _FT_RB_TREE_LEAF)
					std::cout << "╦";
				else if (left != _FT_RB_TREE_LEAF && right == _FT_RB_TREE_LEAF)
					std::cout << "╩";
			}
			void	print_node(int direction)
			{
				print_recursive_space();
				print_direction(direction);
				print_bypass();
				std::cout << *this << std::endl;
			}
			void	recursive_print(int deep, int direction)
			{
				if (deep < 0)
					return ;
				if (this->left != _FT_RB_TREE_LEAF)
					this->left->recursive_print(deep + 1, 1);
				print_node(direction);
				if (this->right != _FT_RB_TREE_LEAF)
					this->right->recursive_print(deep + 1, 2);
			}
		};

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
		std::ostream	&operator<<(std::ostream &o, __ft::RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> const &i)
		{
			o << (i.color == _FT_RB_TREE_BLACK ? _FT_BLACK : _FT_RED)
				<< i.value->first << ": " << i.value->second << _FT_RESET;
			return (o);
		}

	template<typename _Tp, typename _RBnode>
		class Rbtree_iterator
		{
			private:
				typedef _RBnode*						node_pointer;
			public:
				typedef std::bidirectional_iterator_tag	iterator_category;
				typedef _Tp								value_type;
				typedef std::ptrdiff_t					difference_type;
				typedef _Tp*							pointer;
				typedef _Tp&							reference;
			private:
				node_pointer	_node;

				template<typename _Tp1, typename _RBnode1>
					friend bool	operator==(const Rbtree_iterator<_Tp1, _RBnode1>&,
							const Rbtree_iterator<_Tp1, _RBnode1>&);
			public:
				Rbtree_iterator() :
					_node()
			{
			}
				Rbtree_iterator(const Rbtree_iterator& x) :
					_node()
			{
				*this = x;
			}
				Rbtree_iterator(const node_pointer& node) :
					_node(node)
			{
			}
				Rbtree_iterator	&operator=(const Rbtree_iterator& x)
				{
					if (this != &x)
					{
						this->_node = x._node;
					}
					return (*this);
				}
				Rbtree_iterator&
					operator++()
					{
						if (_node)
							_node = _node->next();
						return (*this);
					}

				Rbtree_iterator
					operator++(int)
					{
						_RBnode	*prev_node = _node;

						if (_node)
							_node = _node.next();
						return (Rbtree_iterator(_node));
					}
		};
	template<typename _Tp, typename _RBnode>
		bool	operator==(const Rbtree_iterator<_Tp, _RBnode>& lhs,
				const Rbtree_iterator<_Tp, _RBnode>& rhs)
		{
			return (lhs._node == rhs._node);
		}
	template<typename _Tp, typename _RBnode>
		bool	operator!=(const Rbtree_iterator<_Tp, _RBnode>& lhs,
				const Rbtree_iterator<_Tp, _RBnode>& rhs)
		{
			return (!(lhs == rhs));
		}

	template<typename _Tp, typename _RBnode>
		class Rbtree_const_iterator
		{
			public:
				typedef std::bidirectional_iterator_tag	iterator_category;
				typedef _Tp								value_type;
				typedef std::ptrdiff_t					difference_type;
				typedef _Tp*							pointer;
				typedef _Tp&							reference;
		};

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		struct RBtree
		{
			private:
				typedef	__ft::RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc>	_RBnode;
				typedef	std::allocator<_RBnode>					_Alloc_node;
			public:
				typedef _Val									value_type;
				typedef	Rbtree_iterator<value_type, _RBnode>	iterator;
				typedef	Rbtree_const_iterator<value_type, _RBnode>	const_iterator;
				typedef	ft::reverse_iterator<iterator>			reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
				typedef std::size_t								size_type;
				typedef	std::ptrdiff_t							difference_type;

				RBtree() :
					root(NULL),
					_compare(_Compare()),
					_alloc_node(_Alloc_node()),
					_size(0)
			{
			}
				~RBtree()
				{
					recursive_remove(this->root);
				}
				void	clear()
				{
					recursive_remove(this->root);
					this->root = NULL;
					this->_size = 0;
				}
				RBtree&	operator=(const RBtree& x)
				{
					if (this != &x)
					{
						recursive_remove(this->root);
						if (x.root != NULL)
							this->root = x.root->recursive_copy(NULL);
						else
							this->root = NULL;
						this->_size = x._size;
					}
					return (*this);
				}
				_RBnode	*min()
				{
					_RBnode	*min = root;

					while (min && min->left)
						min = min->left;
					return (min);
				}
				_RBnode	*max()
				{
					_RBnode	*max = root;

					while (max && max->left)
						max = max->right;
					return (max);
				}
				iterator	begin()
				{
					return (iterator(min()));
				}
				iterator	end()
				{
					return (++iterator(max()));
				}
				void	recursive_remove(_RBnode *node)
				{
					if (node != NULL)
					{
						recursive_remove(node->left);
						recursive_remove(node->right);
						delete node;
					}
				}
				_RBnode	*right_rotation(_RBnode *subtree)
				{
					_RBnode	*G = subtree->parent;
					_RBnode	*S = subtree->left;
					_RBnode	*C;

					assert(S != NULL);
					C = S->right;
					subtree->left = C;
					if (C != NULL)
						C->parent = subtree;
					S->right = subtree;
					subtree->parent = S;
					S->parent = G;
					if (G != NULL)
					{
						if (subtree == G->right)
							G->right = S;
						else
							G->left = S;
					}
					else
						this->root = S;
					return (S);
				}
				_RBnode	*left_rotation(_RBnode *subtree)
				{
					_RBnode	*G = subtree->parent;
					_RBnode	*S = subtree->right;
					_RBnode	*C;

					assert(S != NULL);
					C = S->left;
					subtree->right = C;
					if (C != NULL)
						C->parent = subtree;
					S->left = subtree;
					subtree->parent = S;
					S->parent = G;
					if (G != NULL)
					{
						if (subtree == G->right)
							G->right = S;
						else
							G->left = S;
					}
					else
						this->root = S;
					return (S);
				}
				_RBnode	*search(_Key key)
				{
					_RBnode	*node;

					node = this->root;
					while (node && (_compare(node->value->first, key)
								|| _compare(key, node->value->first)))
					{
						if (_compare(node->value->first, key))
							node = node->left;
						else
							node = node->right;
					}
					return (node);
				}
				void	balancing_double_black(_RBnode *db_node, _RBnode *db_parent)
				{
					_RBnode	*db_brother = NULL;
					_RBnode	*db_furthest_nephew = NULL;
					_RBnode	*db_furthest_nephew_brother = NULL;
					_RBnode	*db_grandparent = NULL;

					if (db_parent)
					{
						if (db_parent->left == db_node)
						{
							db_brother = db_parent->right;
							if (db_brother != NULL)
							{
								db_furthest_nephew = db_brother->right;
								db_furthest_nephew_brother = db_brother->left;
							}
						}
						else
						{
							db_brother = db_parent->left;
							if (db_brother != NULL)
							{
								db_furthest_nephew = db_brother->left;
								db_furthest_nephew_brother = db_brother->right;
							}
						}
						db_grandparent = db_parent->parent;
					}
					//cas 0 le nœud x est la racine de l'arbre
					if (db_parent == NULL)
					{
						if (db_node != NULL)
							db_node->color = _FT_RB_TREE_BLACK;
					}
					//cas 1 le frère f de x est noir.
					else if (db_brother == NULL || db_brother->color == _FT_RB_TREE_BLACK)
					{
						//cas 1a les deux fils g et d de f sont noirs.
						if (db_brother
								&& (db_brother->left == NULL || db_brother->left->color == _FT_RB_TREE_BLACK)
								&& (db_brother->right == NULL || db_brother->right->color == _FT_RB_TREE_BLACK))
						{
							db_brother->color = _FT_RB_TREE_RED;
							if (db_parent && db_parent->color == _FT_RB_TREE_RED)
								db_parent->color = _FT_RB_TREE_BLACK;
							else
								balancing_double_black(db_parent, db_grandparent);
						}
						//cas 1b le fils droit d de f est rouge.
						else if (db_furthest_nephew != NULL && db_furthest_nephew->color == _FT_RB_TREE_RED)
						{
							if (db_brother == db_parent->right)
								left_rotation(db_parent);
							else
								right_rotation(db_parent);
							db_brother->color = db_parent->color;
							db_node->color = _FT_RB_TREE_BLACK;
							db_parent->color = _FT_RB_TREE_BLACK;
							db_furthest_nephew->color = _FT_RB_TREE_BLACK;
						}
						//cas 1c le fils droit d est noir et le fils gauche g est rouge.
						else if (db_furthest_nephew_brother != NULL
								&& db_furthest_nephew_brother->color == _FT_RB_TREE_RED)
						{
							if (db_brother == db_parent->right)
							{
								right_rotation(db_brother);
								db_furthest_nephew_brother->color = _FT_RB_TREE_BLACK;
								db_brother->color = _FT_RB_TREE_RED;
								left_rotation(db_parent);
								db_brother->color = _FT_RB_TREE_BLACK;
							}
							else
							{
								left_rotation(db_brother);
								db_furthest_nephew_brother->color = _FT_RB_TREE_BLACK;
								db_brother->color = _FT_RB_TREE_RED;
								right_rotation(db_parent);
								db_brother->color = _FT_RB_TREE_BLACK;
							}
						}
					}
					//cas 3 le frère f de x est rouge.
					else
					{
						if (db_brother == db_parent->right)
							left_rotation(db_parent);
						else
							right_rotation(db_parent);
						db_parent->color = _FT_RB_TREE_RED;
						db_brother->color = _FT_RB_TREE_BLACK;
						balancing_double_black(db_node, db_parent);
					}
				}
				void	swap(_RBnode *node1, _RBnode *node2)
				{
					_Val	*tmp;

					tmp = node1->value;
					node1->value = node2->value;
					node2->value = tmp;
				}
				void	erase(_RBnode *node)
				{
					int		node_color = _FT_RB_TREE_BLACK;
					_RBnode	*node_children = _FT_RB_TREE_LEAF;
					_RBnode	*node_parent = NULL;

					if (node)
					{
						node_color = node->color;
						if (node->left != _FT_RB_TREE_LEAF)
							node_children = node->left;
						else
							node_children = node->right;
						node_parent = node->parent;
					}
					if (node != _FT_RB_TREE_LEAF)
					{
						//cas 2 fils
						if (node->left != _FT_RB_TREE_LEAF                    
								&& node->right != _FT_RB_TREE_LEAF)
						{
							_RBnode	*test;
							_RBnode	tmp(*(node->value));

							test = node->left;
							while (test->right)
								test = test->right;
							//swap
							swap(node, test);
							erase(test);
						}
						//cas 0 ou 1 fils
						else if (node->left == _FT_RB_TREE_LEAF
								|| node->right == _FT_RB_TREE_LEAF)
						{
							//maj noeud parent
							if (node_parent == NULL)
								this->root = node_children;
							else if (node_parent->left == node)
								node_parent->left = node_children;
							else
								node_parent->right = node_children;
							//maj noeud enfant
							if (node_children)
								node_children->parent = node_parent;
							//delete node
							delete node;
							--_size;
							//balance
							if (node_color == _FT_RB_TREE_BLACK)
							{
								if (node_children && node_children->color == _FT_RB_TREE_RED)
									node_children->color = _FT_RB_TREE_BLACK;
								else
									balancing_double_black(node_children, node_parent);
							}
						}
					}
				}
				size_type	erase(_Key key)
				{
					_RBnode	*node = search(key);
					if (node != NULL)
					{
						this->erase(node);
						return (1);
					}
					return (0);
				}
				void	insert(_RBnode *new_node)
				{
					if (this->root == _FT_RB_TREE_LEAF)
						this->root = new_node;
					else
						this->root->insert(new_node);
					++_size;
				}
				void	insert(_Val value)
				{
					_RBnode	*new_node = new _RBnode(value);

					this->insert(new_node);
					this->balancing(new_node);
					while (new_node->parent != NULL)
						new_node = new_node->parent;
					this->root = new_node;
				}
				void	balancing(_RBnode *n)
				{
					if (n->parent == NULL)
						balancing_cas1(n);
					else if (n->parent->color == _FT_RB_TREE_BLACK)
						balancing_cas2();
					else if (n->uncle() && n->uncle()->color == _FT_RB_TREE_RED)
						balancing_cas3(n);
					else
						balancing_cas4(n);
				}
				void	balancing_cas1(_RBnode *n)
				{
					if (n->parent == NULL)
						n->color = _FT_RB_TREE_BLACK;
				}
				void	balancing_cas2()
				{
					return ;
				}
				void	balancing_cas3(_RBnode *n)
				{
					n->parent->color = _FT_RB_TREE_BLACK;
					n->uncle()->color = _FT_RB_TREE_BLACK;
					n->grandparent()->color = _FT_RB_TREE_RED;
					balancing(n->grandparent());
				}
				void	balancing_cas4(_RBnode *n)
				{
					_RBnode	*p = n->parent;
					_RBnode	*g = n->grandparent();

					if (g->left && n == g->left->right)
					{
						left_rotation(p);
						n = n->left;
					}
					else if (g->right && n == g->right->left)
					{
						right_rotation(p);
						n = n->right;
					}
					balancing_cas5(n);
				}
				void	balancing_cas5(_RBnode *n)
				{
					_RBnode	*p = n->parent;
					_RBnode	*g = n->grandparent();

					if (n == p->left)
						right_rotation(g);
					else
						left_rotation(g);
					p->color = _FT_RB_TREE_BLACK;
					g->color = _FT_RB_TREE_RED;
				}
				void	_print(_RBnode *node)
				{
					if (node != NULL)
						node->recursive_print(0, 0);
				}
				void	print()
				{
					_print(this->root);
				}
				size_type size() const
				{
					return (_size);
				}
				size_type max_size() const
				{
					return (_alloc_node.max_size());
				}
				value_type& operator[](const _Key& key)
				{
					_RBnode	*node;

					node = this->root;
					while (node && (_compare(node->value->first, key)
								|| _compare(key, node->value->first)))
					{
						if (_compare(node->value->first, key))
							node = node->left;
						else
							node = node->right;
					}
					if (node != NULL)
						return (*(node->value));
					else
					{
						_Val	test;
						_Val	new_val(key, test.second);

						insert(new_val);
						return (*(search(key)->value));
					}
				}
				void swap(RBtree &x)
				{
					_RBnode		*tmp_root = this->root;
					size_type	tmp_size = this->_size;

					this->root = x.root;
					this->_size = x._size;
					x.root = tmp_root;
					x._size = tmp_size;
				}

				_RBnode		*root;
			private:
				_Compare	_compare;
				_Alloc_node	_alloc_node;
				size_type	_size;
		};
}

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
		class map
		{
			public:
				// types:
				typedef Key										key_type;
				typedef T										mapped_type;
				typedef Compare									key_compare;
				typedef ft::pair<const key_type,mapped_type>	value_type;
				typedef Allocator								allocator_type;
			private:
				typedef __ft::RBtree<key_type, value_type, std::_Select1st<value_type>,
						key_compare, allocator_type>			_Rep_type;
			public:
				typedef typename Allocator::reference			reference;
				typedef typename Allocator::const_reference 	const_reference;
				//replace by bidirect iterator
				typedef	__ft::__bidirectional_iterator<typename _Rep_type::iterator, map>
					iterator;
				typedef	__ft::__normal_iterator<typename _Rep_type::const_iterator, map>
					const_iterator;
				typedef typename _Rep_type::size_type			size_type;
				typedef typename _Rep_type::difference_type		difference_type;
				typedef typename Allocator::pointer				pointer;
				typedef typename Allocator::const_pointer		const_pointer;
				typedef ft::reverse_iterator<iterator>			reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
				class value_compare
					: public std::binary_function<value_type,value_type,bool>
				{
					public:
						friend class map;
					protected:
						Compare comp;
						value_compare(Compare c) : comp(c) {}
					public:
						bool operator()(const value_type& x, const value_type& y) const
						{
							return comp(x.first, y.first);
						}
				};
			private:
				//variables
				Compare		_compare;
				Allocator	_allocator;
				_Rep_type	_binary_tree;
			public:
				// 23.3.1.1 construct/copy/destroy:
				explicit map(const Compare& comp = Compare(),
						const Allocator& = Allocator()) :
					_compare(comp),
					_allocator(Allocator()),
					_binary_tree()
			{
			}
				template <class InputIterator>
					map(InputIterator first, InputIterator last,
							const Compare& comp = Compare(),
							const Allocator& = Allocator()) :
						_compare(comp),
						_allocator(Allocator()),
						_binary_tree()
			{
				for (; first != last; ++first)
				{
					_binary_tree.insert(*first);
				}
			}
				map(const map<Key,T,Compare,Allocator>& x) :
					_compare(Compare()),
					_allocator(Allocator()),
					_binary_tree()
			{
				*this = x;
			}
				~map()
				{
				}
				map<Key,T,Compare,Allocator>&
					operator=(const map<Key,T,Compare,Allocator>& x)
					{
						if (this != &x)
						{
							this->_compare = x._compare;
							this->_allocator = x._allocator;
							this->_binary_tree = x._binary_tree;
						}
						return (*this);
					}
				// iterators:
				iterator begin()
				{
					return (iterator(_binary_tree.begin()));
				}
				const_iterator begin() const
				{
					return (iterator(_binary_tree.begin()));
				}
				iterator end()
				{
					return (iterator(_binary_tree.end()));
				}
				const_iterator end() const
				{
					return (iterator(_binary_tree.end()));
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
				// capacity:
				bool empty() const
				{
					if (this->_binary_tree.size() == 0)
						return (true);
					return (false);
				}
				size_type size() const
				{
					return (this->_binary_tree.size());
				}
				size_type max_size() const
				{
					return (this->_binary_tree.max_size());
				}
				// 23.3.1.2 element access:
				T& operator[](const key_type& x)
				{
					return (_binary_tree[x].second);
				}
				// modifiers:
				ft::pair<iterator, bool> insert(const value_type& x);
				iterator insert(iterator position, const value_type& x);
				template <class InputIterator>
					void insert(InputIterator first, InputIterator last);
				void erase(iterator position);
				size_type erase(const key_type& x)
				{
					return (this->_binary_tree.erase(x));
				}
				void erase(iterator first, iterator last);
				void swap(map<Key,T,Compare,Allocator> &x)
				{
					this->_binary_tree.swap(x._binary_tree);
				}
				void clear()
				{
					_binary_tree.clear();
				}
				// observers:
				key_compare key_comp() const
				{
					return (this->_compare);
				}
				value_compare value_comp() const
				{
					return (value_compare());
				}
				// 23.3.1.3 map operations:
				iterator find(const key_type& x);
				const_iterator find(const key_type& x) const;
				size_type count(const key_type& x) const;
				iterator lower_bound(const key_type& x);
				const_iterator lower_bound(const key_type& x) const;
				iterator upper_bound(const key_type& x);
				const_iterator upper_bound(const key_type& x) const;
				ft::pair<iterator,iterator>
					equal_range(const key_type& x);
				ft::pair<const_iterator,const_iterator>
					equal_range(const key_type& x) const;
				// allocator:
				allocator_type get_allocator() const
				{
					return (allocator_type());
				}
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
				map<Key,T,Compare,Allocator>& y)
		{
			x.swap(y);
		}
}

#endif
