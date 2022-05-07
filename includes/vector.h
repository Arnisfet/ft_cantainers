//
// Created by arnisfet on 05.05.2022.
//

#ifndef FT_CANTAINERS_VECTOR_H
#define FT_CANTAINERS_VECTOR_H

#include <iostream>
#include <memory>

namespace ft {
	template < class T, class Allocator = std::allocator<T> >
			class Vector{
			public:

				/* Псевдонимы для типов данных как в срр референс */

				typedef T										value_type;
				typedef Allocator								allocator_type;
				typedef std::size_t								size_type;
				typedef	std::ptrdiff_t							difference_type;
				typedef	value_type&								reference;
				typedef const value_type&						const_reference;
				typedef	typename Allocator::pointer				pointer;
				typedef	typename Allocator::const_pointer		const_pointer;
				//typedef  VectorIterator<pointer>		iterator;
				//typedef  VectorIterator<const_pointer>	const_iterator;
				//typedef reverse_iterator<iterator> reverse_iterator;
				//typedef reverse_iterator<const_iterator>  const_reverse_iterator;

				/* Приватные переменные */

			private:
				pointer			_p;
				size_type		_size;
				size_type		_capacity;
				allocator_type	_alloc;

				/* Конструкторы */

			public:
				explicit Vector(const Allocator &alloc = Allocator()) :
				_p(NULL), _size(0), _capacity(0), _alloc(alloc)
				{}
				explicit Vector( size_type count,
								 const T& value = T(),
								 const Allocator& alloc = Allocator())
								 : _size(count), _capacity(count), _alloc(alloc)
								 {
					_p = _alloc.allocate(count);
					size_type i = 0;
								 }
			};
}
#endif //FT_CANTAINERS_VECTOR_H
