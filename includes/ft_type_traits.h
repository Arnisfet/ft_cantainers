//
// Created by arnisfet on 10.05.2022.
//

#ifndef FT_CANTAINERS_FT_TYPE_TRAITS_H
#define FT_CANTAINERS_FT_TYPE_TRAITS_H


#include <iostream>
#include <cstddef>

namespace ft {
	/* Iterator Traits */
	template <class Iterator>
			class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	/* T* specialization: */
	template <class T>
			class iterator_traits <T *>
	{
	public:
		typedef ptrdiff_t diffrence_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	/* const T* specialization: */
	template <class T>
	class iterator_traits <const T *>
	{
	public:
		typedef ptrdiff_t diffrence_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class Iterator>
	class VectorIterator
	{
	public:

		typedef typename ft::iterator_traits<Iterator>::value_type 			value_type;
		typedef typename ft::iterator_traits<Iterator>::reference 			reference;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::pointer				iterator_type;
	private:
		pointer _p;
	public:

	};


	template <class Iterator>
	class ReverseIterator
	{
	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
	};
}


namespace ft {

	template <bool B, class T = void>
	struct enable_if;

	template <class T>
	struct enable_if <true, T> {
		typedef T type;
};

	template<class T, T v>
			struct integral_constant
					{
				static const T value = v;
				typedef T value_type;
				typedef integral_constant<T, v> type;
				operator T() {return (v);}
					};
	template <class T> struct is_integral: public integral_constant<bool, false> {};
	template<> struct is_integral<bool>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<char>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<wchar_t>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<signed char>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<short int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<long int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<long long int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<unsigned char>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<unsigned short int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<unsigned int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<unsigned long int>: public integral_constant<bool, true> {} ;
	template<> struct is_integral<unsigned long long int>: public integral_constant<bool, true> {} ;
}

#endif //FT_CANTAINERS_FT_TYPE_TRAITS_H
