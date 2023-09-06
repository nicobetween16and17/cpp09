#include "PmergeMe.hpp"
void display(deque &dq)
{
	for (size_t i = 0; i < dq.size(); ++i) {
		std::cout << dq[i]<< " ";
	}
}
void display(vector &v)
{
	for (size_t i = 0; i < v.size(); ++i) {
		std::cout << v[i]<< " ";
	}
}
int binarySearch(deque arr[], int item, int low, int high) {
	if (high <= low)
		return (item > arr[low].back())? (low + 1): low;
	int mid = (low + high)/2;
	if(item == arr[mid].back())
		return mid+1;
	if(item > arr[mid].back())
		return binarySearch(arr, item, mid+1, high);
	return binarySearch(arr, item, low, mid-1);
}
void FordJohnson(deque &v) {
	size_t mid = v.size() / 2;
	deque vlist[mid];
	int last;
	bool islast = false;

	//getting n/2 pairs and front < back
	for (size_t i = 0; i < mid; i++) {
		vlist[i].push_back(v.back());
		v.pop_back();
		vlist[i].push_back(v.back());
		v.pop_back();
		if (vlist[i].front() > vlist[i].back())
			::swap(vlist[i].front(), vlist[i].back());
	}
	//retaining remaining one if list not pair
	islast = v.size();
	if (islast)
	{
		last = v.back();
		v.pop_back();
	}
	//binary search
	for (size_t i = 1; i < mid; ++i) {
		int key = vlist[i].back();
		int j = i;
		int loc = binarySearch(vlist, key, 0, j);
		while (--j >= loc)
			vlist[j + 1].back() = vlist[j].back();
		vlist[j + 1].back() = key;
	}
	//push every biggest numbers of pairs in v from lowest to biggest
	for (size_t i = 0; i < mid; ++i)
		v.push_back(vlist[i].back());
	//insert at the right place the lower one
	for (size_t i = 0; i < mid; ++i)
		v.insert(std::lower_bound(v.begin(), v.end(), vlist[i].front()), vlist[i].front());
	//place the remaining one if there is one
	if (islast)
		v.insert(std::lower_bound(v.begin(), v.end(), last), last);
}

int binarySearch(vector arr[], int item, int low, int high) {
	if (high <= low)
		return (item > arr[low].back())? (low + 1): low;
	int mid = (low + high)/2;
	if(item == arr[mid].back())
		return mid+1;
	if(item > arr[mid].back())
		return binarySearch(arr, item, mid+1, high);
	return binarySearch(arr, item, low, mid-1);
}

void FordJohnson(vector &v) {
	size_t mid = v.size() / 2;
	vector vlist[mid];
	int last;
	bool islast = false;

	for (size_t i = 0; i < mid; i++) {
		vlist[i].push_back(v.back());
		v.pop_back();
		vlist[i].push_back(v.back());
		v.pop_back();
		if (vlist[i].front() > vlist[i].back())
			::swap(vlist[i].front(), vlist[i].back());
	}
	islast = v.size();
	if (islast)
	{
		last = v.back();
		v.pop_back();
	}
	for (size_t i = 1; i < mid; ++i) {
		int key = vlist[i].back();
		int j = i;
		int loc = binarySearch(vlist, key, 0, j);
		while (--j >= loc)
			vlist[j + 1].back() = vlist[j].back();
		vlist[j + 1].back() = key;
	}
	for (size_t i = 0; i < mid; ++i)
		v.push_back(vlist[i].back());
	for (size_t i = 0; i < mid ; ++i)
		v.insert(std::lower_bound(v.begin(), v.end(), vlist[i].front()), vlist[i].front());
	if (islast)
		v.insert(std::lower_bound(v.begin(), v.end(), last), last);
}

bool check_input(std::string s)
{
	for (size_t i = 0; i < s.length(); ++i) {
		if (!i && s[i] == '-')
			i++;
		if (!isdigit(s[i]))
			return true;
	}
	return false;
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "Error: no arguments given\n";
		return (1);
	}
	for (int i = 1; i < ac; ++i)
	{
		if (check_input(av[i]))
		{
			std::cout << "Error: invalid argument\n";
			return (1);
		}
	}
	struct timeval d1, d2, d3, d4;
	deque dq;
	for (int i = 1; i < ac; ++i) {

		dq.push_back(atoi(av[i]));
	}
	vector v;
	for (int i = 1; i < ac; ++i) {
		v.push_back(atoi(av[i]));
	}
	std::cout << "Before: ";
	display(dq);
	std::cout << std::endl;
	gettimeofday(&d1, NULL);
	FordJohnson(dq);
	gettimeofday(&d2, NULL);


	gettimeofday(&d3, NULL);
	FordJohnson(v);
	gettimeofday(&d4, NULL);
	std::cout << "After: ";
	display(v);
	std::cout << std::endl;
	std::cout << "Time to process a range of "<< ac -1 <<" elements with std::deque : "<< d2.tv_usec - d1.tv_usec << " us\n";
	std::cout << "Time to process a range of "<< ac -1 <<" elements with std::vector : "<< d4.tv_usec - d3.tv_usec << " us\n";
	return (0);
}