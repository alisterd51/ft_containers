/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:44:32 by antoine           #+#    #+#             */
/*   Updated: 2022/05/04 18:40:37 by antoine          ###   ########.fr       */
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
				color(_FT_RB_TREE_BLACK),
				_allocator(_Alloc())
			{
				_allocator.construct(&value, newValue);
			}
			~RBnode()
			{
				_allocator.destroy(&value);
			}
			void	insert(RBnode *new_node)
			{
				if (_Compare{}(this->value.first, new_node->value.first))
				{
					if (this->left != NULL)
						this->left->insert(new_node);
					else
						 this->left = new_node;
				}
				else
				{
					if (this->right != NULL)
						this->right->insert(new_node);
					else
						 this->right = new_node;
				}
			}
			void	recursive_print(int deep)
			{
				if (deep < 0)
					return ;
				if (this->left != _FT_RB_TREE_LEAF)
					this->left->recursive_print(deep + 1);
				std::cout << std::setw(deep) << ""
					<< value.first << ": "
					<< value.second << std::endl;
				if (this->right != _FT_RB_TREE_LEAF)
					this->right->recursive_print(deep + 1);
			}
		};
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
				RBtree	*right_rotation(_RBnode *subtree)
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
				RBtree	*left_rotation(_RBnode *subtree)
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

					this->insert(new_node);
				}
				void	_print(_RBnode *node)
				{
					node->recursive_print(0);
				}
				void	print()
				{
					_print(this->root);
				}
				void	insert1(_RBnode *N, _RBnode *P);
		};
}

/*namespace __ft
{
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		struct RBnode
		{
			public:
				RBnode	*_left;
				RBnode	*_right;
				RBnode	*_parent;
				int				_color;
				_Val			_value;

				RBnode() :
					_left(_FT_RB_TREE_LEAF),
					_right(_FT_RB_TREE_LEAF),
					_parent(_FT_RB_TREE_LEAF)
				{
				}
			public:
				RBnode(const _Val& value) :
					_left(_FT_RB_TREE_LEAF),
					_right(_FT_RB_TREE_LEAF),
					_parent(_FT_RB_TREE_LEAF),
					_color(_FT_RB_TREE_BLACK),
					_value(value)
				{
				}
				_Val			get_value()
				{
					return (this->_value);
				}
				int				color()
				{
					return (this->_color);
				}
				RBnode    *left()
				{
					return (this->_left);
				}
				RBnode    *right()
				{
					return (this->_right);
				}
				RBnode    *parent()
				{
					return (this->_parent);
				}
				RBnode	*grandparent()
				{
					if (this->parent() == NULL)
						return (NULL);
					return (this->parent()->parent());
				}
				RBnode	*brother()
				{
					if (this->parent() == NULL)
						return (NULL);
					if (this == this->parent()->left())
						return (this->parent()->right());
					else
						return (this->parent()->left());
				}
				RBnode	*uncle()
				{
					if (this->grandparent() == NULL)
						return (NULL);
					return (this->parent()->brother());
				}
				//search
				//call _recursive_print with deep 0
				void	print() const
				{
					_recursive_print(0);
				}
				void	_recursive_print(size_t deep) const
				{
					if (_left != _FT_RB_TREE_LEAF)
						_left->_recursive_print(deep + 1);
					std::cout << std::setw(deep) << "";
					std::cout << _value.first << ": " << _value.second << std::endl;
					if (_right != _FT_RB_TREE_LEAF)
						_right->_recursive_print(deep + 1);
				}
		};
	//rotation
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		void	left_rotation(RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *x)
		{
			RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc>	*y = x->right();

			x->_right = y->left();
			if (y->left() != _FT_RB_TREE_LEAF)
				y->left()->_parent = x;
			y->_parent = x->parent();
			if (x->_parent == NULL)
				x = y;
			else if (x == x->parent()->left())
				x->parent()->_left = y;
			else
				x->parent()->_right = y;
			y->_left = x;
			x->_parent = y;
		}
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		void	right_rotation(RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *x)
		{
			RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc>	*y = x->left();

			x->_left = y->right();
			if (y->right() != _FT_RB_TREE_LEAF)
				y->right()->_parent = x;
			y->_parent = x->parent();
			if (x->_parent == NULL)
				x = y;
			else if (x == x->parent()->right())
				x->parent()->_right = y;
			else
				x->parent()->_left = y;
			y->_right = x;
			x->_parent = y;
		}
	//insertion
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc>
		*insertion(RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *root,
				RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *n)
		{
			// Insertion d'un nouveau nœud dans l'arbre
			recursive_insertion(root, n);
			// Réparation de l'arbre au cas où les propriétés rouge-noir seraient violées
			balancing(n);
			// Recherche de la nouvelle racine à renvoyer
			root = n;
			while (root->parent() != NULL && root != root->parent())//
				root = root->parent();
			root->_parent = NULL;//
			return (root);
		}
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		void recursive_insertion(RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *root,
				RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *n)
		{
			// Descente récursive dans l'arbre jusqu'à atteindre une feuille
			if (root != NULL && n->_value.first < root->_value.first)
			{
				if (root->left() != _FT_RB_TREE_LEAF)
				{
					recursive_insertion(root->left(), n);
					return ;
				}
				else
					root->_left = n;
			}
			else if (root != NULL)
			{
				if (root->right() != _FT_RB_TREE_LEAF)
				{
					recursive_insertion(root->right(), n);
					return;
				}
				else
					root->_right = n;
			}

			// Insertion du nouveau noeud n
			n->_parent = root;
			n->_left = _FT_RB_TREE_LEAF; // NIL
			n->_right = _FT_RB_TREE_LEAF; // NIL
			n->_color = _FT_RB_TREE_RED;
		}
	//balancing
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		void	balancing(RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *n)
		{
			if (n->_parent == NULL)
				balancing_cas1(n);
			else if (n->parent()->_color == _FT_RB_TREE_BLACK)
				balancing_cas2(n);
			else if (n->uncle() && n->uncle()->_color == _FT_RB_TREE_RED)//
				balancing_cas3(n);
			else
				balancing_cas4(n);
		}
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		void	balancing_cas1(RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *n)
		{
			if (n->parent() == NULL)
				n->_color = _FT_RB_TREE_BLACK;
		}
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		void	balancing_cas2(RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *n)
		{
			return ;
		}
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		void	balancing_cas3(RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *n)
		{
			n->parent()->_color = _FT_RB_TREE_BLACK;
			n->uncle()->_color = _FT_RB_TREE_BLACK;
			n->grandparent()->_color = _FT_RB_TREE_RED;
			balancing(n->grandparent());
		}
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		void	balancing_cas4(RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *n)
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
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
		void	balancing_cas5(RBnode<_Key, _Val, _KeyOfValue, _Compare, _Alloc> *n)
		{
			if (n == n->parent()->left())
				right_rotation(n->grandparent());
			else
				left_rotation(n->grandparent());
			n->parent()->_color = _FT_RB_TREE_BLACK;
			n->grandparent()->_color = _FT_RB_TREE_RED;
		}
}*/

/*namespace ft
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
}*/

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
