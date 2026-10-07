#include "PmergeMe.hpp"

Pmerge::Pmerge(int *nums, int size)
{
	for (int i = 0; i < size; i++)
	{
		_v.push_back(nums[i]);
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
	jacob(ford());
}

std::vector<std::pair<int, int> >	Pmerge::ford(void)
{
	std::vector<std::pair<int, int> > minmax;

	for (size_t i = 0; i < _v.size(); i++)
	{
		int num1 = _v[i];
		if (i + 1 >= _v.size())
			break ;
		int num2 = _v[++i];
		if (num1 < num2)
		{
			std::pair <int,int> temp(num1,num2);
			minmax.push_back(temp);
		}
		else
		{
			std::pair <int,int> temp(num2,num1);
			minmax.push_back(temp);
		}
	}
	sort(minmax.begin(), minmax.end());
	std::cout << "mins: ";
	for (size_t i = 0; i < _v.size() / 2; i++)
		std::cout << minmax[i].first << ", ";
	std::cout << std::endl;
	std::cout << "max: ";
	for (size_t i = 0; i < _v.size() / 2; i++)
		std::cout << minmax[i].second << ", ";
	std::cout << std::endl;
	if (_v.size() % 2)
		std::cout << "extra: " << _v[_v.size() - 1] << std::endl;
	return (minmax);
}

std::vector<size_t> Pmerge::getJacobsthal(size_t size)
{
	size_t prev = 1;
	size_t curr = 3;
	std::vector<size_t> order;
	if (_v.size() % 2 != 0)
		size++;

	if (size >= 3)
		order.push_back(3);
	order.push_back(2);
	size_t next = 3;
	while(next < size)
	{
		next = (curr + 2 * prev);
		for (size_t i = next; i > curr; i--)
		{
			if (i <= size)
				order.push_back(i);
		}
		prev = curr;
		curr = next;
	}
	return (order);
}

void	Pmerge::jacob(std::vector<std::pair<int, int> > pairs)
{
	_dq.push_back(pairs[0].first);
	for (size_t i = 0; i < pairs.size(); i++)
	{
		_dq.push_back(pairs[i].second);
	}
	std::cout << "_dq: ";
	for(size_t i = 0; i < _dq.size(); i++)
		std::cout << _dq[i] << ", ";
	std::cout << "\n";

	std::cout << "size: " << pairs.size() << std::endl;
	if (pairs.size() > 1 || _v.size() % 2 != 0)
	{
		std::vector<size_t> order(getJacobsthal(pairs.size()));

		std::cout << "order: ";
		for(size_t i = 0; i < order.size(); i++)
			std::cout << order[i] << ", ";
		std::cout << "\n";

		for (size_t i = 0; i < order.size(); i++)
		{
			int temp;
			if (order[i] > pairs.size())
				temp = _v[_v.size() - 1];
			else
				temp = pairs[order[i] - 1].first;
			size_t p;
			for (p = 0; p < _dq.size() - 1; p++)
			{
				if (_dq[p] == pairs[order[i] - 1].second)
					break ;
			}
			for (int j = p; j >= 0; j--)
			{
				if (_dq[j] < temp)
				{
					std::cout << "insert en p: " << j << std::endl;
					_dq.insert(_dq.begin() + j + 1, temp);
					break ;
				}
				else if (j == 0)
				{
					std::cout << "insert principio: " << temp << std::endl;
					_dq.insert(_dq.begin() + 0, temp);
				}
			}
		}
	}

	std::cout << "final _dq: ";
	for(size_t i = 0; i < _dq.size(); i++)
		std::cout << _dq[i] << ", ";
	std::cout << "\n";
}

