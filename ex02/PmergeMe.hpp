#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <sys/time.h>
#include <unistd.h>

typedef std::deque<int> deque;
typedef std::vector<int> vector;

template<typename T>void swap (T& x, T& y)
{
	T temp = x;
	x = y;
	y = temp;
}
#endif