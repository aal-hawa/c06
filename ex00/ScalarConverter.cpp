#include "ScalarConverter.hpp"

static bool isChar(const std::string& str)
{
	return str.length() == 1 && !std::isdigit(str[0]);
}

static bool isInt(const std::string& str)
{
	char* end;
	std::strtol(str.c_str(), &end, 10);
	return *end == '\0';
}

static bool isFloat(const std::string& str)
{
	if (str == "-inff" || str == "+inff" || str == "nanf")
		return true;
	char* end;
	std::strtof(str.c_str(), &end);
	return *end == 'f' && *(end + 1) == '\0'; //(*end == 'f' || *end == 'F')
}

static bool isDouble(const std::string& str)
{
	if (str == "-inf" || str == "+inf" || str == "nan")
		return true;
	char* end;
	std::strtod(str.c_str(), &end);
	return *end == '\0';
}

void ScalarConverter::convert(const std::string& literal)
{
	double value = 0.0;
	bool impossible = false;

	if (isChar(literal))
	{
		char c = literal[0];
		value = static_cast<double>(c);
	}
	else if (isInt(literal))
		value = std::strtol(literal.c_str(), NULL, 10);
	else if (isFloat(literal))
		value = std::strtof(literal.c_str(), NULL);
	else if (isDouble(literal))
		value = std::strtod(literal.c_str(), NULL);
	else 
		impossible = true;

	//print char
	std::cout << "char: ";
	if (impossible || std::isnan(value) || value < 0 || value > 127)
		std::cout << "impossible" << std::endl;
	else if (!std::isprint(static_cast<char>(value)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(value) << "'" << std::endl;

	//print int
	std::cout << "int: ";
	if (impossible || std::isnan(value) || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
		std::cout << "impossible" << std::endl;
	else 
		std::cout << static_cast<int>(value) << std::endl;

	//print float
	std::cout << "float: ";
	if (impossible)
		std::cout << "impossible" << std::endl;
	else 
		// std::cout << static_cast<float>(value) << std::endl;
		std::cout << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f" << std::endl;
	
	//print double
	std::cout << "double: ";
	if (impossible)
		std::cout << "impossible" << std::endl;
	else std::cout << std::fixed << std::setprecision(1) << value << std::endl;
}