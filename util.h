#pragma once

#include <vector>
#include <string>

namespace Util
{
	std::vector<std::string> split(const std::string& s, char c = ' ');
	bool isWhiteLine(const std::string& s);
	std::string stripComment(const std::string& s);

	extern const std::string binary_palindrome_code;
	extern const std::string binary_addition_code;
	extern const std::string parenthesis_check_code;
}

