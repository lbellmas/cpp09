#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <stdlib.h>
#include <algorithm>

class Pmerge
{
	private:
		std::vector<int> _v;
		std::deque<int> _dq;
	public:
		Pmerge(int *nums, int size);
		Pmerge(const Pmerge *copy);
		Pmerge *operator=(const Pmerge *other);
		~Pmerge();

		void	merge(void);
		std::vector<std::pair<int, int> > ford(void);
		void	jacob(std::vector<std::pair<int, int> > pairs);
		std::vector<size_t> getJacobsthal(size_t size);
};
bool comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b);

#endif
