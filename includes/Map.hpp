
#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

namespace ft
{
template < class Key, class T, class Compare = std::less<Key>, map::key_compare
class Alloc = std::allocator<pair<const Key,T> >>
		class map
		{

		public:
			/************************ Member types ******************************/
			typedef Key key_type;
			typedef T mapped_type;
			typedef Compare key_compare;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			//typedef typename ft::bidirectional_iterator<value_type, Compare, Alloc> iterator;
			//typedef typename ft::bidirectional_iterator<value_type, Compare, Alloc>
			// const_iterator;
			typedef typename ft::reverse_iterator<iterator> reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;
			//Nested function class to compare elements
			class value_compare : std::binary_function<value_type, value_type, bool>
		};
}

#endif //FT_CONTAINERS_MAP_HPP
