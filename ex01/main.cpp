#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error: invalid argument number, D=digit O=operation(+, -, /, *) expected ./RPN \"D D O D O D O...\"\n";
		return(1);
	}
	std::string arg(av[1]);
	size_t len;
	while ((len = arg.find(" ")) != std::string::npos)
		arg.erase(len, 1);
	for (size_t i = 0; i < arg.length(); ++i) {
		if ((!isdigit(arg[i]) && arg[i] != '+' && arg[i] != '-' && arg[i] != '/' && arg[i] != '*')\
		|| (isdigit(arg[i]) && i == arg.length() - 1))
		{
			std::cout <<"Error: invalid arguments\n";
			return (1);
		}
	}
//	for (size_t i = 0; i < arg.length(); ++i) {
//		if (i == 0 || i == 1 || i % 2)
//		{
//			if (!isdigit(arg[i]))
//			{
//				std::cout <<"Error: invalid argument\n";
//				return (1);
//			}
//
//		}
//		else if (isdigit(arg[i]))
//		{
//			std::cout << "Error: invalid argument\n";
//			return (1);
//		}
//
//	}
	long int res;
	std::list<long int> rpn;
	try {
		for (size_t i = 0; i < arg.length(); ++i) {
			if (isdigit(arg[i]))
				rpn.push_front(arg[i] - 48);
			else if (rpn.size() >= 2)
			{
				switch (arg[i]) {
					case '-':
						res = rpn.front();
						rpn.pop_front();
						res = rpn.front() - res;
						rpn.pop_front();
						rpn.push_front(res);
						break;
					case '+':
						res = rpn.front();
						rpn.pop_front();
						res = rpn.front() + res;
						rpn.pop_front();
						rpn.push_front(res);
						break;
					case '*':
						res = rpn.front();
						rpn.pop_front();
						res = rpn.front() * res;
						rpn.pop_front();
						rpn.push_front(res);
						break;
					case '/':
						if (!rpn.front())
							throw std::exception();
						res = rpn.front();
						rpn.pop_front();
						res = rpn.front() / res;
						rpn.pop_front();
						rpn.push_front(res);
						break;
				}
			}
			else
			{
				std::cout << "Error: invalid argument\n";
				return (1);
			}
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Error: division by 0 is impossible\n";
		return (1);
	}
	if (rpn.size() != 1)
	{
		std::cout << "Error: invalid argument\n";
		return (1);
	}
	std::cout << rpn.back() << "\n";
	return (0);
}