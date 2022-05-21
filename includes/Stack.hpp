#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP
#include <vector>
#include <iostream>
#include <deque>

namespace ft
{
	template<class T, class Container = std::vector<T> >
	class Stack
	{
/* ******************** Start member types ************************ */
	public:
		typedef Container	container_type;
		typedef typename Container::value_type	value_type;
		typedef typename Container::size_type	size_type;
		typedef typename Container::reference	reference_type;
		typedef typename Container::const_reference const_reference;
		/* ************** End member types ************************ */

		/* ************** Start member objects ************************ */
	private:
		container_type	_C;
		/* ************** Start member functions ************************ */
	public:
		explicit Stack( const Container &cont = Container()) : _C(cont) {}
		~Stack(){}
		Stack &operator=( const Stack& other ) {this->_C = other._C; return(*this);}
		/* ************** End member functions ************************ */

		/* ************** Start element access functions ************************ */
		reference_type top() {return(_C.back());}
		/* ************** End element access functions ************************ */

		/* ************** Start capacity functions ************************ */
		bool empty() const {return(_C.empty());}
		size_type size() const{return(_C.size());}
		/* ************** End capacity functions ************************ */

		/* ************** Start modifiers functions ************************ */
		void push( const value_type& value ) {_C.push_back(value);}
		void pop() {_C.pop_back();}
		/* ************** End modifiers functions ************************ */
		/* ************** Prototype functions of stack ************************ */
		template< class T1, class T2 >
		friend bool operator==( const ft::Stack<T1,T2>& lhs, const ft::Stack<T1,T2>& rhs );

		template< class T1, class T2 >
		friend bool operator!=( const ft::Stack<T1,T2>& lhs, const ft::Stack<T1,T2>&rhs );

		template< class T1, class T2 >
		friend bool operator<( const ft::Stack<T1,T2>& lhs, const ft::Stack<T1,T2> &rhs );

		template< class T1, class T2 >
		friend bool operator<=( const ft::Stack<T1,T2>& lhs, const ft::Stack<T1,T2>& rhs );

		template< class T1, class T2 >
		friend bool operator>( const ft::Stack<T1,T2>& lhs, const ft::Stack<T1,T2>& rhs );

		template< class T1, class T2 >
		friend bool operator>=( const ft::Stack<T1,T2>& lhs, const ft::Stack<T1,T2>& rhs );
	};
	/* ****************** Start non-member functions ************************ */
	template< class T, class Container >
	bool operator==( const ft::Stack<T,Container>& lhs, const ft::Stack<T,Container>& rhs )
	{return(lhs._C == rhs._C);}

	template< class T, class Container >
	bool operator!=( const ft::Stack<T,Container>& lhs, const ft::Stack<T,Container>& rhs )
	{return(lhs._C != rhs._C);}

	template< class T, class Container >
	bool operator<( const ft::Stack<T,Container>& lhs, const ft::Stack<T,Container>& rhs )
	{return(lhs._C < rhs._C);}

	template< class T, class Container >
	bool operator<=( const ft::Stack<T,Container>& lhs, const ft::Stack<T,Container>& rhs )
	{return(lhs._C <= rhs._C);}

	template< class T, class Container >
	bool operator>( const ft::Stack<T,Container>& lhs, const ft::Stack<T,Container>& rhs )
	{return(lhs._C > rhs._C);}

	template< class T, class Container >
	bool operator>=( const ft::Stack<T,Container>& lhs, const ft::Stack<T,Container>& rhs )
	{return(lhs._C >= rhs._C);}
}

#endif //FT_CONTAINERS_STACK_HPP
