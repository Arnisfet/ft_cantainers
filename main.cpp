#include "includes/Vector.hpp"
#include <vector>
#include "includes/ft_type_traits.hpp"

int main()
{
	std::vector<int> v;
	std::vector<int> tmp0(v);
	std::vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
	tmp = tmp2;
	std::vector<int> tmp3(tmp);
	std::vector<int> tmp4(tmp.begin(), tmp.end());
	v.push_back(tmp4.size());
	v.push_back(tmp4.capacity());
	v.push_back(tmp[2]);
	v.push_back(tmp3[2]);
	v.push_back(tmp4[2]);
}
