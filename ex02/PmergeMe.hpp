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
		int ford(void);
};

#endif
