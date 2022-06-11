//
// Created by arnisfet on 05.05.2022.
//

#ifndef FT_CANTAINERS_VECTOR_H
#define FT_CANTAINERS_VECTOR_H

#include <iostream>
#include <memory>
#include "ft_type_traits.hpp"
#include <limits>
#include "compare_equal.h"

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
				typedef  random_access_iterator<value_type>		iterator;
				typedef  random_access_iterator<const_pointer>	const_iterator;
//				typedef ReverseIterator<pointer>				reverse_iterator;
//				typedef ReverseIterator<const_pointer>	const_reverse_iterator;
				typedef class ReverseIterator<iterator>		reverse_iterator;
				typedef class ReverseIterator<const_iterator>	const_reverse_iterator;

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
									 _p = _alloc.allocate(_size);
									 size_type i = 0;
									 try
									 {
										 for (; i < _size; i++)
											 _alloc.construct(_p + i, value);
									 }
									 catch (...)
									 {
										 clear();
										 throw "vector";
									 }
					}

					Vector (Vector const &other) : _p(NULL), _alloc(allocator_type())
					{
						_size = other.size();
						size_type i = 0;
						try
						{
							_p = _alloc.allocate(_size);
							for (; i < _size; i++)
								_alloc.construct(_p + i, other[i]);
						}
						catch (std::exception &e)
						{
							std::cout << e.what() << std::endl;
							for (; i != 0; i--)
								_alloc.destroy(_p + i - 1);
							_alloc.deallocate(_p, _size);
						}
					}

					template < typename InputIt >
					Vector(InputIt first, InputIt last,
						   const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt())
						   : _size(0),  _capacity(20), _alloc(alloc)
					{
						difference_type diff = 0;
						for (InputIt start = first; start != last; start++)
							diff++;
						_p = _alloc.allocate(diff);
						for (size_t i = 0; i != diff; i++)
						{
							_alloc.construct(_p + i, *first);
							first++;
						}
						_size = diff;
						_capacity = diff;
						_alloc = alloc;
					}

					~Vector()
					{
					for(size_type i = 0; i < _size; i++)
						_alloc.destroy(_p + i);
					_size = 0;
					if (_capacity)
						_alloc.deallocate(_p, _capacity);
					}

					/* Гетеры */
					size_type capacity() const {return(_capacity);}
					pointer	point() const {return(_p);}
					allocator_type alloc() const {return(_alloc);}

					/* Функции аллокации и конструкции */

					void	clear()
					{
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(_p + i);
						_alloc.deallocate(_p, _size);
						_size = 0;
					}

					/* Оператор = */

					Vector	&operator=(Vector const &other)
					{
						if (this != &other)
						{
							clear();
							_size = other._size;
							_capacity = other._capacity;
							_alloc = other._alloc;
							if (_capacity)
								_p = _alloc.allocate(_capacity);
							for (size_type i = 0; i < _size; i++)
								_alloc.construct(_p + i, other._p[i]);
						}
						return (*this);
					}

					/* ****************** End of constructors ******************* */
					/* ****************** Iterators functions ******************* */
					iterator				begin() {return(iterator(_p));}
					const_iterator			cbegin() const {return(const_iterator(_p));}
					iterator				end() {return(iterator(_p + _size));}
					const_iterator			cend() const {return(iterator(_p + _size));}
					reverse_iterator		rbegin() {return(reverse_iterator(end()));}
					const_reverse_iterator	rcbegin() const {return(const_reverse_iterator(end()));}
					reverse_iterator		rend() {return(reverse_iterator(begin()));}
					const_reverse_iterator	rcend() const {return(const_reverse_iterator(begin()));}
					/* ****************** Iterators ends	 ******************* */
					/**************************** Capacity  ******************************/
					size_type size() const{return (_size);}
					//Returns the maximum number of elements that the vector can hold.
					//Returns the maximum theoretically possible value of n, for which the call allocate(n, 0) could succeed
					size_type max_size() const {return (_alloc.max_size());}
					//Resizes the container so that it contains n elements
					//If the requested size is bigger than the current capacity, the capacity is usually doubled until it's large enough

					void resize (size_type n, value_type val = value_type())
					{
						if (n < _size) {
							for (size_type i = _size; i != n; i--) {
								pop_back();
							}
						}
						else {
							for (size_type i = _size; i != n; i++) {
								push_back(val);
							}
						}
					}

					bool empty() const {return (size() == 0 ? true : false); }
					void reserve (size_type n)
					{
						//If the size requested is greater than the maximum size (vector::max_size), a length_error exception is thrown.
						if (n > max_size())
							throw std::length_error("Reserve error .");
						/*
							Increase the capacity of the vector to a value that's greater or equal to n.
							If n is greater than the current capacity(), new storage is allocated, otherwise the function does nothing.
						*/
//						std::cout << _capacity << "\n";
						if (n > _capacity)
						{
							// allocate the new_size
							pointer new_ptr = _alloc.allocate(n);
							// copy the old ptr into new_ptr
							for (size_type i = 0; i < _size; i++)
								_alloc.construct(new_ptr + i, _p[i]);
							for (size_type i = 0; i < _size; i++)
								_alloc.destroy(_p + i);
							if (_capacity)
								_alloc.deallocate(_p, _capacity);
							// swap the contenu
							std::swap(new_ptr, _p);
//							std::cout << _capacity << "\n";
//							printf("%lu\n", _capacity);
							_capacity = n;
//							std::cout << _capacity << "\n";
//							printf("%lu\n", _capacity);
						}
					}
				/************************** End Capacity  ****************************/


				/**************************** Element access:  ******************************/
					reference operator[] (size_type n){return (_p[n]);}
					const_reference operator[] (size_type n) const {return (_p[n]);}
					reference at (size_type n)
					{
						if (n >= this->size())
							throw (std::out_of_range("Out of range"));
						return (_p[n]);
					}
					const_reference at (size_type n) const
					{
						if (n >= this->size())
							throw (std::out_of_range("Out of range"));
						return (_p[n]);
					}
					reference front() {return (_p[0]);}
					const_reference front() const {return (_p[0]);}
					reference back() {return (_p[_size - 1]);}
					const_reference back() const {return (_p[_size - 1]);}
					/**************************** End  Element access******************************/


					/**************************** Modifiers  ******************************/
					// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
					//destroy all the old elements
					template <class InputIterator>
					void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
					{
						{
							size_type	counter = 0;
//							if (last < first) {
//								throw std::invalid_argument("vector error: assign");
//							}
							for (InputIterator it = first; it != last; it++) {
								counter++;
							}
							for (size_type i = 0; i < _size; i++) {
								_alloc.destroy(_p + i);
							}
							if (_capacity < counter) {
								_alloc.deallocate(_p, _capacity);
								_capacity = counter;
								_p = _alloc.allocate(_capacity);
							}
							_size = counter;
							for (size_type i = 0; first != last; i++, first++) {
								_alloc.construct(_p + i, *first);
							}
						}
					}
					void assign (size_type n, const value_type& val)
					{
						if (!_capacity)
							_p = _alloc.allocate(n);
						for (size_type i = 0; i < _size; i++) {
							_alloc.destroy(_p + i);
						}
						if (_capacity < n) {
							_alloc.deallocate(_p, _capacity);
							_capacity = n;
							_p = _alloc.allocate(_capacity);
						}
						for (size_type i = 0; i < n; i++) {
							_alloc.construct(_p + i, val);
						}
						_size = n;
					}
					void push_back (const value_type& val)
					{
						if (_capacity == 0)
							reserve(1);
						else if (_size == _capacity)
							reserve(_capacity * 2);
						_alloc.construct(_p + _size, val);
						_size++;
					}
					void pop_back()
					{
						if (_size > 0)
						{
							_alloc.destroy(_p + _size);
							_size--;
						}
					}
					//inserting new elements before the element at the specified position
					// insert new element before the position
					iterator insert (iterator position, const value_type& val)
					{
						Vector tmp;
						size_type index_pos = position - begin();
						size_type end_elem = end() - position;
						// first lets store our end eements int tmp
						tmp.assign(position, end());
						// push in the pos the value in our ptr
						_size = index_pos;
						push_back(val);
						// lets push our end elements in our ptr
						for (size_type i = 0; i < end_elem; i++)
							push_back(tmp[i]);
						return (begin() + index_pos);
					}
					//fill (2)
					void insert (iterator position, size_type n, const value_type& val)
					{
						Vector tmp;
						size_type index_pos = position - begin();
						size_type end_elem = end() - position;
						// first lets store our end eements int tmp
						tmp.assign(position, end());
						if (n + _capacity > (_capacity * 2))
							reserve(_size + n);
						else if (!_size)
							reserve(n);
						// push in the pos the value in our ptr
						_size = index_pos;
						for (size_type i = 0; i < n; i++)
							push_back(val);
						// lets push our end elements in our ptr
						for (size_type i = 0; i < end_elem; i++)
							push_back(tmp[i]);
					}
					//range (3)
					template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last
								 , typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
					{
						Vector tmp;
						difference_type n = last - first;
						size_type index_pos = position - begin();
						size_type end_elem = end() - position;
						// first lets store our end elements int tmp
						tmp.assign(position, end());
						if ((n + _capacity) > (_capacity * 2))
							reserve(_size + n);
						else if (!_size)
							reserve(n);
						// push in the pos the value in our ptr
						_size = index_pos;
						while (first != last)
							push_back(*first++);
						// lets push our end elements in our ptr
						for (size_type i = 0; i < end_elem; i++)
							push_back(tmp[i]);
					}

					iterator erase (iterator position)
					{
						if (position == end())
							pop_back();
						_alloc.destroy(&*position);
						for (iterator it = position; it != end(); it++)
						{
							_alloc.construct(&*it, *(it + 1));
							_alloc.destroy(&*(it + 1));
						}
						_size--;
						return (position);
					}
					iterator erase (iterator first, iterator last)
					{
						// copy from the last position to the end () and join it in first position
						copy_erase(last, end(), first);
						_size -= last - first;
						return(first);
					}
					void swap (Vector& x)
					{
						std::swap(_size, x._size);
						std::swap(_capacity, x._capacity);
						std::swap(_p, x._p);
					}

				/**************************** end Modifiers ******************************/
					allocator_type get_allocator() const {return (_alloc);}
			private:
					template<class InputIterator, class OutputIterator>
					OutputIterator copy_erase (InputIterator first, InputIterator last, OutputIterator result)
					{
						while (first!=last) {
							*result = *first;
							result++;
							first++;
						}
						return result;
					}
			};
	//Exchange contents of vectors
	template <class T, class Alloc>
			void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y)
			{
				x.swap(y);
			}
			//performed by first comparing sizes then use equal to stop at the first  mismatch
			template <class T, class Alloc>
					bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
					return (false);
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}
			template <class T, class Alloc>
					bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			{
				//!(a==b)
				return !(lhs == rhs);
			}
			//The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare
			template <class T, class Alloc>
					bool operator<  (const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs)
			{
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}
			template <class T, class Alloc>
					bool operator<= (const Vector<T,Alloc>& lhs, const
					Vector<T,Alloc>& rhs)
			{
				//	!(b<a)
				return !(rhs < lhs);
			}
			template <class T, class Alloc>bool operator>  (const ft::Vector<T,Alloc>& lhs, const ft::Vector<T,Alloc>& rhs)
					{
					//b<a
					return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
					}
					template <class T, class Alloc>
							bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
					{
						//!(a<b)
						return !(lhs < rhs);
					}


}
#endif //FT_CANTAINERS_VECTOR_H
