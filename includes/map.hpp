/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:44:32 by antoine           #+#    #+#             */
/*   Updated: 2022/05/10 17:29:30 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <iomanip>
# include <cassert>

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
			RBnode	*parent;
			RBnode	*left;
			RBnode	*right;
			int		color;
			_Val	value;
			_Alloc	_allocator;

			RBnode(_Val newValue) :
				parent(_FT_RB_TREE_LEAF),
				left(_FT_RB_TREE_LEAF),
				right(_FT_RB_TREE_LEAF),
				color(_FT_RB_TREE_RED),
				_allocator(_Alloc())
			{
				_allocator.construct(&value, newValue);
			}
			~RBnode()
			{
				_allocator.destroy(&value);
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
			void	insert(RBnode *new_node)
			{
				if (_Compare{}(this->value.first, new_node->value.first))
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
			void	print_node(int deep, int direction)
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
				print_node(deep, direction);
				if (this->right != _FT_RB_TREE_LEAF)
					this->right->recursive_print(deep + 1, 2);
			}
		};

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		std::ostream	&operator<<(std::ostream &o, __ft::RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> const &i)
		{
			o << (i.color == _FT_RB_TREE_BLACK ? _FT_BLACK : _FT_RED)
				<< i.value.first << ": " << i.value.second << _FT_RESET;
			return (o);
		}

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		struct RBtree
		{
			private:
				typedef	__ft::RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc>	_RBnode;
			public:
				_RBnode	*root;

				RBtree() :
					root(NULL)
			{
			}
				~RBtree()
				{
					recursive_remove(this->root);
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
					while (node && (_Compare{}(node->value.first, key)
								|| _Compare{}(key, node->value.first)))
					{
						if (_Compare{}(node->value.first, key))
							node = node->left;
						else
							node = node->right;
					}
					return (node);
				}
				////////////////////////////////////////////////////////////////
				void	balancing_double_black(_RBnode *db_node, _RBnode *db_parent)
				{
					_RBnode	*db_brother = NULL;

					if (db_parent)
					{
						if (db_parent->left == db_node)
							db_brother = db_parent->right;
						else
							db_brother = db_parent->left;
					}
					//cas 0 le nœud x est la racine de l'arbre
					if (db_parent == NULL)
					{
						db_node->color = _FT_RB_TREE_BLACK;
					}
					//cas 1  le frère f de x est noir.
					else if (db_brother == NULL || db_brother->color == _FT_RB_TREE_BLACK)
					{
						//cas 1a
						//cas 1b
						//cas 1c
					}
					//cas 3 le frère f de x est rouge.
					else
					{
					}
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
						//cas 0 ou 1 fils
						if (node->left == _FT_RB_TREE_LEAF
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
							//balance
							if (node_color == _FT_RB_TREE_BLACK)
							{
								if (node_children && node_children->color == _FT_RB_TREE_RED)
									node_children->color = _FT_RB_TREE_BLACK;
								else
									balancing_double_black(node_children, node_parent);
							}
							else
							{
								//Si le nœud supprimé est rouge, la propriété (3) reste vérifiée. 
							}
						}
						//cas 2 fils
						else
						{
						}
					}
					//https://www.irif.fr/~carton/Enseignement/Algorithmique/Programmation/RedBlackTree/
				}
				////////////////////////////////////////////////////////////////
				void	erase(_Key key)
				{
					this->erase(search(key));
				}
				void	insert(_RBnode *new_node)
				{
					if (this->root == _FT_RB_TREE_LEAF)
						this->root = new_node;
					else
						this->root->insert(new_node);
				}
				void	insert(_Val value)
				{
					_RBnode	*new_node = new _RBnode(value);
					_RBnode	*new_root;

					this->insert(new_node);
					this->balancing(new_node);
					new_root = new_node;
					while (new_root->parent != NULL)
						new_root = new_root->parent;
					this->root = new_root;
				}
				void	balancing(_RBnode *n)
				{
					if (n->parent == NULL)
						balancing_cas1(n);
					else if (n->parent->color == _FT_RB_TREE_BLACK)
						balancing_cas2(n);
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
				void	balancing_cas2(_RBnode *n)
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
				typedef __ft::RBtree<key_type, value_type, std::_Select1st<value_type>,
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

/*namespace ft
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
}*/

#endif
