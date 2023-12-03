// Example of std::exclusive_scan()
#include <numeric>
#include <iostream>
#include <vector>
#include <execution>

namespace se = std::execution;

int main()
{
	std::vector<int> vec{ 1, 2, 3, 4 };
	std::vector<int> vec2(vec.size());

	std::exclusive_scan(se::par_unseq, vec.begin(), vec.end(), vec2.begin(), 0);

	// This is equivalent to
	std::vector<int> vec3 { -1, 1, 2, 3 };
	std::vector<int> vec4(vec.size());
	std::inclusive_scan(vec3.begin(), vec3.end(), vec4.begin());

	std::cout << "Vector elements: ";
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';

	std::cout << "Elements of exclusive scan vector: ";
	for (auto i : vec2)
		std::cout << i << ", ";
	std::cout << '\n';

	std::cout << "Elements of inclusive scan vector: ";
	for (auto i : vec4)
		std::cout << i << ", ";
	std::cout << '\n';
}