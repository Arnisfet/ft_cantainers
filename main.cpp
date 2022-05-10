#include "includes/vector.h"
#include <vector>


int main()
{
	ft::Vector<int> first;
	ft::Vector<int> second(5, 2);
	std::vector<int> third(6,3);
	third.push_back(4);
	std::cout << "GOOD";
}
