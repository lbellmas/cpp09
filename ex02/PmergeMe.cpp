#include "PmergeMe.hpp"

Pmerge::Pmerge(int *nums, int size)
{
	for (int i = 0; i < size; i++)
	{
		_v.push_back(nums[i]);
		_dq.push_back(nums[i]);
	}
}

Pmerge::Pmerge(const Pmerge *copy)
{
	_v = copy->_v;
	_dq = copy->_dq;
}

Pmerge::~Pmerge()
{

}

Pmerge	*Pmerge::operator=(const Pmerge *other)
{
	_v = other->_v;
	_dq = other->_dq;
	return (this);
}

void	Pmerge::merge()
{
	std::cout << "sort" << std::endl;
	std::cout << "_v: ";
	for (size_t i = 0; i < _v.size(); i++)
		std::cout << _v[i] << ", ";
	std::cout << "\n _dq: ";
	for (size_t i = 0; i < _dq.size(); i++)
		std::cout << _dq[i] << ", ";
	std::cout << std::endl;
	if (!ford())
		return ;
}

int	Pmerge::ford(void)
{
	std::vector<int> min;
	std::vector<int> max;
	int extra = 0;

	for (size_t i = 0; i < _v.size(); i++)
	{
		int num1 = _v[i];
		if (i + 1 >= _v.size())
		{
			extra = num1;
			break ;
		}
		int num2 = _v[++i];
		if (num1 < num2)
		{
			min.push_back(num1);
			max.push_back(num2);
		}
		else
		{
			min.push_back(num2);
			max.push_back(num1);
		}
	}
	sort(max.begin(), max.end());
	std::cout << "mins: ";
	for (size_t i = 0; i < _v.size() / 2; i++)
		std::cout << min[i] << ", ";
	std::cout << std::endl;
	std::cout << "max: ";
	for (size_t i = 0; i < _v.size() / 2; i++)
		std::cout << max[i] << ", ";
	std::cout << std::endl;
	if (_v.size() % 2)
		std::cout << "extra: " << extra << std::endl;
	return (1);
}
