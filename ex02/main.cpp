#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
		return (std::cerr << "Eror: wrong args" << std::endl, 1);
	int nums[argc];
	for (int i = 1; i < argc; i++)
	{
		int neg = 0;
		std::string tmp = argv[i];
		for (size_t j = 0; j < tmp.size(); j++)
		{
			if (isdigit(argv[i][j]))
				nums[i - 1] = std::strtol(tmp.c_str(), NULL, 10);
			else if (j == 0 && tmp[j] == '-')
				neg = 1;
			else
				return (std::cerr << "Error: wrong args" << std::endl, 1);
		}
		if (neg)
			nums[i] *= -1;
	}
	Pmerge	check(nums, argc - 1);
	check.merge();
	return (0);
}
