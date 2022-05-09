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
					size_type i;
					try
					{
						for (; i < _size; i++)
							_alloc.construct(_p + i, _size);
					}
						catch (std::exception &e)
						{
							std::cout << e.what() << std::endl;
							for (; i != 0; i--)
								_alloc.destroy(_p + i - 1);
							_alloc.deallocate(_p, _size);
						}
					}

					Vector (Vector const &other)
					{
						_size = other.size();
						size_type i;
						try
						{
							for (; i < _size; i++)
								_alloc.construct(_p + i, _size);
						}
						catch (std::exception &e)
						{
							std::cout << e.what() << std::endl;
							for (; i != 0; i--)
								_alloc.destroy(_p + i - 1);
							_alloc.deallocate(_p, _size);
						}
					}

					~Vector()
					{
					for (; this->_size != 0; this->_size--)
							_alloc.destroy(_p + _size -1);
					_alloc.deallocate(_p, _size);
					}

					/* Гетеры */

					size_type size() const {return(_size);}
								 };
}
#endif //FT_CANTAINERS_VECTOR_H
