#include "BitcoinExchange.hpp"

bool validFormat(std::string s, e *error)
{
	bool res;
	bool lol;
	bool point = false;
	//std::cout << "testing " << s << std::endl;
	s.find("|") == std::string::npos ? res = false : res = true;
	for (size_t i = 0; i < s.length(); ++i) {
		!res ? i++ : lol = res;
		i < 4 && !isdigit(s[i]) ?  res = false : lol = res;
		i == 4 && s[i] != '-' ? res = false : lol = res;
		i > 4 && i < 7 && !isdigit(s[i]) ? res = false : lol = res;
		i == 7 && s[i] != '-' ? res = false : lol = res;
		i > 7 && i < 10 && !isdigit(s[i]) ? res = false : lol = res;
		i == 10 && s[i] != ' ' ? res = false : lol = res;
		i == 11 && s[i] != '|' ? res = false : lol = res;
		i == 12 && s[i] != ' ' ? res = false : lol = res;
		(point && s[i] == '.' && i > 12) || (i > 12 && !isdigit(s[i]) && s[i] != '.'  && s[i] != '\n' && s[i] != EOF) ? res = false : lol = res;
		i > 12 && !isdigit(s[i]) && s[i] != '.' && s[i] != '\n' && s[i] != EOF ? *error = NOTPOSITIVE : lol = res;
		i > 12 && s[i] != '.' ? point = true : lol = res;
	}
	return res;
}
std::string getKey(std::string line)
{
	std::string res;

	res = line.substr(0, line.find("|"));
	return res;
}

float getValue(std::string line)
{
	float res = 0;
	std::string sub = line.substr(line.find("|") + 2, line.length() -1);
	std::istringstream s(sub);
	s >> res;
	return res;
}

bool validDate(std::string line, e *error)
{
	bool res = true;
	std::stringstream s1(line.substr(0, line.find('-')));
	std::stringstream s2(line.substr(line.find('-') + 1, line.find('-') + 3));
	std::stringstream s3(line.substr(line.find('-') + 4, line.length()));

	int a,b,c;
	s1 >> a; s2 >> b; s3 >> c;
	res = (a >= 2009 && a <= 9999 && b < 13 && c < 13);
	if (!res){ *error = INVALIDDATE; }
	return res;
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "invalid number of argument, expected input is ./exe filename\n";
		return (1);
	}
	e error;
	std::ifstream data("data.csv");
	std::ifstream file(av[1]);
	if (!file.is_open() || !data.is_open())
	{
		std::cout << "Error: could not open file\n";
		return (1);
	}
	std::map<std::string, float> data_map;
	std::string key;
	float value;
	std::string line;
	while (std::getline(data, line))
	{
		std::istringstream keyString(line.substr(line.find(",") + 1, line.length() -1));
		keyString >> value;
		data_map[line.substr(0, line.find(','))] = value;
	}
	while (std::getline(file, line))
	{
		validFormat(line, &error) ? key = getKey(line) : key = "nul";
		validFormat(line, &error) ? value = getValue(line) : value = 1001;
		if (validFormat(line, &error) && validDate(key, &error) && (value <= 1000 || (error = TOOLARGE) > value))
			std::cout << data_map.lower_bound(key)->first << " -> " <<data_map.lower_bound(key)->second * value << std::endl;
		else if (line != "date | value")
		{
			switch (error) {
				case NOTPOSITIVE:std::cout << "Error: not a positive number\n";
					break;
				case TOOLARGE:std::cout << "Error: too large (of?) a number\n";
					break;
				case INVALIDDATE:std::cout << "Error: invalid date\n";
					break;
				default:
					std::cout << "Error: invalid format\n";
			}
		}
	}
	data.is_open() ? data.close() : file.is_open() ? file.close() : (void)value;
	return (0);
}