#include "includes/vector.hpp"
#include <vector>
#include "includes/ft_type_traits.hpp"

int main()
{
	ft::Vector<int> v;
	ft::Vector<int> tmp0(v);
	ft::Vector<int> tmp(1000, 4), tmp2(1000, 5);
	tmp = tmp2;
	ft::Vector<int> tmp3(tmp);
	ft::Vector<int> tmp4(tmp.begin(), tmp.end());
	v.push_back(tmp4.size());
	v.push_back(tmp4.capacity());
	v.push_back(tmp[2]);
	v.push_back(tmp3[2]);
	v.push_back(tmp4[2]);
}
