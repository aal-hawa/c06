#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{}
ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void) other;
}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void) other;
	return *this;
}
ScalarConverter::~ScalarConverter()
{}

static bool isChar(const std::string& str)
{
	return str.length() == 1 && !std::isdigit(str[0]);
}

static bool isInt(const std::string& str)
{
	errno = 0;
	char* end;
	std::strtol(str.c_str(), &end, 10);
	if (errno == ERANGE)
		return false;
	return *end == '\0';
}

static bool isNanInf(const std::string& str)
{
	return (
        str == "inf" || str == "+inf" || str == "-inf" ||
        str == "inff" || str == "+inff" || str == "-inff" ||
        str == "nan" || str == "nanf"
    );
}

static bool isFloat(const std::string& str)
{
	if (str == "-inff" || str == "+inff" || str == "nanf")
		return true;
	errno = 0;
	char* end;
	float f = std::strtof(str.c_str(), &end);	
	if (errno == ERANGE || f == HUGE_VALF || f == -HUGE_VALF)
		return false;
	return *end == 'f' && *(end + 1) == '\0'; //(*end == 'f' || *end == 'F')
}

static bool isDouble(const std::string& str)
{
	if (str == "-inff" || str == "+inff" || str == "nanf")
	return true;
	errno = 0;
	char* end;
	double d = std::strtod(str.c_str(), &end);
	if (errno == ERANGE  || d == HUGE_VAL || d == -HUGE_VAL)
		return false;
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
	if (impossible || (!isNanInf(literal) && (std::isnan(value) || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())))
		std::cout << "impossible" << std::endl;
	else 
		std::cout << static_cast<int>(value) << std::endl;

	//print float
	std::cout << "float: ";
	if (impossible || (!isNanInf(literal) && (value < -std::numeric_limits<float>::max() || value > std::numeric_limits<float>::max())))
		std::cout << "impossible" << std::endl;
	else 
		// std::cout << static_cast<float>(value) << std::endl;
		std::cout << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f" << std::endl;
	
	//print double
	std::cout << "double: ";
	if (impossible || value < -std::numeric_limits<double>::max() || value > std::numeric_limits<double>::max())
		std::cout << "impossible" << std::endl;
	else 
		std::cout << std::fixed << std::setprecision(1) << value << std::endl;
}