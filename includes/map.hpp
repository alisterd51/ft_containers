/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:44:32 by antoine           #+#    #+#             */
/*   Updated: 2022/05/30 03:11:23 by anclarma         ###   ########.fr       */
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
			typedef _Val	value_type;

			RBnode		*parent;
			RBnode		*left;
			RBnode		*right;
			int			color;
			value_type	*value;
			_Alloc		_allocator;
			_Compare	_compare;

			RBnode(value_type newValue) :
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
			const RBnode  *max() const
			{
					const RBnode	*max = this;

					while (max && max->right)
						max = max->right;
					return (max);
			}
			RBnode  *max()
			{
					RBnode	*max = this;

					while (max && max->right)
						max = max->right;
					return (max);
			}
			const RBnode  *min() const
			{
					const RBnode	*min = this;

					while (min && min->left)
						min = min->left;
					return (min);
			}
			RBnode  *min()
			{
					RBnode	*min = this;

					while (min && min->left)
						min = min->left;
					return (min);
			}
			RBnode	*next()
			{
				RBnode	*n = this;

				if (n->right)
				{
					n = n->right;
					while (n && n->left)
						n = n->left;
				}
				else
				{
					_Key	current(n->value->first);

					while (!_compare(current, n->value->first) && n->parent)
						n = n->parent;
					if (!_compare(current, n->value->first))
						n = NULL;
				}
				return (n);
			}
			const RBnode	*next() const
			{
				const RBnode	*n = this;

				if (n->right)
				{
					n = n->right;
					while (n && n->left)
						n = n->left;
				}
				else
				{
					_Key	current(n->value->first);

					while (!_compare(current, n->value->first) && n->parent)
						n = n->parent;
					if (!_compare(current, n->value->first))
						n = NULL;
				}
				return (n);
			}
			RBnode	*prev()
			{
				RBnode	*n = this;

				if (n->left)
				{
					n = n->left;
					while (n && n->right)
						n = n->right;
				}
				else
				{
					_Key	current(n->value->first);

					while (!_compare(n->value->first, current) && n->parent)
						n = n->parent;
					if (!_compare(n->value->first, current))
						n = NULL;
				}
				return (n);
			}
			const RBnode	*prev() const
			{
				const RBnode	*n = this;

				if (n->left)
				{
					n = n->left;
					while (n && n->right)
						n = n->right;
				}
				else
				{
					_Key	current(n->value->first);

					while (!_compare(n->value->first, current) && n->parent)
						n = n->parent;
					if (!_compare(n->value->first, current))
						n = NULL;
				}
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
				if (_compare(new_node->value->first, this->value->first))
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

	template<typename _RBnode>
		class Rbtree_iterator
		{
			private:
				typedef _RBnode*						node_pointer;
			public:
				typedef std::bidirectional_iterator_tag	iterator_category;
				typedef typename _RBnode::value_type	value_type;
				typedef std::ptrdiff_t					difference_type;
				typedef value_type*						pointer;
				typedef value_type&						reference;
			private:
				node_pointer	_node;
				node_pointer	_root;
				node_pointer	_parent;
				value_type		_default_pair;

				template<typename _RBnode1>
					friend bool	operator==(const Rbtree_iterator<_RBnode1>&,
							const Rbtree_iterator<_RBnode1>&);
			public:
				Rbtree_iterator() :
					_node(),
					_root(),
					_parent(),
					_default_pair()
			{
			}
				Rbtree_iterator(const Rbtree_iterator& x) :
					_node(),
					_root(),
					_parent(),
					_default_pair()
			{
				*this = x;
			}
				Rbtree_iterator(const node_pointer& node,
						const node_pointer& root,
						const node_pointer& parent = NULL) :
					_node(node),
					_root(root),
					_parent(parent),
					_default_pair()
			{
			}
				Rbtree_iterator	&operator=(const Rbtree_iterator& x)
				{
					if (this != &x)
					{
						this->_node = x._node;
						this->_root = x._root;
						this->_parent = x._parent;
					}
					return (*this);
				}
				Rbtree_iterator&	operator++()
					{
						if (_node && _node == _root->max())
						{
							_parent = _root->max();
							_node = NULL;
						}
						else if (_node)
						{
							_parent = NULL;
							_node = _node->next();
						}
						else if (_parent && _parent == _root->min())
						{
							_parent = NULL;
							_node = _root->min();
						}
						return (*this);
					}
				Rbtree_iterator	operator++(int)
				{
					Rbtree_iterator	temp = *this;

					++(*this);
					return (temp);
				}
				Rbtree_iterator&	operator--()
				{
					if (_node && _node == _root->min())
					{
						_parent = _root->min();
						_node = NULL;
					}
					else if (_node)
					{
						_parent = NULL;
						_node = _node->prev();
					}
					else if (_parent && _parent == _root->max())
					{
						_parent = NULL;
						_node = _root->max();
					}
					return (*this);
				}
				Rbtree_iterator	operator--(int)
				{
					Rbtree_iterator	temp = *this;

					--(*this);
					return (temp);
				}
				reference operator*() const
				{
					if (_node)
						return (*(_node->value));
					return (reference(_default_pair));
				}
				pointer operator->() const
				{
					return (&operator*());
				}
				// for const conversion:
				node_pointer	get_node() const
				{
					return (_node);
				}
				node_pointer	get_root() const
				{
					return (_root);
				}
				node_pointer	get_parent() const
				{
					return (_parent);
				}

		};
	template<typename _RBnode>
		bool	operator==(const Rbtree_iterator<_RBnode>& lhs,
				const Rbtree_iterator<_RBnode>& rhs)
		{
			return (lhs._node == rhs._node/* && lhs._parent == rhs._parent*/);
		}
	template<typename _RBnode>
		bool	operator!=(const Rbtree_iterator<_RBnode>& lhs,
				const Rbtree_iterator<_RBnode>& rhs)
		{
			return (!(lhs == rhs));
		}

	template<typename _RBnode>
		class Rbtree_const_iterator
		{
			private:
				typedef _RBnode*						node_pointer;
			public:
				typedef std::bidirectional_iterator_tag	iterator_category;
				typedef typename _RBnode::value_type const	value_type;
				typedef std::ptrdiff_t					difference_type;
				typedef value_type*						pointer;
				typedef value_type&						reference;
			private:
				const _RBnode	*_node;
				const _RBnode	*_root;
				const _RBnode	*_parent;
				value_type		_default_pair;

				template<typename _RBnode1>
					friend bool	operator==(const Rbtree_const_iterator<_RBnode1>&,
							const Rbtree_const_iterator<_RBnode1>&);
			public:
				Rbtree_const_iterator() :
					_node(),
					_root(),
					_parent(),
					_default_pair()
			{
			}
				Rbtree_const_iterator(const Rbtree_const_iterator& x) :
					_node(x._node),
					_root(x._root),
					_parent(x._parent),
					_default_pair()
			{
			}
				Rbtree_const_iterator(const Rbtree_iterator<_RBnode>& x) :
					_node(x.get_node()),
					_root(x.get_root()),
					_parent(x.get_parent()),
					_default_pair()
			{
			}
				Rbtree_const_iterator(const node_pointer& node,
						const node_pointer& root,
						const node_pointer& parent = NULL) :
					_node(node),
					_root(root),
					_parent(parent),
					_default_pair()
			{
			}
				Rbtree_const_iterator	&operator=(const Rbtree_const_iterator& x)
				{
					if (this != &x)
					{
						this->_node = x._node;
						this->_root = x._root;
						this->_parent = x._parent;
					}
					return (*this);
				}
				Rbtree_const_iterator&	operator++()
				{
					if (_node && _node == _root->max())
					{
						_parent = _root->max();
						_node = NULL;
					}
					else if (_node)
					{
						_parent = NULL;
						_node = _node->next();
					}
					else if (_parent && _parent == _root->min())
					{
						_parent = NULL;
						_node = _root->min();
					}
					return (*this);
				}
				Rbtree_const_iterator	operator++(int)
				{
					Rbtree_const_iterator	temp = *this;

					++(*this);
					return (temp);
				}
				Rbtree_const_iterator&	operator--()
				{
					if (_node && _node == _root->min())
					{
						_parent = _root->min();
						_node = NULL;
					}
					else if (_node)
					{
						_parent = NULL;
						_node = _node->prev();
					}
					else if (_parent && _parent == _root->max())
					{
						_parent = NULL;
						_node = _root->max();
					}
					return (*this);
				}
				Rbtree_const_iterator	operator--(int)
				{
					Rbtree_const_iterator	temp = *this;

					--(*this);
					return (temp);
				}
				reference operator*() const
				{
					if (_node)
						return (*(_node->value));
					return (reference(_default_pair));
				}
				pointer operator->() const
				{
					return (&operator*());
				}
		};
	template<typename _RBnode>
		bool	operator==(const Rbtree_const_iterator<_RBnode>& lhs,
				const Rbtree_const_iterator<_RBnode>& rhs)
		{
			return (lhs._node == rhs._node && lhs._parent == rhs._parent);
		}
	template<typename _RBnode>
		bool	operator!=(const Rbtree_const_iterator<_RBnode>& lhs,
				const Rbtree_const_iterator<_RBnode>& rhs)
		{
			return (!(lhs == rhs));
		}
	template<typename _RBnode>
		bool	operator==(const Rbtree_iterator<_RBnode>& lhs,
				const Rbtree_const_iterator<_RBnode>& rhs)
		{
			const Rbtree_const_iterator<_RBnode>	l(lhs);
			return (l == rhs);
		}
	template<typename _RBnode>
		bool	operator!=(const Rbtree_iterator<_RBnode>& lhs,
				const Rbtree_const_iterator<_RBnode>& rhs)
		{
			return (!(lhs == rhs));
		}
	template<typename _RBnode>
		bool	operator==(const Rbtree_const_iterator<_RBnode>& lhs,
				const Rbtree_iterator<_RBnode>& rhs)
		{
			const Rbtree_const_iterator<_RBnode>	r(rhs);
			return (lhs == r);
		}
	template<typename _RBnode>
		bool	operator!=(const Rbtree_const_iterator<_RBnode>& lhs,
				const Rbtree_iterator<_RBnode>& rhs)
		{
			return (!(lhs == rhs));
		}

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		struct RBtree
		{
			private:
				typedef	__ft::RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc>	_RBnode;
				typedef	std::allocator<_RBnode>					_Alloc_node;
			public:
				typedef _Val									value_type;
				typedef	Rbtree_iterator<_RBnode>				iterator;
				typedef	Rbtree_const_iterator<_RBnode>			const_iterator;
				typedef	ft::reverse_iterator<iterator>			reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
				typedef std::size_t								size_type;
				typedef	std::ptrdiff_t							difference_type;

				RBtree() :
					root(NULL),
					min(NULL),
					max(NULL),
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
					this->min = NULL;
					this->max = NULL;
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
						update_limit();
						this->_size = x._size;
					}
					return (*this);
				}
				void	update_limit()
				{
					if (root)
					{
						min = root->min();
						max = root->max();
					}
					else
					{
						min = NULL;
						max = NULL;
					}
				}
				iterator	begin()
				{
					return (iterator(min, root));
				}
				const_iterator	begin() const
				{
					return (const_iterator(min, root));
				}
				iterator	end()
				{
					return (++iterator(max, root));
				}
				const_iterator	end() const
				{
					return (++const_iterator(max, root));
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
				_RBnode	*search(_Key key) const
				{
					_RBnode	*node;

					node = this->root;
					while (node && (_compare(node->value->first, key)
								|| _compare(key, node->value->first)))
					{
						if (_compare(key, node->value->first))
							node = node->left;
						else
							node = node->right;
					}
					return (node);
				}
				iterator	lower_bound(_Key key) const
				{
					_RBnode	*node = search(key);

					if (!root)
						return (iterator(root, root));
					if (node)
						return (iterator(node, root));
					node = min;
					if (_compare(key, node->value->first))
						return (iterator(node, root));
					node = max;
					if (_compare(node->value->first, key))
						return (++iterator(node, root));

					iterator	it(min, root);
					while (_compare(it->first, key))
						++it;
					return (it);//vrai mais ne respecte pas la complexiter de l'iso
				}
				iterator find(_Key x)
				{
					_RBnode	*f = search(x);
					if (f)
						return (iterator(f, root));
					else
						return (++iterator(max, root));
				}
				const_iterator find(_Key x) const
				{
					_RBnode	*f = search(x);
					if (f)
						return (const_iterator(f, root));
					else
						return (++const_iterator(max, root));
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
							if (db_node)
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
					update_limit();
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
				void	erase(iterator first, iterator last)
				{
					_Key		min(first->first);

					while (first != last)
					{
						erase(first->first);
						first = lower_bound(min);
					}
				}
				void	insert(_RBnode *p, _RBnode *new_node)
				{
					if (this->root == _FT_RB_TREE_LEAF)
						this->root = new_node;
					else
						p->insert(new_node);
					++_size;
				}
				void	insert(_RBnode *new_node)
				{
					this->insert(this->root, new_node);
				}
				void	insert(iterator pos, _Val value)
				{
					if (_compare(pos->first, value.first)
							&& (max == NULL
								|| pos->first == max->value->first
								|| _compare(value.first, (++pos)->first)))
					{
						_RBnode	*new_node = new _RBnode(value);

						this->insert(search(pos->first), new_node);
						this->balancing(new_node);
						while (new_node->parent != NULL)
							new_node = new_node->parent;
						this->root = new_node;
						update_limit();
					}
					else
						insert(value);
				}
				void	insert(_Val value)
				{
					if (search(value.first) == NULL)
					{
						_RBnode	*new_node = new _RBnode(value);

						this->insert(new_node);
						this->balancing(new_node);
						while (new_node->parent != NULL)
							new_node = new_node->parent;
						this->root = new_node;
						update_limit();
					}
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
						if (_compare(key, node->value->first))
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
					_RBnode		*tmp_min = this->min;
					_RBnode		*tmp_max = this->max;
					size_type	tmp_size = this->_size;

					this->root = x.root;
					this->min = x.min;
					this->max = x.max;
					this->_size = x._size;
					x.root = tmp_root;
					x.min = tmp_min;
					x.max = tmp_max;
					x._size = tmp_size;
				}

				_RBnode		*root;
			private:
				_RBnode		*min;
				_RBnode		*max;
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
				typedef	typename _Rep_type::iterator			iterator;
				typedef	typename _Rep_type::const_iterator		const_iterator;
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
					return (const_iterator(_binary_tree.begin()));
				}
				iterator end()
				{
					return (iterator(_binary_tree.end()));
				}
				const_iterator end() const
				{
					return (const_iterator(_binary_tree.end()));
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
				ft::pair<iterator, bool> insert(const value_type& x)
				{

					if (_binary_tree.search(x.first) != NULL)
						return (ft::make_pair<iterator, bool>(find(x.first), false));
					else
					{
						_binary_tree.insert(x);
						return (ft::make_pair<iterator, bool>(find(x.first), true));
					}
				}
				iterator insert(iterator position, const value_type& x)
				{
					_binary_tree.insert(position, x);
					return (find(x.first));
				}
				template <class InputIterator>
					void insert(InputIterator first, InputIterator last)
					{
						for (; first != last; ++first)
							insert(*first);
					}
				void erase(iterator position)
				{
					erase(position->first);
				}
				size_type erase(const key_type& x)
				{
					return (this->_binary_tree.erase(x));
				}
				void erase(iterator first, iterator last)
				{
					this->_binary_tree.erase(first, last);
				}
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
					return (value_compare(_compare));
				}
				// 23.3.1.3 map operations:
				iterator find(const key_type& x)
				{
					if (count(x))
						return (iterator(_binary_tree.search(x), _binary_tree.root));
					else
						return (end());
				}
				const_iterator find(const key_type& x) const
				{
					if (count(x))
						return (const_iterator(_binary_tree.search(x), _binary_tree.root));
					else
						return (end());
				}
				size_type count(const key_type& x) const
				{
					if (_binary_tree.search(x))
						return (1);
					else
						return (0);
				}
				iterator lower_bound(const key_type& x)
				{
					return (iterator(_binary_tree.lower_bound(x)));
				}
				const_iterator lower_bound(const key_type& x) const
				{
					return (const_iterator(_binary_tree.lower_bound(x)));
				}
				iterator upper_bound(const key_type& x)
				{
					iterator	l = lower_bound(x);

					if (!_compare(x, l->first) && !_compare(l->first, x))
						++l;
					return (l);
				}
				const_iterator upper_bound(const key_type& x) const
				{
					const_iterator	l = lower_bound(x);

					if (l->first == x)
						++l;
					return (l);
				}
				ft::pair<iterator, iterator>
					equal_range(const key_type& x)
					{
						return (ft::make_pair<iterator, iterator>(lower_bound(x), upper_bound(x)));
					}
				ft::pair<const_iterator, const_iterator>
					equal_range(const key_type& x) const
					{
						return (ft::make_pair<const_iterator, const_iterator>(lower_bound(x), upper_bound(x)));
					}
				// allocator:
				allocator_type get_allocator() const
				{
					return (allocator_type());
				}
		};
	template <class Key, class T, class Compare, class Allocator>
		bool operator==(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y)
		{
			return (equal(x.begin(), x.end(), y.begin())
					&& equal(y.begin(), y.end(), x.begin()));
		}
	template <class Key, class T, class Compare, class Allocator>
		bool operator< (const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y)
		{
			return (lexicographical_compare(x.begin(), x.end(), y.begin(),
						y.end()));
		}
	template <class Key, class T, class Compare, class Allocator>
		bool operator!=(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y)
		{
			return (!(x == y));
		}
	template <class Key, class T, class Compare, class Allocator>
		bool operator> (const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y)
		{
			return (y < x);
		}
	template <class Key, class T, class Compare, class Allocator>
		bool operator>=(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y)
		{
			return (!(x < y));
		}
	template <class Key, class T, class Compare, class Allocator>
		bool operator<=(const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y)
		{
			return (!(y < x));
		}
	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
		void swap(map<Key,T,Compare,Allocator>& x,
				map<Key,T,Compare,Allocator>& y)
		{
			x.swap(y);
		}
}

#endif
